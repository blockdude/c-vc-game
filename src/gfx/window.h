#ifndef WINDOW_H
#define WINDOW_H

#include "../util/util.h"

// window function
typedef void ( *window_event_fn )( void );

// window struct
struct window
{
    // sdl stuff
    SDL_Window *handle;
    
    // tracks width and height. not needed but convenient for me
    int w;
    int h;

    // frame timing (delta is in seconds)
    f64 delta;
    u64 fps;
    u64 frame;

    // tick timing (delta is in seconds)
    f64 tdelta;
    u64 tps;
    u64 tick;
};

// global renderer and window
extern SDL_Renderer *renderer;
extern struct window window;

// state
extern bool quit;
extern bool pause;

void window_init( window_event_fn init, window_event_fn close, window_event_fn update, window_event_fn tick, window_event_fn render );
void window_start( void );
void window_close( void );

#endif
