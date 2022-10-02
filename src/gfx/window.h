#ifndef WINDOW_H
#define WINDOW_H

#include "../util/util.h"
#include <SDL2/SDL.h>

#define WINDOW_SUCCESS	0
#define WINDOW_ERROR	-1

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
	// target cycles per second
	int target_rate;
	
	// target milliseconds per cycle
	f64 target_delta;

	// cycles per second (updated every second)
	int rate;

	// seconds per cycle (updated every cycle)
	f64 delta;

	// # of cycles that have occurred
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

// window setup and cleanup functions
int window_init( struct window_state *state );
int window_start( void );
int window_close( void );

// window setters
int window_set_state( struct window_state *state );
int window_set_target_fps( int fps );
int window_set_target_tps( int tps );

// window getters
int window_get_size( int *w, int *h );
int window_get_fps( void );
int window_get_tps( void );

// window events
int window_event_resized( void );
int window_event_moved( void );

#endif
