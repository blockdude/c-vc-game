#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SDL2/SDL.h>

#include "sdl-window.h"
#include "scene.h"
#include "util.h"
#include "sprite.h"

// window info
int window_w;
int window_h;

// viewports
SDL_Rect button_view;

// main_scene
scene *main_scene;
float pvx = 0;
float pvy = 0;

// settings
const float zoom_speed = 1.3f;
const float player_speed = 10.0f;
const int button_view_width = 0;

// player
sprite *player_sprite[4];
object *player;
int player_direction = 0;
float frame_time = 0.2f;
float hitbox = 0.4f;

// fram counter
int frame = 0;

/*
 * window stuff
 */

int render()
{
    SDL_RenderSetViewport( renderer, &main_view );

    /*
     * render player
     */

    {
        float x, y;
        get_object_pos( player, &x, &y );

        SDL_Rect rect = { 0, 0, scale.x, scale.y };
        switch ( player_direction )
        {
            // north
            case 0:
                world_to_screen( x, y, &rect.x, &rect.y );
                render_sprite( renderer, player_sprite[ player_direction ], &rect, 0 );
                break;

            // south
            case 1:
                world_to_screen( x + 0.1f, y - 0.1f, &rect.x, &rect.y );
                render_sprite( renderer, player_sprite[ player_direction ], &rect, 0 );
                break;

            // west
            case 2:
                rect.w /= 1.25f;
                rect.h /= 1.25f;
                world_to_screen( x + 0.09f, y + 0.1f, &rect.x, &rect.y );
                render_sprite( renderer, player_sprite[ player_direction ], &rect, SDL_FLIP_HORIZONTAL );
                break;

            // east
            case 3:
                rect.w /= 1.25f;
                rect.h /= 1.25f;
                world_to_screen( x + 0.11f, y + 0.1f, &rect.x, &rect.y );
                render_sprite( renderer, player_sprite[ player_direction ], &rect, 0 );
                break;
        }

        center_pos( x, y, &x, &y );

        char r, g, b, a;
        int color = get_object_comp( player, COMP_COLOR );
        split_color( color, &r, &g, &b, &a );

        SDL_SetRenderDrawColor( renderer, r, g, b, a );
        draw_circle_world( renderer, x, y, hitbox );
    }

    /*
     * render main_scene
     */

    int point[] = { floor( camera.x ), floor( camera.y ) };
    int dim[] = { ceil( main_view.w / scale.x ) + 1, ceil( main_view.h / scale.y ) + 1 };

    int length = 0;
    result *query = query_dim( main_scene, point[ 0 ], point[ 1 ], dim[ 0 ], dim[ 1 ] );
    object *obj = poll_result( query );
    while( obj )
    {
        SDL_FRect temp = { 0, 0, 1, 1 };
        get_object_pos( obj, &temp.x, &temp.y );

        char r, g, b, a;
        int color = get_object_comp( obj, COMP_COLOR );
        split_color( color, &r, &g, &b, &a );

        SDL_SetRenderDrawColor( renderer, r, g, b, a );
        fill_rect_world( renderer, &temp );

        obj = poll_result( query );
        length++;
    }

    free_result( query );

    return length;
}

int handle()
{
    /*
     * general handle
     */

    switch ( event.type )
    {
        case SDL_WINDOWEVENT:

            switch ( event.window.event )
            {
                case SDL_WINDOWEVENT_RESIZED:

                    SDL_GetWindowSize( window, &window_w, &window_h );

                    float x, y;
                    get_object_pos( player, &x, &y );
                    camera.x = x - window_w / 2 / scale.x + 0.5f;
                    camera.y = y - window_h / 2 / scale.y + 0.5f;

                    main_view.x = 0;
                    main_view.y = 0;
                    main_view.w = window_w - button_view_width;
                    main_view.h = window_h;

                    button_view.x = main_view.w;
                    button_view.y = 0;
                    button_view.w = window_w - main_view.w;
                    button_view.h = window_h;

                    break;
            }

            break;
    }

    /*
     * main view handle
     */

    if ( SDL_PointInRect( &mouse_screen, &main_view ) )
    {
        switch ( event.type )
        {
            case SDL_MOUSEWHEEL:

                /*
                 * zooming
                 */

                // before and after zoom for camera offset
                float bzx, bzy;
                float azx, azy;

                screen_to_world( window_w / 2, window_h / 2, &bzx, &bzy );

                if ( event.wheel.y > 0 ) // scroll up (zoom in)
                {
                    scale.x = ceil( scale.x * zoom_speed );
                    scale.y = ceil( scale.y * zoom_speed );
                }
                else if ( event.wheel.y < 0 ) // scroll down (zoom out)
                {
                    if ( scale.x != 1 )
                        scale.x = floor( scale.x / zoom_speed );

                    if ( scale.y != 1 )
                        scale.y = floor( scale.y / zoom_speed );
                }

                screen_to_world( window_w / 2, window_h / 2, &azx, &azy );

                camera.x += bzx - azx;
                camera.y += bzy - azy;

                break;
        }
    }

    return 0;
}

