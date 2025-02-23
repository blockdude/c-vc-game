#include "window.h"
#include "../util/log.h"

#include <SDL3/SDL.h>
#include <glad/gl.h>

static struct
{
    bool initialized;
    uint32_t flags;
    char title[ VCP_MAX_STRING_LEN ];
    float aspect;
    int width;
    int height;
    int id;
} g_win_state = { .id = -1, .title = "Application", .width = 700, .height = 700, .aspect = 1.0f };

static struct
{
    SDL_Window *handle;
    SDL_GLContext glcontext;
} g_win_ctx = { 0 };

/*
 * =============================
 * -----------------------------
 * INIT
 * -----------------------------
 */

int window_init( void )
{
    if ( SDL_InitSubSystem( SDL_INIT_VIDEO ) == false )
    {
        log_warn( "Unable to initialize SDL video system: %s", SDL_GetError() );
        goto cleanup;
    }

    SDL_WindowFlags flags = 0;

#ifdef VCP_WINDOW_OPENGL
    flags = SDL_WINDOW_OPENGL;
#endif

    if ( HASFLAG( g_win_state.flags, WINDOW_RESIZABLE ) )
    {
        flags |= SDL_WINDOW_RESIZABLE;
    }

    if ( HASFLAG( g_win_state.flags, WINDOW_FULLSCREEN ) )
    {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    if ( HASFLAG( g_win_state.flags, WINDOW_HIGHDPI ) )
    {
        flags |= SDL_WINDOW_HIGH_PIXEL_DENSITY;
    }

    if ( HASFLAG( g_win_state.flags, WINDOW_RELATIVE_MOUSE ) )
    {
        flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

#ifdef VCP_WINDOW_OPENGL
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 6 );
    SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
#endif

    g_win_ctx.handle = SDL_CreateWindow( g_win_state.title, g_win_state.width, g_win_state.height, flags );
    if ( g_win_ctx.handle == NULL )
    {
        log_warn( "Failed to initialize system. Unable to create SDL window: %s", SDL_GetError() );
        goto cleanup;
    }

#ifdef VCP_WINDOW_OPENGL
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

    SDL_GL_SetSwapInterval( HASFLAG( g_win_state.flags, WINDOW_VSYNC ) ? 1 : 0 );
#endif

    g_win_state.id = SDL_GetWindowID( g_win_ctx.handle );
    g_win_state.initialized = true;

    log_info( "Window ID   : %u", g_win_state.id );

#ifdef VCP_WINDOW_OPENGL
    log_info( "Vendor      : %s", glGetString( GL_VENDOR ) );
    log_info( "Renderer    : %s", glGetString( GL_RENDERER ) );
    log_info( "GL Version  : %s", glGetString( GL_VERSION ) );
    log_info( "SL Version  : %s", glGetString( GL_SHADING_LANGUAGE_VERSION ) );
#endif

    return 0;

cleanup:
#ifdef VCP_WINDOW_OPENGL
    if ( g_win_ctx.glcontext )
        SDL_GL_DestroyContext( g_win_ctx.glcontext );
#endif

    if ( g_win_ctx.handle )
        SDL_DestroyWindow( g_win_ctx.handle );

    g_win_ctx.handle = NULL;
    g_win_ctx.glcontext = NULL;
    return -1;
}

void window_deinit( void )
{
    if ( g_win_state.initialized == false )
        return;

#ifdef VCP_WINDOW_OPENGL
    if ( g_win_ctx.glcontext )
    {
        SDL_GL_DestroyContext( g_win_ctx.glcontext );
        log_info( "Destroyed OpenGL context" );
        g_win_ctx.glcontext = NULL;
    }
#endif

    if ( g_win_ctx.handle )
    {
        SDL_DestroyWindow( g_win_ctx.handle );
        log_info( "Destroyed SDL window" );
        g_win_ctx.handle = NULL;
    }

    SDL_QuitSubSystem( SDL_INIT_VIDEO );
    g_win_state.initialized = false;
}

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * GRAPHICS
 * -----------------------------
 */

void window_swap_buffer( void )
{
#ifdef VCP_WINDOW_OPENGL
    SDL_GL_SwapWindow( g_win_ctx.handle );
#endif
}

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * GETTERS
 * -----------------------------
 */

struct extent window_size( void )
{
    struct extent result = {
        g_win_state.width,
        g_win_state.height
    };

    return result;
}

float window_aspect( void )
{
    return g_win_state.aspect;
}

const char *window_title( void )
{
    return g_win_state.title;
}

uint32_t window_flags( void )
{
    return g_win_state.flags;
}

int window_id( void )
{
    return g_win_state.id;
}

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * SETTERS
 * -----------------------------
 */

void window_set_title( const char *title )
{
    SDL_SetWindowTitle( g_win_ctx.handle, title );
    snprintf( g_win_state.title, VCP_MAX_STRING_LEN, "%s", title );
}

void window_set_size( int w, int h )
{
    SDL_SetWindowSize( g_win_ctx.handle, w, h );
    g_win_state.width = w;
    g_win_state.height = h;
    g_win_state.aspect = ( float ) w / h;

#ifdef VCP_WINDOW_OPENGL
    glViewport( 0, 0, w, h );
#endif
}

void window_set_flags( uint32_t flags, bool state )
{
    g_win_state.flags = state ?
        g_win_state.flags | flags :
        g_win_state.flags & ~flags;

    if ( g_win_state.initialized == false )
        return;

    if ( HASFLAG( flags, WINDOW_RELATIVE_MOUSE ) )
    {
        SDL_WarpMouseInWindow( g_win_ctx.handle, g_win_state.width / 2.0f, g_win_state.height / 2.0f );
        SDL_SetWindowRelativeMouseMode( g_win_ctx.handle, state );
    }

    if ( HASFLAG( flags, WINDOW_VSYNC ) )
    {
#ifdef VCP_WINDOW_OPENGL
        SDL_GL_SetSwapInterval( state ? 1 : 0 );
#endif
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

void window_toggle_flags( uint32_t flags )
{
    uint32_t z = window_flags();
    uint32_t x = ~z & flags;
    uint32_t y =  z & flags;

    window_set_flags( x, true );
    window_set_flags( y, false );
}

void window_enable_flags( uint32_t flags )
{
    window_set_flags( flags, true );
}

void window_disable_flags( uint32_t flags )
{
    window_set_flags( flags, false );
}

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * INTERNAL
 * -----------------------------
 */

void _window_notify( int type, int w, int h )
{
    if ( type == _WINDOW_NOTIFY_RESIZE )
    {
        g_win_state.width = w;
        g_win_state.height = h;
        g_win_state.aspect = ( float ) w / h;

#ifdef VCP_WINDOW_OPENGL
        glViewport( 0, 0, w, h );
#endif
    }

    if ( type == _WINDOW_NOTIFY_CLOSE )
    {
    }
}

/*
 * =============================
 */
