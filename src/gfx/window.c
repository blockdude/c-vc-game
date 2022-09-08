#include "window.h"
#include "../input/input.h"

// global variables
struct window window;
SDL_Renderer *renderer;

#define WINDOW_TITLE "window"
#define WINDOW_FLAGS SDL_WINDOW_RESIZABLE
#define RENDER_FLAGS SDL_RENDERER_PRESENTVSYNC

// handle input each frame
static int handle( void )
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

    return 0;
}

static int init( void )
{
    window.event.init();
    input_init();

    return 0;
}

static int quit( void )
{
    window.event.quit();

    return 0;
}

static int update( void )
{
    window.event.update();
    input_update();

    return 0;
}

static int tick( void )
{
    window.event.tick();
    window.tick.count++;

    return 0;
}

static int render( void )
{
	window.event.render();
    window.frame.count++;

    return 0;
}

int window_init( window_event_fn init, window_event_fn quit, window_event_fn update, window_event_fn tick, window_event_fn render )
{
	// init variables
	window.running = true;

    window.event.init = init;
    window.event.quit = quit;
    window.event.update = update;
    window.event.tick = tick;
    window.event.render = render;

	window.frame.target_rate = 60;
	window.frame.rate = 0;
	window.frame.delta = 0;
	window.frame.count = 0;

	window.tick.target_rate = 60;
	window.tick.rate = 0;
	window.tick.delta = 1000.0 / window.tick.target_rate;
	window.tick.count = 0;

	// init sdl stuff
    if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
        return 1;

    window.handle = SDL_CreateWindow( WINDOW_TITLE, 0, 0, 700, 700, WINDOW_FLAGS );
    if ( !window.handle )
    {
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer( window.handle, -1, RENDER_FLAGS );
    if ( !renderer )
    {
        SDL_DestroyWindow( window.handle );
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_BLEND );

    return 0;
}

int window_loop( void )
{
    init();

	u64 target_frame_delta = 1000.0 / window.frame.target_rate;
	f64 target_tick_delta = 1000.0 / window.tick.target_rate;

    // note: cool game loop from "Game Programming Patterns"
    u64 frame_previous = SDL_GetTicks64();
    f64 tick_time = 0;

    u64 tick_last = 0;
    u64 frame_last = 0;

    u64 frame_timer = frame_previous;

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

        handle();

        // do ticks and maintain tick rate
        while( tick_time >= target_tick_delta )
        {
            tick();
            tick_time -= target_tick_delta;
        }

        update();
        render();

        // convert & store frame timing of current frame
        window.frame.delta = ( f64 ) frame_delta / 1000.0;

        // apply fps cap
        int delay = frame_current + target_frame_delta - SDL_GetTicks64();
        if ( delay > 0 )
        {
            SDL_Delay( delay );
        }
    }

    quit();

    return 0;
}

int window_quit( void )
{
    if ( window.handle )
        SDL_DestroyWindow( window.handle );

    if ( renderer )
        SDL_DestroyRenderer( renderer );

    SDL_Quit();
	quit();

    window.handle = NULL;
    renderer = NULL;

    return 0;
}
