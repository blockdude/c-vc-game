#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "linked-list.h"
#include "kd-tree.h"
#include "sdl-game.h"
#include "objects.h"
#include "grid-map.h"

// game info
float mouse_world_x;
float mouse_world_y;
int sel_def;

// window info
int window_w;
int window_h;

// viewports
SDL_Rect main_view;
SDL_Rect button_view;

// settings
const float zoom_speed = 1.3f;
const int button_view_width = 150;

int pt_in_rect( int x, int y, SDL_Rect *port )
{
    return ( x >= port->x && x <= port->x + port->w && y >= port->y && y <= port->y + port->h );
}

int pt_in_rect_f( int x, int y, SDL_FRect *port )
{
    return ( x >= port->x && x <= port->x + port->w && y >= port->y && y <= port->y + port->h );
}

int render()
{
    /*
     * main view
     */

    SDL_RenderSetViewport( renderer, &main_view );

    int point[] = { floor( camera_x ), floor( camera_y ) };
    int dim[] = { ceil( main_view.w / scale_x ) + 1, ceil( main_view.h / scale_y ) + 1 };

    int length;
    void **query = kd_query_dim( objects, point, dim, &length );

    for ( int i = 0; i < length; i++ )
    {
        object *obj = query[ i ];
        SDL_FRect temp;
        world_to_screen_f( obj->x, obj->y, &temp.x, &temp.y );
        temp.w = scale_x;
        temp.h = scale_y;

        char r, g, b, a;
        split_color( obj->def->color, &r, &g, &b, &a );

        SDL_SetRenderDrawColor( renderer, r, g, b, a );
        SDL_RenderFillRectF( renderer, &temp );
    }

    free( query );

    /*
     * button view
     */

    SDL_RenderSetViewport( renderer, &button_view );

    float button_height = ( float ) window_h / def_c;
    SDL_FRect button;

    button.x = 1;
    button.y = 0;
    button.w = button_view.w - 1;
    button.h = button_height;

    for ( int i = 0; i < def_c; i++ )
    {
        char r, g, b, a;
        split_color( defs[ i ].color, &r, &g, &b, &a );

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

    if ( pt_in_rect( mouse_x, mouse_y, &main_view ) )
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

    else if ( pt_in_rect( mouse_x, mouse_y, &button_view ) )
    {
        switch ( event.type )
        {
            case SDL_MOUSEBUTTONDOWN:

                if ( event.button.button == SDL_BUTTON_LEFT )
                {
                    float button_height = ( float ) window_h / def_c;
                    SDL_FRect button;

                    button.x = 0;
                    button.y = 0;
                    button.w = button_view.w;
                    button.h = button_height;

                    // check if mouse is over any button from defs
                    for ( int i = 0; i < def_c; i++ )
                    {
                        if ( pt_in_rect_f( mouse_x - button_view.x, mouse_y - button_view.y, &button ) )
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

    if ( pt_in_rect( mouse_x, mouse_y, &main_view ) )
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
            place_object( mouse_world_x, mouse_world_y, sel_def );
        }

        if ( ( mouse_state & SDL_BUTTON_RMASK ) != 0 )
        {
            remove_object( mouse_world_x, mouse_world_y );
        }
    }

    /*
     * button view update
     */

    else if ( pt_in_rect( mouse_x, mouse_y, &button_view ) )
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
    printf( "objects            :%3d\n", kd_size( objects ) );
    printf( "objects_rendered   :%3d\n", i );
    printf( "mouse_screen_pos   :%3d, %3d\n", mouse_x, mouse_y );
    printf( "mouse_world_pos    :%3.0f, %3.0f\n", mouse_world_x, mouse_world_y );
    printf( "camera_pos         :%3.0f, %3.0f\n", camera_x, camera_y );
    printf( "scaling            :%3.0f, %3.0f\n", scale_x, scale_y );
    printf( "selected def       :%2d\n", sel_def );

    return 0;
}

void test_random_points( int w, int h, int c )
{
    for ( int i = 0; i < c; i++ )
    {
        int point[] = { rand() % w - w / 2, rand() % h - h / 2 };
        kd_insert( objects, point, new_object( point[ 0 ], point[ 1 ], rand() % LAST ) );
    }
}

void test_memory_leak_points( int w, int h, int c )
{
    for ( int j = 0; j < c; j++ )
    {
        for ( int i = 0; i < 100; i++ )
        {
            srand( i );
            int point[] = { rand() % w - w / 2, rand() % h - h / 2 };
            kd_insert( objects, point, new_object( point[ 0 ], point[ 1 ], rand() % LAST ) );
        }

        for ( int i = 0; i < 100; i++ )
        {
            srand( i );
            int point[] = { rand() % w - w / 2, rand() % h - h / 2 };
            kd_remove( objects, point );
        }
    }
}

int main()
{
    /*
     * pre window
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

    init_game( window_w, window_h, "world creation tool" );

    /*
     * post window
     */

    load_defs( NULL );
    load_level( NULL );

    sel_def = 0;
    objects = new_kd_tree( 2, NULL );
    scale_x = 100;
    scale_y = 100;
    camera_x = 0;
    camera_y = 0;

    fps_cap = 60;

    SDL_SetWindowResizable( window, SDL_TRUE );

    /*
     * game
     */

    start_game();

    /*
     * clean up
     */

    close_game();
    free_defs();
    free_level();

    return 0;
}
