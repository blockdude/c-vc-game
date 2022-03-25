#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "sdl-game.h"
#include "vc-world.h"
#include "util.h"

// game info
float scale_x;
float scale_y;
float camera_x;
float camera_y;
float mouse_world_x;
float mouse_world_y;

// window info
int window_w;
int window_h;

// viewports
SDL_Rect main_view;
SDL_Rect button_view;

// world
vc_world *world;
vc_object *player;
float pvx = 0;
float pvy = 0;

// settings
const float zoom_speed = 1.3f;
const float player_speed = 9.0f;
const int button_view_width = 0;

/*
 * util
 */

void draw_circle_f( SDL_Renderer *renderer, float x0, float y0, float radius )
{
    float diameter = radius * 2;
    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - diameter;

    while (x >= y)
    {
        SDL_RenderDrawPoint( renderer, x0 + x, y0 + y );
        SDL_RenderDrawPoint( renderer, x0 + y, y0 + x );
        SDL_RenderDrawPoint( renderer, x0 - y, y0 + x );
        SDL_RenderDrawPoint( renderer, x0 - x, y0 + y );
        SDL_RenderDrawPoint( renderer, x0 - x, y0 - y );
        SDL_RenderDrawPoint( renderer, x0 - y, y0 - x );
        SDL_RenderDrawPoint( renderer, x0 + y, y0 - x );
        SDL_RenderDrawPoint( renderer, x0 + x, y0 - y );

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - diameter;
        }
    }
}

int pt_in_rect( int ax, int ay, int bx, int by, int w, int h )
{
    return ( ax >= bx && ax <= bx + w && ay >= by && ay <= by + h );
}

int pt_in_rect_f( int ax, int ay, float bx, float by, float w, float h )
{
    return ( ax >= bx && ax <= bx + w && ay >= by && ay <= by + h );
}

int rect_in_rect( SDL_FRect a, SDL_FRect b )
{
    return (
            a.x + a.w > b.x &&
            a.x < b.x + b.w &&
            a.y + a.h > b.y &&
            a.y < b.y + b.h );
}

void screen_to_world( int screen_x, int screen_y, float *world_x, float *world_y )
{
    *world_x = ( float ) ( screen_x / scale_x + camera_x );
    *world_y = ( float ) ( screen_y / scale_y + camera_y );
}

void world_to_screen( float world_x, float world_y, int *screen_x, int *screen_y )
{
    *screen_x = ( int ) ( ( world_x - camera_x ) * scale_x );
    *screen_y = ( int ) ( ( world_y - camera_y ) * scale_y );
}

void screen_to_world_f( float screen_x, float screen_y, float *world_x, float *world_y )
{
    *world_x = ( float ) ( screen_x / scale_x + camera_x );
    *world_y = ( float ) ( screen_y / scale_y + camera_y );
}

