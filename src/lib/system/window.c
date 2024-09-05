#include "window.h"
#include "internal/core.h"
#include "internal/sys.h"

void window_swap( void )
{
    sys_swap_screen_buffer();
}

void window_size_set( int w, int h )
{
    sys_window_size_set( w, h );
    core.window.w = w;
    core.window.h = h;
}

void window_size( int *w, int *h )
{
    *w = core.window.w;
    *h = core.window.h;
}

void window_title_set( const char *title )
{
    sys_window_title_set( title );
    core.window.title = title;
}

void window_set( unsigned int flags, bool state )
{
    core.window.flags = state ?
        core.window.flags | flags :
        core.window.flags & ~flags;

    if ( ( flags & WINDOW_RELATIVE_MOUSE ) > 0 )
    {
        sys_window_relative_mouse_set( state );
    }

    if ( ( flags & WINDOW_VSYNC ) > 0 )
    {
        sys_window_vsync_set( state );
    }
}

void window_toggle( unsigned int flags )
{
    unsigned int ef = ~core.window.flags & flags;
    unsigned int df =  core.window.flags & flags;

    window_set( ef, true );
    window_set( df, false );
}

float window_aspect( void )
{
    return core.window.aspect;
}
