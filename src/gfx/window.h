#ifndef WINDOW_H
#define WINDOW_H

#include "../util/util.h"
#include <SDL2/SDL.h>

// window function
typedef int ( *window_event_fn )( void );

// window struct
struct window
{
	// handle to sdl window
	SDL_Window *handle;

	struct
	{
		// runs once when window_loop is called
		window_event_fn init;

		// runs when window exits or events change
		window_event_fn quit;

		// runs every frame
		window_event_fn update;

		// runs every tick
		window_event_fn tick;

		// runs after every update
		window_event_fn render;
	} event;

	// better run
	bool running;

	struct
	{
		// target frame rate
		int target_rate;

		// frames per second
		int rate;

		// seconds per frame
		f64 delta;

		// frame count
		u64 count;
	} frame;

	struct
	{
		// target frame rate
		int target_rate;

		// ticks per second
		int rate;

		// seconds per tick ( should be static )
		f64 delta;
		
		// tick count
		u64 count;
	} tick;
};

// global renderer and window
extern SDL_Renderer *renderer;
// global window i guess
extern struct window window;

int window_init( window_event_fn init, window_event_fn quit, window_event_fn update, window_event_fn tick, window_event_fn render );
int window_loop( void );
int window_quit( void );

// change all event functions. used when switching game states.
int window_set_event_fn( window_event_fn init, window_event_fn clean, window_event_fn update, window_event_fn tick, window_event_fn render );

// change target frame rate
int window_set_target_frame_rate( unsigned int rate );

// change target tick rate (avoid changing tick rate)
int window_set_target_tick_rate( unsigned int rate );

// get window width and height
int window_get_size( int *w, int *h );

#endif
