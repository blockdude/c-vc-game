#include "window.h"
#include "SDL3/SDL_video.h"
#include "core.h"

#include <glad/glad.h>
#include <util/log.h>

int window_init( void )
{
    const int window_size = 700;

	// init variables
    core.window.initialized = false;
    core.window.relative_mouse = false;
    core.window.w = window_size;
    core.window.h = window_size;
    core.window.aspect = 1.f;

    const SDL_WindowFlags window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_OPENGL;

    // Request an OpenGL 4.6 context (should be core)
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 6 );
    SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );

    // Request a depth buffer
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );

    // create sdl2 window
    core.platform.window = SDL_CreateWindow( "Application", core.window.w, core.window.h, window_flags );
    if ( !core.platform.window )
    {
        log_error( "Failed to initialize core.window. Unable to create SDL window: %s", SDL_GetError() );
        return WINDOW_ERROR;
    }
    log_trace( "Created SDL window" );

    // create opengl context
    core.platform.glcontext = SDL_GL_CreateContext( core.platform.window );
    if ( !core.platform.glcontext )
    {
        // if we cannot create the gl context then close the window and report an error
        log_error( "Failed to initialize core.window. Unable to create OpenGL context: %s", SDL_GetError() );
        SDL_DestroyWindow( core.platform.window );
        return WINDOW_ERROR;
    }
    log_trace( "Created OpenGL context" );

    // init glad library
    if ( !gladLoadGLLoader( ( GLADloadproc ) SDL_GL_GetProcAddress ) )
    {
        log_error( "Failed to initialize opengl" );
        SDL_GL_DestroyContext( core.platform.glcontext );
        SDL_DestroyWindow( core.platform.window );
        return WINDOW_ERROR;
    }
    log_trace( "Initialized OpenGL" );

    // log opengl info information
    log_info( "Window successfully created" );
    log_info( "Vendor      : %s", glGetString( GL_VENDOR ) );
    log_info( "Renderer    : %s", glGetString( GL_RENDERER ) );
    log_info( "GL Version  : %s", glGetString( GL_VERSION ) );
    log_info( "SL Version  : %s", glGetString( GL_SHADING_LANGUAGE_VERSION ) );
	log_info( "SDL Version : %d.%d.%d",
			SDL_VERSIONNUM_MAJOR( SDL_VERSION ),
			SDL_VERSIONNUM_MINOR( SDL_VERSION ),
			SDL_VERSIONNUM_MICRO( SDL_VERSION ) );


    core.window.initialized = true;
    return WINDOW_SUCCESS;
}

int window_free( void )
{
    log_info( "Closing OpenGL context" );
    SDL_GL_DestroyContext( core.platform.glcontext );
    log_info( "Closing SDL window" );
    SDL_DestroyWindow( core.platform.window );
	core.window.initialized = false;

    return WINDOW_SUCCESS;
}

void window_swap( void )
{
    SDL_GL_SwapWindow( core.platform.window );
}

int window_get_size( int *w, int *h )
{
    *w = core.window.w;
    *h = core.window.h;
    return WINDOW_SUCCESS;
}

int window_set_title( const char *title )
{
    SDL_SetWindowTitle( core.platform.window, title );
    return WINDOW_SUCCESS;
}

int window_set_relative_mouse( bool state )
{
    core.window.relative_mouse = state;
    SDL_WarpMouseInWindow( core.platform.window, ( float ) core.window.w / 2.0f, ( float ) core.window.h / 2.0f );
    SDL_SetWindowRelativeMouseMode( core.platform.window , state );
    return WINDOW_SUCCESS;
}

int window_toggle_relative_mouse( void )
{
    core.window.relative_mouse = !core.window.relative_mouse;
    SDL_WarpMouseInWindow( core.platform.window , ( float ) core.window.w / 2.0f, ( float ) core.window.h / 2.0f );
    SDL_SetWindowRelativeMouseMode( core.platform.window , core.window.relative_mouse );
    return WINDOW_SUCCESS;
}
