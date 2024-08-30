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

void window_state_set( unsigned int flags );
void window_state_clear( unsigned int flags );

void window_swap( void );

int window_set_size( int w, int h );
int window_set_title( const char *title );
int window_relative_mouse( bool state );
int window_relative_mouse_toggle( void );

int window_get_size( int *w, int *h );

// get sdl handle
void *window_get_handle( void );

#ifdef __cplusplus
}
#endif

#endif
