#include "sdl-game.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

float delta_t;
float fps_cur;
float fps_avg;
float fps_cap;

char quit;
char pause;

int mouse_state;
const unsigned char *keystate;

// mouse pos
SDL_Point mouse_screen;
SDL_FPoint mouse_world;
SDL_Point mouse_world_floor;

SDL_FPoint scale;
SDL_FPoint camera;

// viewports
SDL_Rect main_view;

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

/*
 * util
 */

void screen_to_world( int screen_x, int screen_y, float *world_x, float *world_y )
{
    *world_x = ( float ) ( screen_x / scale.x + camera.x );
    *world_y = ( float ) ( screen_y / scale.y + camera.y );
}

void world_to_screen( float world_x, float world_y, int *screen_x, int *screen_y )
{
    *screen_x = ( int ) ( ( world_x - camera.x ) * scale.x );
    *screen_y = ( int ) ( ( world_y - camera.y ) * scale.y );
}

void screen_to_world_f( float screen_x, float screen_y, float *world_x, float *world_y )
{
    *world_x = ( float ) ( screen_x / scale.x + camera.x );
    *world_y = ( float ) ( screen_y / scale.y + camera.y );
}

void world_to_screen_f( float world_x, float world_y, float *screen_x, float *screen_y )
{
    *screen_x = ( float ) ( ( world_x - camera.x ) * scale.x );
    *screen_y = ( float ) ( ( world_y - camera.y ) * scale.y );
}

void draw_circle_screen( SDL_Renderer *renderer, float x0, float y0, float radius )
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

void draw_circle_world( SDL_Renderer *renderer, float x, float y, float r )
{
    world_to_screen_f( x, y, &x, &y );
    r = r * scale.x;

    draw_circle_screen( renderer, x, y, r );
}

void draw_rect_world( SDL_Renderer *renderer, SDL_FRect *rect )
{
    world_to_screen_f( rect->x, rect->y, &rect->x, &rect->y );
    rect->w = rect->w * scale.x;
    rect->h = rect->h * scale.y;

    SDL_RenderDrawRectF( renderer, rect );
}

void fill_rect_world( SDL_Renderer *renderer, SDL_FRect *rect )
{
    world_to_screen_f( rect->x, rect->y, &rect->x, &rect->y );
    rect->w = rect->w * scale.x;
    rect->h = rect->h * scale.y;

    SDL_RenderFillRectF( renderer, rect );
}
