#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "core.h"
#include "scene.h"
#include "util.h"

int sel_def;

// window info
int window_w;
int window_h;

SDL_Rect button_view;

// main_scene
scene *main_scene;

// settings
const float camera_speed = 20.0f;
const float zoom_speed = 1.3f;
const int button_view_width = 150;

/*
 * util
 */

int pt_in_rect( int ax, int ay, int bx, int by, int w, int h )
{
    return ( ax >= bx && ax <= bx + w && ay >= by && ay <= by + h );
}

int pt_in_rect_f( int ax, int ay, float bx, float by, float w, float h )
{
    return ( ax >= bx && ax <= bx + w && ay >= by && ay <= by + h );
}

/*
 * window stuff
 */

int render()
{
    /*
     * main view render
     */

    SDL_RenderSetViewport( renderer, &main_view );

    int point[] = { floor( camera.x ), floor( camera.y ) };
    int dim[] = { ceil( main_view.w / scale.x ) + 1, ceil( main_view.h / scale.y ) + 1 };

    int length = 0;
    result *res = query_dim( main_scene, point[ 0 ], point[ 1 ], dim[ 0 ], dim[ 1 ] );
    object *obj = poll_result( res );
    while( obj )
    {
        //SDL_FRect temp;
        //float x, y;
        //get_object_pos( obj, &x, &y );
        //world_to_screen_f( x, y, &temp.x, &temp.y );
        //temp.w = scale.x;
        //temp.h = scale.y;

        //char r, g, b, a;
        //int color = 0xff0000ff;
        //split_color( color, &r, &g, &b, &a );

        //SDL_SetRenderDrawColor( renderer, r, g, b, a );
        //SDL_RenderDrawRectF( renderer, &temp );
        def_list[ 0 ].on_render( obj );

        obj = poll_result( res );
        length++;
    }

    free_result( res );

    /*
     * button view render
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
        int color = 0xff0000ff;
        split_color( color, &r, &g, &b, &a );

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

    if ( pt_in_rect( mouse_screen.x, mouse_screen.y, main_view.x, main_view.y, main_view.w, main_view.h ) )
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

    /*
     * button view handle
     */

    else if ( pt_in_rect( mouse_screen.x, mouse_screen.y, button_view.x, button_view.y, button_view.w, button_view.h ) )
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
                        if ( pt_in_rect_f( mouse_screen.x - button_view.x, mouse_screen.y - button_view.y, button.x, button.y, button.w, button.h ) )
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
     * main view update
     */

    if ( pt_in_rect( mouse_screen.x, mouse_screen.y, main_view.x, main_view.y, main_view.w, main_view.h ) )
    {
        /*
         * panning
         */

        static int prev_mouse_screen_x = 0;
        static int prev_mouse_screen_y = 0;

        if ( ( mouse_state & SDL_BUTTON_MMASK ) != 0)
        {
            camera.x += ( prev_mouse_screen_x - mouse_screen.x ) / scale.x;
            camera.y += ( prev_mouse_screen_y - mouse_screen.y ) / scale.y;
        }

        prev_mouse_screen_x = mouse_screen.x;
        prev_mouse_screen_y = mouse_screen.y;

        if ((keystate[SDL_SCANCODE_W]))
        {
            camera.y -= camera_speed * delta_t;
        }

        if ((keystate[SDL_SCANCODE_S]))
        {
            camera.y += camera_speed * delta_t;
        }

        if ((keystate[SDL_SCANCODE_A]))
        {
            camera.x -= camera_speed * delta_t;
        }

        if ((keystate[SDL_SCANCODE_D]))
        {
            camera.x += camera_speed * delta_t;
        }

        /*
         * place / remove objects
         */

        if ( ( mouse_state & SDL_BUTTON_LMASK ) != 0 )
        {
            object *new_obj = new_object( mouse_world_floor.x, mouse_world_floor.y, sel_def );
            if ( !insert_object_nc( main_scene, new_obj ) )
                free_object( new_obj );
        }

        if ( ( mouse_state & SDL_BUTTON_RMASK ) != 0 )
        {
            result *res = query_point( main_scene, mouse_world_floor.x, mouse_world_floor.y );
            object *obj = poll_result( res );
            remove_object( main_scene, obj );
            free_object( obj );
            free_result( res );
        }
    }

    /*
     * button view update
     */

    else if ( pt_in_rect( mouse_screen.x, mouse_screen.y, button_view.x, button_view.y, button_view.w, button_view.h ) )
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
    printf( "fps                :%3.4f\n", fps_cur );
    printf( "fps_avg            :%3.4f\n", fps_avg );
    printf( "objects            :%3d\n", get_object_count( main_scene ) );
    printf( "objects_rendered   :%3d\n", i );
    printf( "mouse_screen_pos   :%3d, %3d\n", mouse_screen.x, mouse_screen.y );
    printf( "mouse_world_pos    :%3.0f, %3.0f\n", floor( mouse_world.x ), floor( mouse_world.y ) );
    printf( "camera_pos         :%3.0f, %3.0f\n", camera.x, camera.y );
    printf( "scaling            :%3.0f, %3.0f\n", scale.x, scale.y );
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
//void test_memory_leak_points( int w, int h, int c )
//{
//    for ( int i = 0; i < c; i++ )
//    {
//        srand( i );
//        int point[] = { rand() % w - w / 2, rand() % h - h / 2 };
//
//        object *new_obj = new_object( point[ 0 ], point[ 1 ], DEF_WALL );
//        if ( !insert_object( main_scene, new_obj ) )
//            free_object( new_obj );
//    }
//
//    for ( int i = 0; i < c; i++ )
//    {
//        srand( i );
//        int point[] = { rand() % w - w / 2, rand() % h - h / 2 };
//
//        result *res = query_point( main_scene, point[ 0 ], point[ 1 ] );
//        object *obj = poll_result( res );
//        remove_object( main_scene, obj );
//        free_object( obj );
//        free_result( res );
//    }
//}

/*
 * sdl init
 */

int close_game()
{
    if ( window )
        SDL_DestroyWindow(window);

    if ( renderer )
        SDL_DestroyRenderer(renderer);

    SDL_Quit();

    window = NULL;
    renderer = NULL;

    return 0;
}

int init_game(int width, int height, const char *title)
{
    int wflags = 0; // window flags
    int rflags = SDL_RENDERER_PRESENTVSYNC; // render flags

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        return -1;

    window = SDL_CreateWindow(title, 0, 0, width, height, wflags);

    if (!window)
    {
        close_game();
        return -2;
    }

    renderer = SDL_CreateRenderer(window, -1, rflags);

    if (!renderer)
    {
        close_game();
        return -3;
    }

    // init data
    quit = 0;
    pause = 0;
    delta_t = 0;
    fps_cur = 0;
    fps_avg = 0;
    fps_cap = 60;
    mouse_state = SDL_GetMouseState(&mouse_screen.x, &mouse_screen.y);
    keystate = SDL_GetKeyboardState(NULL);

    SDL_RenderPresent(renderer);

    return 0;
}

int handle_events()
{
    while ( SDL_PollEvent( &event ) )
    {
        if ( event.type == SDL_QUIT ) quit = 1;
        handle();
    }

    return 0;
}

int start_game()
{
    unsigned int start, end;
    while (!quit)
    {
        start = SDL_GetTicks();

        // get mouse info
        mouse_state = SDL_GetMouseState( &mouse_screen.x, &mouse_screen.y );
        screen_to_world( mouse_screen.x, mouse_screen.y, &mouse_world.x, &mouse_world.y );
        mouse_world_floor.x = floor( mouse_world.x );
        mouse_world_floor.y = floor( mouse_world.y );

        // do stuff on update
        handle_events();
        update();

        // cap fps
        int delay = ( 1000.0f / fps_cap ) - ( SDL_GetTicks() - start );
        if ( delay > 0 && fps_cap > 0 && fps_cap < 1000.0f )
            SDL_Delay( delay );

        end = SDL_GetTicks();

        // get timing
        delta_t = ( float ) ( end - start ) / 1000.0f;
        fps_cur = 1.0f / delta_t;
        fps_avg = ( fps_cur + fps_avg ) / 2.0f;
    }

    return 0;
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

    init_game( window_w, window_h, "main_scene creation tool" );

    /*
     * post init
     */

    scale.x = 100;
    scale.y = 100;
    camera.x = 0;
    camera.y = 0;
    sel_def = 0;

    fps_cap = 60;

    SDL_SetWindowResizable( window, SDL_TRUE );
    
    /*
     * load main_scene
     */

    load_defs( "" );
    main_scene = load_scene( "world.level" );

    /*
     * game
     */

    start_game();

    /*
     * save main_scene
     */

    //save_scene( main_scene, "world.level" );

    /*
     * clean up
     */

    close_game();
    free_scene( main_scene );

    return 0;
}
