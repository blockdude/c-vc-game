#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#include "kd-tree.h"
#include "sdl-game.h"

#include "grid-map-util.h"
#include "collision-util.h"
#include "vc-world-util.h"

// game info
float scale_x;
float scale_y;
float camera_x;
float camera_y;
float mouse_world_x;
float mouse_world_y;
int sel_def;

// window info
int window_w;
int window_h;

// viewports
SDL_Rect main_view;
SDL_Rect button_view;

// world
vc_world *world;

// settings
const float zoom_speed = 1.3f;
const int button_view_width = 150;

int render()
{
    /*
     * main view render
     */

    SDL_RenderSetViewport( renderer, &main_view );

    int point[] = { floor( camera_x ), floor( camera_y ) };
    int dim[] = { ceil( main_view.w / scale_x ) + 1, ceil( main_view.h / scale_y ) + 1 };

    int length = 0;
    vc_result *query = vc_query_rect( world, point[ 0 ], point[ 1 ], dim[ 0 ], dim[ 1 ] );
    vc_object *obj = vc_poll_result( query );
    while( obj )
    {
        SDL_FRect temp;
        double x, y;
        vc_get_object_pos( obj, &x, &y );
        world_to_screen_f( x, y, &temp.x, &temp.y );
        temp.w = scale_x;
        temp.h = scale_y;

        char r, g, b, a;
        int color = vc_get_object_comp( obj, VC_COMP_COLOR );
        vc_split_color( color, &r, &g, &b, &a );

        SDL_SetRenderDrawColor( renderer, r, g, b, a );
        SDL_RenderFillRectF( renderer, &temp );

        obj = vc_poll_result( query );
        length++;
    }

    vc_free_result( query );

    /*
     * button view render
     */

    SDL_RenderSetViewport( renderer, &button_view );

    float button_height = ( float ) window_h / VC_DEF_LAST;
    SDL_FRect button;

    button.x = 1;
    button.y = 0;
    button.w = button_view.w - 1;
    button.h = button_height;

    for ( int i = 0; i < VC_DEF_LAST; i++ )
    {
        char r, g, b, a;
        int color = vc_get_def_comp( i, VC_COMP_COLOR );
        vc_split_color( color, &r, &g, &b, &a );

        SDL_SetRenderDrawColor( renderer, r, g, b, a );
        SDL_RenderFillRectF( renderer, &button );

        // highlight if selected
        if ( i == sel_def )
        {
            SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
            SDL_RenderDrawRectF( renderer, &button );
        }

        button.y += button_height;
    }

    SDL_SetRenderDrawColor( renderer, 0x80, 0x80, 0x80, 255 );
    SDL_RenderDrawLine( renderer, 0, 0, 0, button_view.h );

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

                    main_view.x = 0;
                    main_view.y = 0;
                    main_view.w = window_w - 150;
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

    if ( pt_in_rect( mouse_x, mouse_y, main_view.x, main_view.y, main_view.w, main_view.h ) )
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

    /*
     * button view handle
     */

    else if ( pt_in_rect( mouse_x, mouse_y, button_view.x, button_view.y, button_view.w, button_view.h ) )
    {
        switch ( event.type )
        {
            case SDL_MOUSEBUTTONDOWN:

                if ( event.button.button == SDL_BUTTON_LEFT )
                {
                    float button_height = ( float ) window_h / VC_DEF_LAST;
                    SDL_FRect button;

                    button.x = 0;
                    button.y = 0;
                    button.w = button_view.w;
                    button.h = button_height;

                    // check if mouse is over any button from defs
                    for ( int i = 0; i < VC_DEF_LAST; i++ )
                    {
                        if ( pt_in_rect_f( mouse_x - button_view.x, mouse_y - button_view.y, button.x, button.y, button.w, button.h ) )
                        {
                            sel_def = i;
                            break;
                        }

                        button.y += button_height;
                    }
                }

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

    if ( pt_in_rect( mouse_x, mouse_y, main_view.x, main_view.y, main_view.w, main_view.h ) )
    {
        /*
         * panning
         */

        static int prev_mouse_x = 0;
        static int prev_mouse_y = 0;

        if ( ( mouse_state & SDL_BUTTON_MMASK ) != 0)
        {
            camera_x += ( prev_mouse_x - mouse_x ) / scale_x;
            camera_y += ( prev_mouse_y - mouse_y ) / scale_y;
        }

        prev_mouse_x = mouse_x;
        prev_mouse_y = mouse_y;

        /*
         * place / remove objects
         */

        if ( ( mouse_state & SDL_BUTTON_LMASK ) != 0 )
        {
            vc_object *new_obj = vc_new_object( floor( mouse_world_x ), floor( mouse_world_y ), sel_def );
            if ( !vc_insert_object( world, new_obj ) )
                vc_free_object( new_obj );
        }

        if ( ( mouse_state & SDL_BUTTON_RMASK ) != 0 )
        {
            vc_result *query = vc_query_point( world, ( int ) mouse_world_x, ( int ) mouse_world_y );
            vc_object *obj = vc_poll_result( query );

            vc_remove_object( world, obj );
            vc_free_object( obj );

            vc_free_result( query );
        }
    }

    /*
     * button view update
     */

    else if ( pt_in_rect( mouse_x, mouse_y, button_view.x, button_view.y, button_view.w, button_view.h ) )
    {
    }

    /*
     * draw objects
     */

    SDL_RenderClear( renderer );
    int i = render();
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
    printf( "mouse_world_pos    :%3.0f, %3.0f\n", mouse_world_x, mouse_world_y );
    printf( "camera_pos         :%3.0f, %3.0f\n", camera_x, camera_y );
    printf( "scaling            :%3.0f, %3.0f\n", scale_x, scale_y );
    printf( "selected def       :%2d\n", sel_def );

    return 0;
}

//void test_random_points( int w, int h, int c )
//{
//    for ( int i = 0; i < c; i++ )
//    {
//        int point[] = { rand() % w - w / 2, rand() % h - h / 2 };
//        kd_insert( objects, point, new_object( point[ 0 ], point[ 1 ], rand() % LAST ) );
//    }
//}
//
void test_memory_leak_points( int w, int h, int c )
{
    for ( int i = 0; i < c; i++ )
    {
        srand( i );
        int point[] = { rand() % w - w / 2, rand() % h - h / 2 };

        vc_object *new_obj = vc_new_object( point[ 0 ], point[ 1 ], VC_DEF_WALL );
        if ( !vc_insert_object( world, new_obj ) )
            vc_free_object( new_obj );
    }

    for ( int i = 0; i < c; i++ )
    {
        srand( i );
        int point[] = { rand() % w - w / 2, rand() % h - h / 2 };

        vc_result *query = vc_query_point( world, point[ 0 ], point[ 1 ] );
        vc_object *obj = vc_poll_result( query );

        vc_remove_object( world, obj );
        vc_free_object( obj );

        vc_free_result( query );
    }
}

int main()
{
    /*
     * pre init
     */

    window_w = 850;
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

    world = vc_load_world( NULL );

    scale_x = 100;
    scale_y = 100;
    camera_x = 0;
    camera_y = 0;
    sel_def = 0;

    fps_cap = 60;

    SDL_SetWindowResizable( window, SDL_TRUE );

    test_memory_leak_points( 1000, 1000, 1000000 );

    /*
     * game
     */

    start_game();

    /*
     * clean up
     */

    close_game();
    vc_free_world( world );

    return 0;
}
