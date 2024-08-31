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

int window_size_set( int w, int h );
int window_title_set( const char *title );
int window_relative_mouse( bool state );
int window_relative_mouse_toggle( void );

int window_size_get( int *w, int *h );

// get sdl handle
void *window_handle( void );
float window_aspect( void );

#ifdef __cplusplus
}
#endif

#endif
