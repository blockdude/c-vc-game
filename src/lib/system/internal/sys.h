#ifndef SYSTEM_H
#define SYSTEM_H

/*
 * Platform specific functions.
 */

#include <util/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * General
 */

void  sys_init( void );
void  sys_free( void );
void  sys_quit( void );

/*
 * Audio
 */

void  sys_init_audio( void );

/*
 * Window
 */

void  sys_init_window( void );
void  sys_swap_screen_buffer( void );
void  sys_window_size_set( int w, int h );
void  sys_window_title_set( const char *title );
void  sys_window_relative_mouse_set( bool state );
void  sys_window_vsync_set( bool state );

/*
 * Input
 */

void  sys_init_input( void );
int   sys_poll_events( void );

/*
 * Time
 */

void  sys_init_timer( void );
float sys_ticks( void );
void  sys_sleep( float );

#ifdef __cplusplus
}
#endif

#endif