int update()
{
    /*
     * get input
     */

    /*
     * main view update
     */

    pvx = 0;
    pvy = 0;

    if ( SDL_PointInRect( &mouse_screen, &main_view ) )
    {
        /*
         * player movement
         */

        // north
        if ( keystate[ SDL_SCANCODE_W ] )
        {
            pvy -= 1.0f;
            player_direction = 0;
        }

        // south
        if ( keystate[ SDL_SCANCODE_S ] )
        {
            pvy += 1.0f;
            player_direction = 1;
        }

        // west
        if ( keystate[ SDL_SCANCODE_A ] )
        {
            pvx -= 1.0f;
            player_direction = 2;
        }

        // east
        if ( keystate[ SDL_SCANCODE_D ] )
        {
            pvx += 1.0f;
            player_direction = 3;
        }
    }

    /*
     * collision detection and resolution
     */

    // variables
    normalize( pvx, pvy, &pvx, &pvy );

    float player_x;
    float player_y;
    get_object_pos( player, &player_x, &player_y );
    center_pos( player_x, player_y, &player_x, &player_y );

    // potential position
    float potpos_x = player_x + pvx * player_speed * delta_t;
    float potpos_y = player_y + pvy * player_speed * delta_t;

    SDL_FRect rect_query;

    // init rect_query
    rect_query.x = floor( player_x ) - 1;
    rect_query.y = floor( player_y ) - 1;
    rect_query.w = 3;
    rect_query.h = 3;

    // check and resolve collision
    result *r = query_dim( main_scene, rect_query.x, rect_query.y, rect_query.w, rect_query.h );
    object *obj = poll_result( r );
    while ( obj )
    {
        float object_x;
        float object_y;

        get_object_pos( obj, &object_x, &object_y );

        float near_x = clamp( potpos_x, object_x, object_x + 1.0f );
        float near_y = clamp( potpos_y, object_y, object_y + 1.0f );

        float raynear_x = near_x - potpos_x;
        float raynear_y = near_y - potpos_y;

        float overlap = hitbox - magnitude( raynear_x, raynear_y );

        // check for nan
        if ( overlap != overlap ) overlap = 0;

        if ( overlap > 0 )
        {
            normalize( raynear_x, raynear_y, &raynear_x, &raynear_y );
            potpos_x = potpos_x - raynear_x * overlap;
            potpos_y = potpos_y - raynear_y * overlap;
        }

        obj = poll_result( r );
    }
    free_result( r );

    add_object_pos( player, potpos_x - player_x, potpos_y - player_y );
    camera.x += potpos_x - player_x;
    camera.y += potpos_y - player_y;

    /*
     * draw objects
     */

    // clear screen with white
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderClear( renderer );

    int i = render();

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 33 );
    fill_rect_world( renderer, &rect_query );

    SDL_RenderPresent( renderer );

    /*
     * info
     */

    printf( "---------------------------\n" );
    printf( "frame              :%3d\n",           frame++ );
    printf( "fps                :%3.4f\n",          fps_cur );
    printf( "fps_avg            :%3.4f\n",          fps_avg );
    printf( "objects            :%3d\n",            get_object_count( main_scene ) );
    printf( "objects_rendered   :%3d\n",            i );
    printf( "mouse_screen_pos   :%3d, %3d\n",       mouse_screen.x, mouse_screen.y );
    printf( "mouse_world_pos    :%3d, %3d\n",       mouse_world_floor.x, mouse_world_floor.y );
    printf( "player_pos         :%3.2f, %3.2f\n",   player_x, player_y );
    printf( "player_speed       :%3.2f\n",          magnitude( potpos_x - player_x, potpos_y - player_y ) * fps_cur );
    printf( "camera_pos         :%3.0f, %3.0f\n",   floor( camera.x ), floor( camera.y ) );
    printf( "scaling            :%3.0f, %3.0f\n",   scale.x, scale.y );

    return 0;
}

int main()
{
    /*
     * pre init
     */

    window_w = 700;
    window_h = 700;

    main_view.x = 0;
    main_view.y = 0;
    main_view.w = window_w - button_view_width;
    main_view.h = window_h;

    button_view.x = main_view.w;
    button_view.y = 0;
    button_view.w = window_w - main_view.w;
    button_view.h = window_h;

    /*
     * init
     */

    init_game( window_w, window_h, "main_scene creation tool" );

    /*
     * post init
     */

    scale.x = 100;
    scale.y = 100;
    camera.x = 0;
    camera.y = 0;

    fps_cap = 60;

    SDL_SetWindowResizable( window, SDL_TRUE );
    SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_BLEND );

    /*
     * load main_scene
     */

    player = new_object(
            ( ( camera.x + ( main_view.w / 2 ) ) / scale.x ) - 0.5f,
            ( ( camera.y + ( main_view.h / 2 ) ) / scale.y ) - 0.5f,
            DEF_PLAYER );

    player_sprite[ 0 ] = load_sprite( renderer, "textures/player-north.bmp", 250, 250, 3, 100 ); // north
    player_sprite[ 1 ] = load_sprite( renderer, "textures/player-south.bmp", 250, 250, 3, 100 ); // south
    player_sprite[ 2 ] = load_sprite( renderer, "textures/player-east.bmp", 250, 250, 2, 100 );  // west
    player_sprite[ 3 ] = load_sprite( renderer, "textures/player-east.bmp", 250, 250, 2, 100 );  // east

    if ( player_sprite == NULL )
        return 1;

    main_scene = load_scene( "world.level" );

    /*
     * game
     */

    start_game();

    /*
     * save main_scene
     */

    save_scene( main_scene, "world.level" );

    /*
     * clean up
     */

    close_game();
    free_scene( main_scene );

    return 0;
}
