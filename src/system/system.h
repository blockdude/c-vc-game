#ifndef SYSTEM_H
#define SYSTEM_H

/*
 * System initialization
 */

#include <util/types.h>
#include <util/util.h>

enum system_flags
{
	WINDOW = BITFLAG( 0 ),

	/*
	 * Input events are limited if the window is not also initialized.
	 */
	INPUT  = BITFLAG( 1 ),
	AUDIO  = BITFLAG( 2 ),
	TIMER  = BITFLAG( 3 )
};

#ifdef __cplusplus
extern "C" {
#endif

/*
 * General
 */

void   sys_init( unsigned int flags );
void   sys_free( void );

/*
 * Audio
 */

void   sys_audio_init( void );

/*
 * Window
 */

void   sys_window_init( void );
void * sys_window_handle( void );

/*
 * Input
 */

void   sys_input_init( void );

/*
 * Time
 */

void   sys_timer_init( void );

#ifdef __cplusplus
}
#endif

#endif
