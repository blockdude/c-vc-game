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

void			window_swap_buf( void );

void   			window_size_set( int w, int h );
void   			window_size( int *w, int *h );

void			window_title_set( const char *title );
const char *	window_title( void );

void			window_flags_set( unsigned int flags, bool state );
unsigned int	window_flags( void );

// get sdl handle
void *			window_handle( void );
float  			window_aspect( void );

#ifdef __cplusplus
}
#endif

static inline void window_flags_toggle( unsigned int flags )
{
	unsigned int z = window_flags();
    unsigned int x = ~z & flags;
    unsigned int y =  z & flags;

    window_flags_set( x, true );
    window_flags_set( y, false );
}

static inline void window_flags_enable( unsigned int flags )
{
	window_flags_set( flags, true );
}

static inline void window_flags_disable( unsigned int flags )
{
	window_flags_set( flags, false );
}

#endif
