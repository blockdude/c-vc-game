#ifndef VCP_WINDOW_H
#define VCP_WINDOW_H

#include "../common.h"
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

extern int window_init( void );
extern void window_deinit( void );
extern void window_swap_buffer( void );
extern bool window_keep_open( void );
extern struct extent window_size( void );
extern float window_aspect( void );
extern const char *window_title( void );
extern uint32_t window_flags( void );
extern uint32_t window_id( void );
extern void window_set_size( int w, int h );
extern void window_set_title( const char *title );
extern void window_set_flags( uint32_t flags, bool state );
extern void window_toggle_flags( uint32_t flags );
extern void window_enable_flags( uint32_t flags );
extern void window_disable_flags( uint32_t flags );

// INTERNAL USE
// used for input.c to notify window on certain events
#define _WINDOW_NOTIFY_RESIZE 0
#define _WINDOW_NOTIFY_CLOSE 1
extern void _window_notify( int type, int w, int h );

#endif
