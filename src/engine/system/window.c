#include "window.h"
#include "core-internal.h"

int window_get_size( int *w, int *h )
{
    *w = core.window.w;
    *h = core.window.h;
    return WINDOW_SUCCESS;
}
