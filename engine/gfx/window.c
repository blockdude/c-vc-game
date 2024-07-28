#define SDL_FUNCTION_POINTER_IS_VOID_POINTER
#include "window.h"
#include "render.h"
#include <SDL3/SDL_video.h>
#include <stdalign.h>
#include <system/input.h>
#include <glad/glad.h>

// global window context
struct window window;

#define INIT_TIMING( r ) \
    ( struct timing ) {                             \
		.target_rate	= ( r ),                    \
		.target_delta	= 1000.0 / ( r ),           \
		.rate			= 0,                        \
		.delta			= 0,                        \
		.count			= 0                         \
	}

// used in window_loop only
#define process_event_( fn ) \
    do                                              \
    {                                               \
        int code = window_internal_##fn();          \
        switch ( code )                             \
        {                                           \
            case WINDOW_SUCCESS:   break;           \
            case WINDOW_EXIT:      goto soft_exit_; \
            case WINDOW_HARD_EXIT: goto hard_exit_; \
            default:               goto soft_exit_; \
        };                                          \
    }                                               \
    while ( 0 )

static void resize_callback_( int w, int h )
{
    window.w = w;
    window.h = h;
    window.aspect = ( float )w / ( float )h;
    glViewport( 0, 0, w, h );
}

static void quit_callback_( void )
{
    window.quit = true;
}

// base init
static inline int window_internal_init_( void )
{
    int code = WINDOW_SUCCESS;
    if ( window.state.init )
        code = window.state.init();

    // set callback functions
    input_push_resize_callback( resize_callback_ );
    input_push_quit_callback( quit_callback_ );

    return code;
}

// base clean
static inline int window_internal_free_( void )
{
    int code = WINDOW_SUCCESS;
    if ( window.state.free )
        code = window.state.free();

    return code;
}

// base tick
static inline int window_internal_tick_( void )
{
    int code = WINDOW_SUCCESS;
    if ( window.state.tick )
        code = window.state.tick();
    window.tick.count++;

    return code;
}

// base update
static inline int window_internal_update_( void )
{
    int code = WINDOW_SUCCESS;
    if ( window.state.update )
        code = window.state.update();

    return code;
}

// base render
static inline int window_internal_render_( void )
{
    int code = WINDOW_SUCCESS;
	if ( window.state.render )
        code = window.state.render();

    window.frame.count++;
    SDL_GL_SwapWindow( window.handle );

    return code;
}

int window_init( const struct window_state *state )
{
    // skip init if already done
    if ( window.initialized )
    {
        return WINDOW_ERROR;
    }

    const float default_rate = 60.0f;
    const int window_size = 700;
    const Uint32 window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_OPENGL;

	// init variables
	window.quit = false;
    window.initialized = false;
    window.rel_mouse_mode = false;
	window.state = state != NULL ? *state : ( struct window_state ) { 0 };
	window.frame = INIT_TIMING( default_rate );
	window.tick = INIT_TIMING( default_rate );
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
    log_info( "Creating SDL window" );
    window.handle = SDL_CreateWindow( "Raytracer", window_size, window_size, window_flags );
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
        SDL_GL_DestroyContext( window.context );
        SDL_DestroyWindow( window.handle );
        return WINDOW_ERROR;
    }

    // log opengl info information
    log_debug( "Vendor     : %s", glGetString( GL_VENDOR ) );
    log_debug( "Renderer   : %s", glGetString( GL_RENDERER ) );
    log_debug( "GL Version : %s", glGetString( GL_VERSION ) );
    log_debug( "SL Version : %s", glGetString( GL_SHADING_LANGUAGE_VERSION ) );

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

    log_info( "Starting window loop..." );

	// init
    process_event_( init_ );

	// setup game loop
    uint64_t frame_previous = SDL_GetTicks();
    float tick_time = 0;

    uint64_t tick_last = 0;
    uint64_t frame_last = 0;

    uint64_t frame_timer = frame_previous;

	// begin main loop
    while ( !window.quit )
    {
        // get frame timing
        uint64_t frame_current = SDL_GetTicks();
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
        if ( input_process_events() != 0 )
            goto soft_exit_;
        
        // maintain fixed time step for each tick
        while ( tick_time >= window.tick.target_delta )
        {
            process_event_( tick_ );
            tick_time -= window.tick.target_delta;
        }

        process_event_( update_ );
        process_event_( render_ );

        // calculate & store frame time
        window.frame.delta = ( float ) frame_delta / 1000.0f;

        // apply fps cap
        int delay = frame_current + window.frame.target_delta - SDL_GetTicks();
        if ( delay > 0 )
            SDL_Delay( delay );
    }

soft_exit_:
	window_internal_free_();

hard_exit_:
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
    SDL_GL_DestroyContext( window.context );
    log_info( "Closing SDL window" );
    SDL_DestroyWindow( window.handle );
	window.initialized = false;

    return WINDOW_SUCCESS;
}

int window_set_target_fps( float fps )
{
	window.frame.target_rate = fps;
	window.frame.target_delta = ( fps <= 0.0 ? 1.0 : 1000.0 / ( float ) fps );

	return WINDOW_SUCCESS;
}

int window_set_target_tps( float tps )
{
	window.tick.target_rate = tps;
	window.tick.target_delta = ( tps <= 0.0 ? 0.01 : 1000.0 / ( float ) tps );

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
    window.rel_mouse_mode = state;
    SDL_WarpMouseInWindow( window.handle, window.w / 2, window.h / 2 );
    SDL_SetRelativeMouseMode( state );
    return WINDOW_SUCCESS;
}

int window_toggle_relative_mouse( void )
{
    window.rel_mouse_mode = !window.rel_mouse_mode;
    SDL_WarpMouseInWindow( window.handle, window.w / 2, window.h / 2 );
    SDL_SetRelativeMouseMode( window.rel_mouse_mode );
    return WINDOW_SUCCESS;
}
