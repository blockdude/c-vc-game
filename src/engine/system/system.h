#ifndef SYSTEM_H
#define SYSTEM_H

/*
 * This will be for platform or framework specific funcitons that
 * we can hide behind custom functions for if I decide to move
 * away from sdl.
 */

#include <SDL3/SDL.h>

enum system_status
{
    SYSTEM_ERROR   = -1,
    SYSTEM_SUCCESS =  0
};

#ifdef __cplusplus
extern "C" {
#endif

int system_init( void );
int system_free( void );

#ifdef __cplusplus
}
#endif

#endif
