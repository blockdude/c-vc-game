#ifndef TIME_H
#define TIME_H

#include "internal/sys.h"
#include <util/types.h>

// units per second.
#define TIMESCALE 1.0f

#ifdef __cplusplus
extern "C" {
#endif

float time_now( void )
{
    return sys_ticks();
}

void  time_sleep( float s )
{
    sys_sleep( s );
}

#ifdef __cplusplus
}
#endif

#endif
