#include <stdio.h>
#include <SDL2/SDL.h>
#include "core.h"

/*
 * window stuff
 */

static void handle()
{
    SDL_Event event;
    while ( SDL_PollEvent( &event ) )
    {
        switch ( event.type )
        {
            case SDL_QUIT:

                quit = 1;

                break;

            case SDL_WINDOWEVENT:

                switch ( event.window.event )
                {
                    case SDL_WINDOWEVENT_RESIZED:

                        SDL_GetWindowSize( window, &window_w, &window_h );

                        break;
                }

                break;
        }
    }
}

static void update()
{
    update_loaded_entities();
    update_loaded_objects();
}

static void render()
{
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderClear( renderer );

    float x = 0;
    float y = 0;
    float w = window_w / scale_x;
    float h = window_h / scale_y;
    screen_to_world_f( x, y, &x, &y );

    query_objects_func( x, y, w, h, &render_object );
    query_entities_func( x, y, w, h, &render_entity );

    SDL_RenderPresent( renderer );

    printf( "---------------------------\n" );
    printf( "frame              :%3d\n",            frame );
    printf( "fps_cur            :%3.4f\n",          fps_cur );
    printf( "fps_avg            :%3.4f\n",          fps_avg );
}

static int start_game()
{
    while (!quit)
    {
        unsigned int start = SDL_GetTicks();

        handle();
        update();
        render();

        // apply fps cap
        if ( fps_cap > 0.0f && fps_cap < 1000.0f )
        {
            int delay = ( 1000.0f / fps_cap ) - ( SDL_GetTicks() - start );
            if ( delay > 0.0f )
                SDL_Delay( delay );
        }

        unsigned int end = SDL_GetTicks();

        delta_t = ( float ) ( end - start ) / 1000.0f;
        fps_cur = 1.0f / delta_t;
        fps_avg = ( fps_cur + fps_avg ) / 2.0f;

        frame++;
    }

    return 0;
}

static void init_game()
{
    const char *title = "game";
    int wflags = 0; // window flags
    int rflags = SDL_RENDERER_PRESENTVSYNC; // render flags

    if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
        return;

    window = SDL_CreateWindow( title, 0, 0, window_w, window_h, wflags );

    if ( !window )
    {
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer( window, -1, rflags );

    if ( !renderer )
    {
        SDL_DestroyWindow( window );
        SDL_Quit();
        return;
    }

    SDL_SetWindowResizable( window, SDL_TRUE );
    SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_BLEND );

    keystate = SDL_GetKeyboardState( NULL );

    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderPresent( renderer );
}

static void quit_game()
{
    if ( window )
        SDL_DestroyWindow( window );

    if ( renderer )
        SDL_DestroyRenderer( renderer );

    SDL_Quit();

    window = NULL;
    renderer = NULL;
}

int main()
{
    /*
     * init
     */

    init_game();
    init_core();

    /*
     * start game
     */

    start_game();

    /*
     * clean up
     */

    quit_game();
    free_core();

    return 0;
}
