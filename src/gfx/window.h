#ifndef WINDOW_H
#define WINDOW_H

#include <util/util.h>
#include <SDL2/SDL.h>

#define WINDOW_SUCCESS	 0
#define WINDOW_ERROR	-1
#define WINDOW_EXIT      1
#define WINDOW_HARD_EXIT 2

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
	float target_rate;
	
	// target milliseconds per cycle
	float target_delta;

	// cycles per second (updated every second)
	int rate;

	// seconds per cycle (updated every cycle)
	float delta;

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

	// keeps track of width, height and aspect ratio
	int w;
	int h;
	float aspect;
};

// global window context (defined in window.c)
extern struct window window;

// window setup and cleanup functions
int window_init( const struct window_state *state );
int window_loop( void );
int window_quit( void );
int window_free( void );

// window setters
int window_set_state( const struct window_state *state );
int window_set_target_fps( float fps );
int window_set_target_tps( float tps );
int window_set_title( const char *title );

// window getters
int window_get_size( int *w, int *h );
int window_get_fps( void );
int window_get_tps( void );

#endif
