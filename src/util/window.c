#include "window.h"

// global variables
struct Window window;
SDL_Renderer *renderer;

bool quit = false;
bool pause = false;

// private variables
static const char *title = "game";
static const u32 wflags = SDL_WINDOW_RESIZABLE;
static const u32 rflags = SDL_RENDERER_PRESENTVSYNC;

#define FRAME_RATE 60.0f
#define TICK_RATE 60.0f

static u32 target_frame_rate = FRAME_RATE;
static u32 target_frame_delta = 1000.0f / FRAME_RATE;

static u32 target_tick_rate = TICK_RATE;
static u32 target_tick_delta = 1000.0f / TICK_RATE;

// user functions
static WF user_init;
static WF user_close;
static WF user_update;
static WF user_tick;
static WF user_render;

// handle input each frame
static void handle()
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

static void init()
{
    window.frame = 0;
    window.tick = 0;
    user_init();
    input_init();
}

static void close()
{
    user_close();
}

static void update()
{
    user_update();
    input_update();
    window.frame++;
}

static void tick()
{
    user_tick();
    window.tick++;
}

static void render()
{
    user_render();
}

void window_init( WF init, WF close, WF update, WF tick, WF render )
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

void window_start()
{
    init();

    while ( !quit )
    {
        u64 frame_start = SDL_GetTicks64();

        handle();
        update();
        render();

        u64 frame_delta = SDL_GetTicks64() - frame_start;

        // apply fps cap
        if ( target_frame_delta > frame_delta )
        {
            SDL_Delay( target_frame_delta - frame_delta );
        }

        // get timings
        window.delta_t = ( f64 ) ( SDL_GetTicks64() - frame_start ) / 1000.0f;
        window.fps = 1.0f / window.delta_t;
    }

    close();
}

void window_close()
{
    if ( window.handle )
        SDL_DestroyWindow( window.handle );

    if ( renderer )
        SDL_DestroyRenderer( renderer );

    SDL_Quit();

    window.handle = NULL;
    renderer = NULL;
}
