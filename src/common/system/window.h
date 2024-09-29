#ifndef WINDOW_H
#define WINDOW_H

#include <util/types.h>
#include <util/util.h>

enum window_status
{
	WINDOW_SUCCESS = 0,
	WINDOW_ERROR   = 1
};

enum window_flags
{
	WINDOW_RELATIVE_MOUSE = BITFLAG( 0 ),
	WINDOW_VSYNC          = BITFLAG( 1 ),
	WINDOW_FULLSCREEN	  = BITFLAG( 2 ),
	WINDOW_RESIZABLE	  = BITFLAG( 3 ),
	WINDOW_HIGHDPI        = BITFLAG( 4 )
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