void world_to_screen_f( float world_x, float world_y, float *screen_x, float *screen_y )
{
    *screen_x = ( float ) ( ( world_x - camera_x ) * scale_x );
    *screen_y = ( float ) ( ( world_y - camera_y ) * scale_y );
}

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
        SDL_FRect temp;
        float x, y;
        vc_get_object_pos( player, &x, &y );
        center_pos( x, y, &x, &y );
        world_to_screen_f( x, y, &temp.x, &temp.y );
        temp.w = scale_x;
        temp.h = scale_y;

        char r, g, b, a;
        int color = vc_get_object_comp( player, VC_COMP_COLOR );
        split_color( color, &r, &g, &b, &a );

        SDL_SetRenderDrawColor( renderer, r, g, b, a );
        draw_circle_f( renderer, temp.x, temp.y, scale_x / 2 );
    }

    /*
     * render world
     */

    int point[] = { floor( camera_x ), floor( camera_y ) };
    int dim[] = { ceil( main_view.w / scale_x ) + 1, ceil( main_view.h / scale_y ) + 1 };

    int length = 0;
    vc_result *query = vc_query_dim( world, point[ 0 ], point[ 1 ], dim[ 0 ], dim[ 1 ] );
    vc_object *obj = vc_poll_result( query );
    while( obj )
    {
        SDL_FRect temp;
        float x, y;
        vc_get_object_pos( obj, &x, &y );
        world_to_screen_f( x, y, &temp.x, &temp.y );
        temp.w = scale_x;
        temp.h = scale_y;

        char r, g, b, a;
        int color = vc_get_object_comp( obj, VC_COMP_COLOR );
        split_color( color, &r, &g, &b, &a );

        SDL_SetRenderDrawColor( renderer, r, g, b, a );
        SDL_RenderDrawRectF( renderer, &temp );

        obj = vc_poll_result( query );
        length++;
    }

    vc_free_result( query );

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
                    vc_get_object_pos( player, &x, &y );
                    camera_x = x - window_w / 2 / scale_x + 0.5f;
                    camera_y = y - window_h / 2 / scale_y + 0.5f;

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

    SDL_Point mouse = { mouse_x, mouse_y };
    if ( SDL_PointInRect( &mouse, &main_view ) )
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
                    scale_x = ceil( scale_x * zoom_speed );
                    scale_y = ceil( scale_y * zoom_speed );
                }
                else if ( event.wheel.y < 0 ) // scroll down (zoom out)
                {
                    if ( scale_x != 1 )
                        scale_x = floor( scale_x / zoom_speed );

                    if ( scale_y != 1 )
                        scale_y = floor( scale_y / zoom_speed );
                }

                screen_to_world( window_w / 2, window_h / 2, &azx, &azy );

                camera_x += bzx - azx;
                camera_y += bzy - azy;

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

    screen_to_world( mouse_x, mouse_y, &mouse_world_x, &mouse_world_y );
    mouse_world_x = floor( mouse_world_x );
    mouse_world_y = floor( mouse_world_y );

    /*
     * main view update
     */

    pvx = 0;
    pvy = 0;

    if ( pt_in_rect( mouse_x, mouse_y, main_view.x, main_view.y, main_view.w, main_view.h ) )
    {
        /*
         * player movement
         */

        if ( keystate[ SDL_SCANCODE_W ] )
        {
            pvy -= 1.0f;
        }

        if ( keystate[ SDL_SCANCODE_S ] )
        {
            pvy += 1.0f;
        }

        if ( keystate[ SDL_SCANCODE_A ] )
        {
            pvx -= 1.0f;
        }

        if ( keystate[ SDL_SCANCODE_D ] )
        {
            pvx += 1.0f;
        }
    }

    /*
     * collision detection and resolution
     */

    // variables
    normalize( pvx, pvy, &pvx, &pvy );

    float player_x;
    float player_y;
    vc_get_object_pos( player, &player_x, &player_y );
    center_pos( player_x, player_y, &player_x, &player_y );
    float potpos_x = player_x + pvx * player_speed * delta_t;
    float potpos_y = player_y + pvy * player_speed * delta_t;

    float object_x;
    float object_y;

    SDL_Rect query_dim;

    // init query_dim
    query_dim.x = floor( player_x ) - 1;
    query_dim.y = floor( player_y ) - 1;
    query_dim.w = 3;
    query_dim.h = 3;

    // check collision
    vc_result *result = vc_query_dim( world, query_dim.x, query_dim.y, query_dim.w, query_dim.h );
    vc_object *object = vc_poll_result( result );
    while ( object )
    {
        vc_get_object_pos( object, &object_x, &object_y );

        float near_x = clamp( potpos_x, object_x, object_x + 1 );
        float near_y = clamp( potpos_y, object_y, object_y + 1 );

        float raynear_x = near_x - potpos_x;
        float raynear_y = near_y - potpos_y;

        float overlap = 0.5f - magnitude( raynear_x, raynear_y );

        // check for nan
        if ( overlap != overlap ) overlap = 0;

        if ( overlap > 0 )
        {
            normalize( raynear_x, raynear_y, &raynear_x, &raynear_y );
            potpos_x = potpos_x - raynear_x * overlap;
            potpos_y = potpos_y - raynear_y * overlap;
        }

        object = vc_poll_result( result );
    }
    vc_free_result( result );

    vc_add_object_pos( player, potpos_x - player_x, potpos_y - player_y );
    camera_x += potpos_x - player_x;
    camera_y += potpos_y - player_y;

    /*
     * draw objects
     */

    SDL_RenderClear( renderer );

    // debug stuff

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

    int i = render();

    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 33 );
    SDL_FRect screen_dim;
    world_to_screen_f( query_dim.x, query_dim.y, &screen_dim.x, &screen_dim.y );
    screen_dim.w = scale_x * query_dim.w;
    screen_dim.h = scale_y * query_dim.h;
    SDL_RenderFillRectF( renderer, &screen_dim );

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderPresent( renderer );

    /*
     * info
     */

    printf( "---------------------------\n" );
    printf( "fps                :%3.4f\n", fps );
    printf( "fps_avg            :%3.4f\n", fps_avg );
    printf( "objects            :%3d\n", vc_get_object_count( world ) );
    printf( "objects_rendered   :%3d\n", i );
    printf( "mouse_screen_pos   :%3d, %3d\n", mouse_x, mouse_y );
    printf( "mouse_world_pos    :%3.0f, %3.0f\n", floor( mouse_world_x ), floor( mouse_world_y ) );
    printf( "player_pos         :%3.2f, %3.2f\n", player_x, player_y );
    printf( "player_speed       :%3.2f\n", magnitude( pvx, pvy ) );
    printf( "camera_pos         :%3.0f, %3.0f\n", floor( camera_x ), floor( camera_y ) );
    printf( "scaling            :%3.0f, %3.0f\n", scale_x, scale_y );

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

    init_game( window_w, window_h, "world creation tool" );

    /*
     * post init
     */

    scale_x = 100;
    scale_y = 100;
    camera_x = 0;
    camera_y = 0;

    fps_cap = 60;

    SDL_SetWindowResizable( window, SDL_TRUE );
    SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_ADD );

    /*
     * load world
     */

    player = vc_new_object(
            ( ( camera_x + ( main_view.w / 2 ) ) / scale_x ) - 0.5f,
            ( ( camera_y + ( main_view.h / 2 ) ) / scale_y ) - 0.5f,
            VC_DEF_PLAYER );

    world = vc_load_world( "world.level" );

    /*
     * game
     */

    start_game();

    /*
     * save world
     */

    vc_save_world( world, "world.level" );

    /*
     * clean up
     */

    close_game();
    vc_free_world( world );

    return 0;
}
