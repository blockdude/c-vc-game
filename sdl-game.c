#include "sdl-game.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;
float delta_t;
float fps;
float max_fps;
char quit;
char pause;
const unsigned char *keystate;

int init_game(int width, int height, const char *title)
{
    int wflags = 0; // window flags
    int rflags = 0; // render flags

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
    max_fps = 60;
    fps = 0;
    keystate = SDL_GetKeyboardState(NULL);

    SDL_RenderPresent(renderer);

    return 0;
}

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

        handle_events();
        update();

        if ( max_fps > 0 && max_fps < 1000.0f )
            SDL_Delay( ( 1000.0f / max_fps ) - ( SDL_GetTicks() - start ) );

        end = SDL_GetTicks();

        delta_t = ( float ) ( end - start ) / 1000.0f;
        fps = 1.0f / delta_t;
    }

    return 0;
}
