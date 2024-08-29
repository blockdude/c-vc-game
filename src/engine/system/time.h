#ifndef TIME_H
#define TIME_H

#include <util/types.h>

// units per second.
#define TIMESCALE 1000.0f

#ifdef __cplusplus
extern "C" {
#endif

uint64_t time_now( void );
void time_wait( unsigned int t );

#ifdef __cplusplus
}
#endif

#endif
