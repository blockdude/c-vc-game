#include "window.h"
#include "global.h"
#include "system.h"

#include <SDL3/SDL.h>

void window_swap( void )
{
    SDL_Window *handle = sys_window_handle();
    SDL_GL_SwapWindow( handle );
}

void window_size_set( int w, int h )
{
    SDL_Window *handle = sys_window_handle();
    SDL_SetWindowSize( handle, w, h );
    core.window.width = w;
    core.window.height = h;
}

void window_size( int *w, int *h )
{
    *w = core.window.width;
    *h = core.window.height;
}

void window_title_set( const char *title )
{
    SDL_Window *handle = sys_window_handle();
    SDL_SetWindowTitle( handle, title );
    core.window.title = title;
}

void window_set( unsigned int flags, bool state )
{
    SDL_Window *handle = sys_window_handle();

    core.window.flags = state ?
        core.window.flags | flags :
        core.window.flags & ~flags;

    if ( ( flags & WINDOW_RELATIVE_MOUSE ) > 0 )
    {
        SDL_WarpMouseInWindow( handle, core.window.width / 2.0f, core.window.height / 2.0f );
        SDL_SetWindowRelativeMouseMode( handle, state );
    }

    if ( ( flags & WINDOW_VSYNC ) > 0 )
    {
        SDL_GL_SetSwapInterval( state ? 1 : 0 );
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
