#include "window.h"
#include "render.h"
#include <system/input.h>
#include <glad/glad.h>

#define init_timing( r ) \
    ( struct timing ) {                             \
		.target_rate	= ( r ),                    \
		.target_delta	= 1000.0 / ( r ),           \
		.rate			= 0,                        \
		.delta			= 0,                        \
		.count			= 0                         \
	}

// global window context
struct window window;

// base init
static int window_internal_init( void )
{
    if ( window.state.init )
        window.state.init();

    return WINDOW_SUCCESS;
}

// base clean
static int window_internal_free( void )
{
    if ( window.state.free )
        window.state.free();

    return WINDOW_SUCCESS;
}

// base tick
static int window_internal_tick( void )
{
    if ( window.state.tick )
        window.state.tick();
    window.tick.count++;

    return WINDOW_SUCCESS;
}

// base update
static int window_internal_update( void )
{
    if ( window.state.update )
        window.state.update();

    return WINDOW_SUCCESS;
}

// base render
static int window_internal_render( void )
{
	if ( window.state.render )
        window.state.render();
    window.frame.count++;

    return WINDOW_SUCCESS;
}

int window_init( struct window_state *state )
{
    // skip init if already done
    if ( window.initialized )
    {
        return WINDOW_ERROR;
    }

    const double default_rate = 60.0;
    const int window_size = 700;
    const Uint32 window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL;

	// init variables
	window.quit = false;
	window.state = state == NULL ? ( struct window_state ) { 0 } : *state;
	window.frame = init_timing( default_rate );
	window.tick = init_timing( default_rate );

    // Request an OpenGL 3.3 context (should be core)
    SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    // Request a depth buffer
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );

    // create sdl2 window
    log_info( "Creating SDL window" );
    window.handle = SDL_CreateWindow( "game engine", 0, 0, window_size, window_size, window_flags );
    if ( !window.handle )
    {
        log_error( "Failed to initialize window. Unable to create SDL window: %s", SDL_GetError() );
        return WINDOW_ERROR;
    }

    // create opengl context
    log_info( "Creating OpenGL context" );
    window.context = SDL_GL_CreateContext( window.handle );
    if ( !window.context )
    {
        // if we cannot create the gl context then close the window and report an error
        log_error( "Failed to initialize window. Unable to create OpenGL context: %s", SDL_GetError() );
        SDL_DestroyWindow( window.handle );
        return WINDOW_ERROR;
    }

    // init glad library
    log_info( "Initializing OpenGL" );
    if ( !gladLoadGLLoader( SDL_GL_GetProcAddress ) )
    {
        log_error( "Failed to initialize opengl" );
        SDL_GL_DeleteContext( window.context );
        SDL_DestroyWindow( window.handle );
        return WINDOW_ERROR;
    }

    // log opengl info information
    log_info( "Vendor     : %s", glGetString( GL_VENDOR ) );
    log_info( "Renderer   : %s", glGetString( GL_RENDERER ) );
    log_info( "GL Version : %s", glGetString( GL_VERSION ) );
    log_info( "SL Version : %s", glGetString( GL_SHADING_LANGUAGE_VERSION ) );

    window.initialized = true;
    return WINDOW_SUCCESS;
}

int window_loop( void )
{
    // sanity check
    if ( !window.initialized )
    {
        log_error( "Window not initialized" );
        return WINDOW_ERROR;
    }

	// init
    window_internal_init();

	// setup game loop
    uint64_t frame_previous = SDL_GetTicks64();
    double tick_time = 0;

    uint64_t tick_last = 0;
    uint64_t frame_last = 0;

    uint64_t frame_timer = frame_previous;

	// begin main loop
    while ( !window.quit )
    {
        // get frame timing
        uint64_t frame_current = SDL_GetTicks64();
        uint64_t frame_delta = frame_current - frame_previous;

        // update fps & tps every second
        if ( frame_current - frame_timer >= 1000 )
        {
            // get variables
            uint64_t ticks = window.tick.count - tick_last;
            uint64_t frames = window.frame.count - frame_last;

            // store rate per second
            window.frame.rate = frames;
            window.tick.rate = ticks;

            // store this frame/tick
            tick_last = window.tick.count;
            frame_last = window.frame.count;

            // reset timer
            frame_timer = frame_current;
        }

        frame_previous = frame_current;
        tick_time += frame_delta;

        // poll events
        window.quit = input_process_events();
        
        // maintain fixed time stamp
        while ( tick_time >= window.tick.target_delta )
        {
            window_internal_tick();
            tick_time -= window.tick.target_delta;
        }

        window_internal_update();
        window_internal_render();

        // convert & store frame timing of current frame
        window.frame.delta = ( double ) frame_delta / 1000.0;

        // apply fps cap
        int delay = frame_current + window.frame.target_delta - SDL_GetTicks64();
        if ( delay > 0 )
            SDL_Delay( delay );
    }

	// clean up
	window_internal_free();

    return WINDOW_SUCCESS;
}

int window_quit( void )
{
    window.quit = true;
    return WINDOW_SUCCESS;
}

int window_free( void )
{
    log_info( "Closing OpenGL context" );
    SDL_GL_DeleteContext( window.context );
    log_info( "Closing SDL window" );
    SDL_DestroyWindow( window.handle );
	window.initialized = false;

    return WINDOW_SUCCESS;
}

int window_set_target_fps( int fps )
{
	window.frame.target_rate = fps;
	window.frame.target_delta = ( fps <= 0.0 ? 1.0 : 1000.0 / ( double ) fps );

	return WINDOW_SUCCESS;
}

int window_set_target_tps( int tps )
{
	window.tick.target_rate = tps;
	window.tick.target_delta = ( tps <= 0.0 ? 0.01 : 1000.0 / ( double ) tps );

	return WINDOW_SUCCESS;
}

int window_get_size( int *w, int *h )
{
    SDL_GetWindowSize( window.handle, w, h );
    return WINDOW_SUCCESS;
}

int window_set_title( const char *title )
{
    SDL_SetWindowTitle( window.handle, title );
    return WINDOW_SUCCESS;
}
