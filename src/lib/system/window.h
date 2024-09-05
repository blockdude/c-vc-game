#ifndef WINDOW_H
#define WINDOW_H

#include <util/types.h>

enum window_status
{
	WINDOW_SUCCESS = 0,
	WINDOW_ERROR   = 1
};

enum window_flags
{
	WINDOW_RELATIVE_MOUSE = 0x01,
	WINDOW_VSYNC          = 0x02
};

#ifdef __cplusplus
extern "C" {
#endif

void   window_swap( void );

void   window_size_set( int w, int h );
void   window_title_set( const char *title );
void   window_set( unsigned int flags, bool state );
void   window_toggle( unsigned int flags );

void   window_size( int *w, int *h );

// get sdl handle
void * window_handle( void );
float  window_aspect( void );

#ifdef __cplusplus
}
#endif

#endif
