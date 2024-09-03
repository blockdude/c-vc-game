#include "window.h"
#include "core-internal.h"

int window_size_get( int *w, int *h )
{
    *w = core.window.w;
    *h = core.window.h;
    return WINDOW_SUCCESS;
}

float window_aspect( void )
{
    return core.window.aspect;
}
