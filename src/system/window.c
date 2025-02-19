#include "window.h"
#include "../internal.h"
#include "../util/log.h"

#include <SDL3/SDL.h>
#include <glad/gl.h>

static struct
{
    SDL_Window *handle;
    SDL_GLContext glcontext;
} g_win_ctx = { 0 };

int window_init( void )
{
    if ( SDL_InitSubSystem( SDL_INIT_VIDEO ) != 0 )
    {
        log_warn( "Unable to initialize SDL video system: %s", SDL_GetError() );
        goto cleanup;
    }

    SDL_WindowFlags flags =
        SDL_WINDOW_OPENGL;

    if ( HASFLAG( core.window.flags, WINDOW_RESIZABLE ) )
    {
        flags |= SDL_WINDOW_RESIZABLE;
    }

    if ( HASFLAG( core.window.flags, WINDOW_FULLSCREEN ) )
    {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    if ( HASFLAG( core.window.flags, WINDOW_HIGHDPI ) )
    {
        flags |= SDL_WINDOW_HIGH_PIXEL_DENSITY;
    }

    if ( HASFLAG( core.window.flags, WINDOW_RELATIVE_MOUSE ) )
    {
        flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 6 );
    SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );

    g_win_ctx.handle = SDL_CreateWindow( core.window.title, core.window.width, core.window.height, flags );
    if ( g_win_ctx.handle == NULL )
    {
        log_warn( "Failed to initialize system. Unable to create SDL window: %s", SDL_GetError() );
        goto cleanup;
    }

    g_win_ctx.glcontext = SDL_GL_CreateContext( g_win_ctx.handle );
    if ( g_win_ctx.glcontext == NULL )
    {
        log_warn( "Failed to initialize system. Unable to create OpenGL context: %s", SDL_GetError() );
        goto cleanup;
    }

    if ( !gladLoadGL( ( GLADloadfunc ) SDL_GL_GetProcAddress ) )
    {
        log_warn( "Failed to load opengl functions" );
        goto cleanup;
    }

    SDL_GL_SetSwapInterval( HASFLAG( core.window.flags, WINDOW_VSYNC ) ? 1 : 0 );
    core.window.id = SDL_GetWindowID( g_win_ctx.handle );
    core.window.initialized = true;

    log_info( "Window ID   : %u", core.window.id );
    log_info( "Vendor      : %s", glGetString( GL_VENDOR ) );
    log_info( "Renderer    : %s", glGetString( GL_RENDERER ) );
    log_info( "GL Version  : %s", glGetString( GL_VERSION ) );
    log_info( "SL Version  : %s", glGetString( GL_SHADING_LANGUAGE_VERSION ) );
    return 0;

cleanup:
    if ( g_win_ctx.glcontext )
        SDL_GL_DestroyContext( g_win_ctx.glcontext );

    if ( g_win_ctx.handle )
        SDL_DestroyWindow( g_win_ctx.handle );

    g_win_ctx.handle = NULL;
    g_win_ctx.glcontext = NULL;
    return -1;
}

void window_deinit( void )
{
    if ( core.window.initialized == false )
        return;

    if ( g_win_ctx.glcontext )
    {
        SDL_GL_DestroyContext( g_win_ctx.glcontext );
        log_info( "Destroyed OpenGL context" );
        g_win_ctx.glcontext = NULL;
    }

    if ( g_win_ctx.handle )
    {
        SDL_DestroyWindow( g_win_ctx.handle );
        log_info( "Destroyed SDL window" );
        g_win_ctx.handle = NULL;
    }

    SDL_QuitSubSystem( SDL_INIT_VIDEO );
    core.window.initialized = false;
}

void window_swap_buffer( void )
{
    SDL_GL_SwapWindow( g_win_ctx.handle );
}

void window_size( int *w, int *h )
{
    *w = core.window.width;
    *h = core.window.height;
}

float window_aspect( void )
{
    return core.window.aspect;
}

const char *window_title( void )
{
    return core.window.title;
}

uint32_t window_flags( void )
{
    return core.window.flags;
}

int window_id( void )
{
    return core.window.id;
}

void window_title_set( const char *title )
{
    SDL_SetWindowTitle( g_win_ctx.handle, title );
    snprintf( core.window.title, VCP_MAX_STRING_LEN, "%s", title );
}

void window_size_set( int w, int h )
{
    SDL_SetWindowSize( g_win_ctx.handle, w, h );
    core.window.width = w;
    core.window.height = h;
}

void window_flags_set( uint32_t flags, bool state )
{
    core.window.flags = state ?
        core.window.flags | flags :
        core.window.flags & ~flags;

    if ( !core.window.initialized )
        return;

    if ( HASFLAG( flags, WINDOW_RELATIVE_MOUSE ) )
    {
        SDL_WarpMouseInWindow( g_win_ctx.handle, core.window.width / 2.0f, core.window.height / 2.0f );
        SDL_SetWindowRelativeMouseMode( g_win_ctx.handle, state );
    }

    if ( HASFLAG( flags, WINDOW_VSYNC ) )
    {
        SDL_GL_SetSwapInterval( state ? 1 : 0 );
    }

    if ( HASFLAG( flags, WINDOW_FULLSCREEN ) )
    {
        SDL_SetWindowFullscreen( g_win_ctx.handle, state );
    }

    if ( HASFLAG( flags, WINDOW_HIGHDPI ) )
    {
        log_warn( "Unable to toggle WINDOW_HIGHDPI: Set flag before window initialization." );
    }
}

void window_flags_toggle( uint32_t flags )
{
    uint32_t z = window_flags();
    uint32_t x = ~z & flags;
    uint32_t y =  z & flags;

    window_flags_set( x, true );
    window_flags_set( y, false );
}

void window_flags_enable( uint32_t flags )
{
    window_flags_set( flags, true );
}

void window_flags_disable( uint32_t flags )
{
    window_flags_set( flags, false );
}

void _window_notify( int type, int w, int h )
{
    if ( type == _WINDOW_NOTIFY_RESIZE )
    {
        core.window.width = w;
        core.window.height = h;
        glViewport( 0, 0, core.window.width, core.window.height );
    }

    if ( type == _WINDOW_NOTIFY_CLOSE )
    {
    }
}
