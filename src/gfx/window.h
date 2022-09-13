#ifndef WINDOW_H
#define WINDOW_H

#include "../util/util.h"
#include <SDL2/SDL.h>

extern const char *g_window_title;
extern const u32 g_window_flags;

// window function
typedef int ( *window_event_fn )( void );

// game states
struct window_state
{
	window_event_fn init;
	window_event_fn free;
	window_event_fn update;
	window_event_fn tick;
	window_event_fn render;
};

// track timing of frame and tick
struct timing
{
	int target_rate;
	int rate;
	f64 delta;
	u64 count;
};

// window struct
struct window
{
	// handle to sdl window
	SDL_Window *handle;

	// is the window running
	bool running;

	// store window state
	struct window_state state;

	// store timings
	struct timing frame;
	struct timing tick;
};

// global window because only one window should be opened for this game anyways
extern struct window window;

// init window and open it
int window_init( struct window_state *state );

// start main loop
int window_start( void );

// close window and free memory
int window_close( void );

// change all event functions. used when switching game states.
int window_set_state( struct window_state *state );

// change target frame rate
int window_set_target_frame_rate( unsigned int rate );

// change target tick rate (avoid changing tick rate)
int window_set_target_tick_rate( unsigned int rate );

// get window width and height
int window_get_size( int *w, int *h );

#endif
