#ifndef TIME_H
#define TIME_H

// units per second.
#define TIMESCALE 1.0f

#ifdef __cplusplus
extern "C" {
#endif

float time_ticks( void );
void  time_sleep( float s );

#ifdef __cplusplus
}
#endif

#endif
