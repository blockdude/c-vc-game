#ifndef WINDOW_H
#define WINDOW_H

#include <util/types.h>

enum window_status
{
	WINDOW_SUCCESS = 0,
	WINDOW_ERROR   = 1
};

#ifdef __cplusplus
extern "C" {
#endif

int window_init( void );
int window_free( void );

// swap the screen buffer
void window_swap( void );

// window setters
int window_set_size( int w, int h );
int window_set_title( const char *title );
int window_set_relative_mouse( bool state );
int window_toggle_relative_mouse( void );

// window getters
int window_get_size( int *w, int *h );

// get the sdl handle
void *window_get_handle( void );

#ifdef __cplusplus
}
#endif

#endif
