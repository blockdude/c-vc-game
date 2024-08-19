#ifndef WINDOW_H
#define WINDOW_H

#include <util/util.h>
#include <SDL3/SDL.h>

enum window_status
{
	WINDOW_SUCCESS = 0,
	WINDOW_ERROR = 1
};

struct window
{
	// handle to sdl window and opengl context
	SDL_Window *handle;
	// note: glcontext is an alias for void *
	SDL_GLContext context;

	// is the window running
	bool initialized;
	bool relative_mouse;

	// keeps track of width, height and aspect ratio
	int w;
	int h;
	float aspect;
};

#ifdef __cplusplus
extern "C" {
#endif

// global window context (defined in window.c)
extern struct window window;

// window setup and cleanup functions
int window_init( void );
int window_free( void );

// window setters
int window_set_title( const char *title );
int window_set_relative_mouse( bool state );
int window_toggle_relative_mouse( void );

// window getters
int window_get_size( int *w, int *h );

#ifdef __cplusplus
}
#endif

#endif
