#ifndef VCP_WINDOW_H
#define VCP_WINDOW_H

#include "../util/bitflag.h"
#include "../util/types.h"

enum window_flags
{
	WINDOW_RELATIVE_MOUSE = BITFLAG( 0 ),
	WINDOW_VSYNC          = BITFLAG( 1 ),
	WINDOW_FULLSCREEN	  = BITFLAG( 2 ),
	WINDOW_RESIZABLE	  = BITFLAG( 3 ),
	WINDOW_HIGHDPI        = BITFLAG( 4 )
};

int window_init( void );
void window_deinit( void );
void window_swap_buffer( void );
void window_size( int *w, int *h );
float window_aspect( void );
const char *window_title( void );
uint32_t window_flags( void );
int window_id( void );
void window_size_set( int w, int h );
void window_title_set( const char *title );
void window_flags_set( uint32_t flags, bool state );
void window_flags_toggle( uint32_t flags );
void window_flags_enable( uint32_t flags );
void window_flags_disable( uint32_t flags );

// INTERNAL USE
// used for input.c to notify window on certain events
#define _WINDOW_NOTIFY_RESIZE 0
#define _WINDOW_NOTIFY_CLOSE 1
void _window_notify( int type, int w, int h );

#endif
