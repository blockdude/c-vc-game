#include "window.h"
#include "global.h"
#include "system.h"

#include <util/log.h>
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
    core.window.flags = state ?
        core.window.flags | flags :
        core.window.flags & ~flags;

    if ( !core.window.initialized )
        return;

    SDL_Window *handle = sys_window_handle();

    if ( HASFLAG( flags, WINDOW_RELATIVE_MOUSE ) )
    {
        SDL_WarpMouseInWindow( handle, core.window.width / 2.0f, core.window.height / 2.0f );
        SDL_SetWindowRelativeMouseMode( handle, state );
    }

    if ( HASFLAG( flags, WINDOW_VSYNC ) )
    {
        SDL_GL_SetSwapInterval( state ? 1 : 0 );
    }

    if ( HASFLAG( flags, WINDOW_FULLSCREEN ) )
    {
        SDL_SetWindowFullscreen( handle, state );
    }

    if ( HASFLAG( flags, WINDOW_HIGHDPI ) )
    {
        log_warn( "Unable to set WINDOW_HIGHDPI: Unsupported feature in SDL." );
    }
}

void window_toggle( unsigned int flags )
{
    unsigned int enableflags  = ~core.window.flags & flags;
    unsigned int disableflags =  core.window.flags & flags;

    window_set( enableflags, true );
    window_set( disableflags, false );
}

float window_aspect( void )
{
    return core.window.aspect;
}
