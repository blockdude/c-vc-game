#ifndef WINDOW_H
#define WINDOW_H

#include "util.h"

// window function
typedef void ( *WF )();

struct Window
{
    // stuff
    SDL_Window *handle;
    
    int w;
    int h;

    // frame timing (delta is in seconds)
    f64 fdelta;
    f64 fps;
    u64 frame;

    // tick timing (delta is in seconds)
    f64 tdelta;
    f64 tps;
    u64 tick;
};

// global renderer and window
extern SDL_Renderer *renderer;
extern struct Window window;

// state
extern bool quit;
extern bool pause;

void window_init( WF init, WF close, WF update, WF tick, WF render );
void window_start();
void window_close();

#endif
