#include "window.h"
#include "render.h"
#include "../input/input.h"

// global variables
struct window window;

// window stuff
const char *g_window_title = "window";
const u32 g_window_flags = SDL_WINDOW_RESIZABLE;

// base handle
static int window_general_handle( void )
{
    SDL_Event event;
    while ( SDL_PollEvent( &event ) )
    {
        switch ( event.type )
        {
            case SDL_QUIT:
                window.running = false;
                break;
        }

        input_handle( &event );
    }

    return WINDOW_SUCCESS;
}

// base init
static int window_general_init( void )
{
    if ( window.state.init ) window.state.init();
    input_init();

    return WINDOW_SUCCESS;
}

// base clean
static int window_general_free( void )
{
    if ( window.state.free ) window.state.free();

    return WINDOW_SUCCESS;
}

// base update
static int window_general_update( void )
{
    if ( window.state.update ) window.state.update();
    input_update();

    return WINDOW_SUCCESS;
}

// base tick
static int window_general_tick( void )
{
    if ( window.state.tick ) window.state.tick();
    window.tick.count++;

    return WINDOW_SUCCESS;
}

// base render
static int window_general_render( void )
{
	if ( window.state.render ) window.state.render();
    window.frame.count++;

    return WINDOW_SUCCESS;
}

int window_init( struct window_state *state )
{
	// init variables
	window.running = true;

	if ( state == NULL )
		window.state = ( struct window_state ) { 0 };
	else
		window.state = *state;

	window.frame = ( struct timing ) {
		.target_rate	= 60,
		.target_delta	= 1000.0 / 60.0,
		.rate			= 0,
		.delta			= 0,
		.count			= 0
	};

	window.tick = ( struct timing ) {
		.target_rate	= 60,
		.target_delta	= 1000.0 / 60.0,
		.rate			= 0,
		.delta			= 0,
		.count			= 0
	};

	// sdl init and make window
    if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
        return WINDOW_ERROR;

    window.handle = SDL_CreateWindow( g_window_title, 0, 0, 700, 700, g_window_flags );
    if ( !window.handle )
    {
        SDL_Quit();
        return WINDOW_ERROR;
    }

    return WINDOW_SUCCESS;
}

int window_start( void )
{
	// init
    window_general_init();

	// setup game loop
    u64 frame_previous = SDL_GetTicks64();
    f64 tick_time = 0;

    u64 tick_last = 0;
    u64 frame_last = 0;

    u64 frame_timer = frame_previous;

	// begin main loop
    while ( window.running )
    {
        // get frame timing
        u64 frame_current = SDL_GetTicks64();
        u64 frame_delta = frame_current - frame_previous;

        // update fps & tps every second
        if ( frame_current - frame_timer >= 1000 )
        {
            // get variables
            u64 ticks = window.tick.count - tick_last;
            u64 frames = window.frame.count - frame_last;

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

        window_general_handle();

        // do ticks and maintain tick rate
        while( tick_time >= window.tick.target_delta )
        {
            window_general_tick();
            tick_time -= window.tick.target_delta;
        }

        window_general_update();
        window_general_render();

        // convert & store frame timing of current frame
        window.frame.delta = ( f64 ) frame_delta / 1000.0;

        // apply fps cap
        int delay = frame_current + window.frame.target_delta - SDL_GetTicks64();
        if ( delay > 0 ) SDL_Delay( delay );
    }

	// clean up
	window_general_free();

    return WINDOW_SUCCESS;
}

int window_close( void )
{
    SDL_DestroyWindow( window.handle );
    SDL_Quit();

	// reset window
	window = ( struct window ){ 0 };

    return WINDOW_SUCCESS;
}

int window_set_target_fps( int fps )
{
	window.frame.target_rate = fps;
	window.frame.target_delta = ( fps <= 0.0 ? 1.0 : 1000.0 / ( f64 ) fps );

	return 0;
}

int window_set_target_tps( int tps )
{
	window.tick.target_rate = tps;
	window.tick.target_delta = ( tps <= 0.0 ? 0.01 : 1000.0 / ( f64 ) tps );

	return 0;
}

int window_get_size( int *w, int *h )
{
    SDL_GetWindowSize( window.handle, w, h );
    return 0;
}
