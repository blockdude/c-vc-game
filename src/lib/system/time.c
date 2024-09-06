#include "time.h"
#include <SDL3/SDL.h>

float time_ticks( void )
{
    Uint64 ns = SDL_GetTicksNS();
    return ( float ) ns / 1000000000.0f;
}

void  time_sleep( float s )
{
    Uint64 ns = s * 1000000000.0f;
    SDL_DelayNS( ns );
}
