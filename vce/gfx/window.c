#define SDL_FUNCTION_POINTER_IS_VOID_POINTER
#include "window.h"
#include "render.h"
#include <SDL3/SDL_video.h>
#include <stdalign.h>
#include <system/input.h>
#include <glad/glad.h>

// global window context
struct window window;

static void resize_callback_( int w, int h )
{
    window.w = w;
    window.h = h;
    window.aspect = ( float )w / ( float )h;
    glViewport( 0, 0, w, h );
}

// base init
int window_init( void )
{
    // skip init if already done
    if ( window.initialized )
    {
        return WINDOW_SUCCESS;
    }

    const int window_size = 700;
    const Uint32 window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_OPENGL;

	// init variables
	window.quit = false;
    window.initialized = false;
    window.relative_mouse = false;
    window.w = window_size;
    window.h = window_size;
    window.aspect = 1.f;

    // Request an OpenGL 3.3 context (should be core)
    SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    // Request a depth buffer
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );

    // create sdl2 window
    log_debug( "Creating SDL window" );
    window.handle = SDL_CreateWindow( "Application", window_size, window_size, window_flags );
    if ( !window.handle )
    {
        log_error( "Failed to initialize window. Unable to create SDL window: %s", SDL_GetError() );
        return WINDOW_ERROR;
    }

    // create opengl context
    log_debug( "Creating OpenGL context" );
    window.context = SDL_GL_CreateContext( window.handle );
    if ( !window.context )
    {
        // if we cannot create the gl context then close the window and report an error
        log_error( "Failed to initialize window. Unable to create OpenGL context: %s", SDL_GetError() );
        SDL_DestroyWindow( window.handle );
        return WINDOW_ERROR;
    }

    // init glad library
    log_debug( "Initializing OpenGL" );
    if ( !gladLoadGLLoader( SDL_GL_GetProcAddress ) )
    {
        log_error( "Failed to initialize opengl" );
        SDL_GL_DestroyContext( window.context );
        SDL_DestroyWindow( window.handle );
        return WINDOW_ERROR;
    }

    // log opengl info information
    log_info( "Vendor      : %s", glGetString( GL_VENDOR ) );
    log_info( "Renderer    : %s", glGetString( GL_RENDERER ) );
    log_info( "GL Version  : %s", glGetString( GL_VERSION ) );
    log_info( "SL Version  : %s", glGetString( GL_SHADING_LANGUAGE_VERSION ) );
	log_info( "SDL Version : %d.%d.%d",
			SDL_VERSIONNUM_MAJOR( SDL_VERSION ),
			SDL_VERSIONNUM_MINOR( SDL_VERSION ),
			SDL_VERSIONNUM_MICRO( SDL_VERSION ) );

    input_push_resize_callback( resize_callback_ );

    window.initialized = true;
    return WINDOW_SUCCESS;
}

int window_free( void )
{
    log_debug( "Closing OpenGL context" );
    SDL_GL_DestroyContext( window.context );
    log_debug( "Closing SDL window" );
    SDL_DestroyWindow( window.handle );
	window.initialized = false;

    return WINDOW_SUCCESS;
}

int window_get_size( int *w, int *h )
{
    //SDL_GetWindowSize( window.handle, w, h );
    *w = window.w;
    *h = window.h;
    return WINDOW_SUCCESS;
}

int window_set_title( const char *title )
{
    SDL_SetWindowTitle( window.handle, title );
    return WINDOW_SUCCESS;
}

int window_set_relative_mouse( bool state )
{
    window.relative_mouse = state;
    SDL_WarpMouseInWindow( window.handle, window.w / 2, window.h / 2 );
    SDL_SetRelativeMouseMode( state );
    return WINDOW_SUCCESS;
}

int window_toggle_relative_mouse( void )
{
    window.relative_mouse = !window.relative_mouse;
    SDL_WarpMouseInWindow( window.handle, window.w / 2, window.h / 2 );
    SDL_SetRelativeMouseMode( window.relative_mouse );
    return WINDOW_SUCCESS;
}
