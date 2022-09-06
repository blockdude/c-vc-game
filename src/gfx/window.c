#include "window.h"
#include "../input/input.h"

// global variables
struct window window;
SDL_Renderer *renderer;

bool quit = false;
bool pause = false;

// private variables
static const char *title = "game";
static const u32 wflags = SDL_WINDOW_RESIZABLE;
static const u32 rflags = SDL_RENDERER_PRESENTVSYNC;

#define FRAME_RATE 100.0
#define TICK_RATE 60.0

static u64 target_frame_delta = 1000.0 / FRAME_RATE;
static f64 target_tick_delta = 1000.0 / TICK_RATE;

// user functions
static window_event_fn user_init = NULL;
static window_event_fn user_close = NULL;
static window_event_fn user_update = NULL;
static window_event_fn user_tick = NULL;
static window_event_fn user_render = NULL;

// handle input each frame
static void handle( void )
{
    SDL_Event event;
    while ( SDL_PollEvent( &event ) )
    {
        switch ( event.type )
        {
            case SDL_QUIT:

                quit = true;

                break;

            case SDL_WINDOWEVENT:

                switch ( event.window.event )
                {
                    case SDL_WINDOWEVENT_RESIZED:

                        SDL_GetWindowSize( window.handle, &window.w, &window.h );

                        break;
                }

                break;
        }

        input_handle( &event );
    }
}

static void init( void )
{
    window.frame = 0;
    window.tick = 0;
    window.tdelta = target_tick_delta;
    user_init();
    input_init();
}

static void close( void )
{
    user_close();
}

static void update( void )
{
    user_update();
    input_update();
}

static void tick( void )
{
    user_tick();
    window.tick++;
}

static void render( void )
{
    user_render();
    window.frame++;
}

void window_init( window_event_fn init, window_event_fn close, window_event_fn update, window_event_fn tick, window_event_fn render )
{
    user_init = init;
    user_close = close;
    user_update = update;
    user_tick = tick;
    user_render = render;

    window.w = 700;
    window.h = 700;

    if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
        return;

    window.handle = SDL_CreateWindow( title, 0, 0, window.w, window.h, wflags );
    if ( !window.handle )
    {
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer( window.handle, -1, rflags );
    if ( !renderer )
    {
        SDL_DestroyWindow( window.handle );
        SDL_Quit();
        return;
    }

    SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_BLEND );
}

void window_start( void )
{
    init();

    // note: cool game loop from "Game Programming Patterns"
    u64 frame_previous = SDL_GetTicks64();
    f64 tick_time = 0;

    u64 tick_last = 0;
    u64 frame_last = 0;

    u64 frame_timer = frame_previous;

    while ( !quit )
    {
        // get frame timing
        u64 frame_current = SDL_GetTicks64();
        u64 frame_delta = frame_current - frame_previous;

        // update fps & tps every second
        if ( frame_current - frame_timer >= 1000 )
        {
            // get variables
            u64 ticks = window.tick - tick_last;
            u64 frames = window.frame - frame_last;

            // store timeings
            window.tps = ticks;
            window.fps = frames;

            // store this frame/tick
            tick_last = window.tick;
            frame_last = window.frame;

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
        window.delta = ( f64 ) frame_delta / 1000.0;

        // apply fps cap
        int delay = frame_current + target_frame_delta - SDL_GetTicks64();
        if ( delay > 0 )
        {
            SDL_Delay( delay );
        }
    }

    close();
}

void window_close( void )
{
    if ( window.handle )
        SDL_DestroyWindow( window.handle );

    if ( renderer )
        SDL_DestroyRenderer( renderer );

    SDL_Quit();

    window.handle = NULL;
    renderer = NULL;
    quit = 1;
}
