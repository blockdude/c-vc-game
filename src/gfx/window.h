#ifndef WINDOW_H
#define WINDOW_H

#include <util/util.h>
#include <SDL2/SDL.h>

#define WINDOW_SUCCESS	0
#define WINDOW_ERROR	-1

// window function
typedef int ( *window_fn )( void );

// game states
struct window_state
{
	window_fn init;
	window_fn free;
	window_fn tick;
	window_fn update;
	window_fn render;
};

// track timing of frame and tick
struct timing
{
	// target cycles per second
	int target_rate;
	
	// target milliseconds per cycle
	double target_delta;

	// cycles per second (updated every second)
	int rate;

	// seconds per cycle (updated every cycle)
	double delta;

	// # of cycles that have occurred
	uint64_t count;
};

// window struct
struct window
{
	// handle to sdl window and opengl context
	SDL_Window *handle;
	SDL_GLContext context;
	// note: glcontext is an alias for void *

	// is the window running
	bool quit;
	bool initialized;

	// store window state
	struct window_state state;

	// store timings
	struct timing frame;
	struct timing tick;

	// unused for now
	int w;
	int h;
};

// global window because only one window should be opened for this game anyways
extern struct window window;

// window setup and cleanup functions
int window_init( struct window_state *state );
int window_loop( void );
int window_quit( void );
int window_free( void );

// window setters
int window_set_state( struct window_state *state );
int window_set_target_fps( int fps );
int window_set_target_tps( int tps );
int window_set_title( const char *title );

// window getters
int window_get_size( int *w, int *h );
int window_get_fps( void );
int window_get_tps( void );

// window events
int window_event_resized( void );
int window_event_moved( void );

#endif
