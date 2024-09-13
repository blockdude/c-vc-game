#include "time.h"
#include <SDL3/SDL.h>

double time_ticks( void )
{
    Uint64 t = SDL_GetTicksNS();
    return ( float ) t / 1000000000.0;
}

void time_delay( double s )
{
    Uint64 t = s * 1000000000.0;
    SDL_DelayNS( t );
}
