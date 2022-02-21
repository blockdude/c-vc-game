#include "sdl-game.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;
float delta_t;
float fps;
float fps_avg;
float fps_cap;
char quit;
char pause;
int mouse_x;
int mouse_y;
int mouse_state;
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
    fps = 0;
    fps_avg = 0;
    fps_cap = 60;
    mouse_state = SDL_GetMouseState( &mouse_x, &mouse_y );
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

        mouse_state = SDL_GetMouseState( &mouse_x, &mouse_y );

        handle_events();
        update();

        if ( fps_cap > 0 && fps_cap < 1000.0f )
            SDL_Delay( ( 1000.0f / fps_cap ) - ( SDL_GetTicks() - start ) );

        end = SDL_GetTicks();

        delta_t = ( float ) ( end - start ) / 1000.0f;
        fps = 1.0f / delta_t;
        fps_avg = ( fps + fps_avg ) / 2.0f;
    }

    return 0;
}
