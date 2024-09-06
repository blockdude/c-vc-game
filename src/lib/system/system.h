#ifndef SYSTEM_H
#define SYSTEM_H

/*
 * System initialization
 */

#include <util/types.h>

enum system_flags
{
	WINDOW = 0x01,

	/*
	 * Input events are limited if the window is not also initialized.
	 */
	INPUT  = 0x02,

	AUDIO  = 0x04,
	TIMER  = 0x08
};

#ifdef __cplusplus
extern "C" {
#endif

/*
 * General
 */

void   sys_init( unsigned int flags );
void   sys_free( void );
void   sys_quit( void );

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
