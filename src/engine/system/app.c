#include "app.h"
#include <util/log.h>
#include <system/input.h>

static inline int internal_init( struct app *self )
{
    if ( self->init != NULL )
        self->init( self );

    return 0;
}

static inline int internal_free( struct app *self )
{
    if ( self->free != NULL )
        self->free( self );

    return 0;
}

static inline int internal_tick( struct app *self )
{
    if ( self->tick != NULL )
        self->tick( self );

    self->tick_count++;

    return 0;
}

static inline int internal_update( struct app *self )
{
    if ( self->update != NULL )
        self->update( self );

    return 0;
}

static inline int internal_render( struct app *self )
{
    if ( self->render != NULL )
        self->render( self );

    self->frame_count++;

    return 0;
}

static int internal_loop( struct app *self )
{
    log_info( "Starting application loop" );
    internal_init( self );

    uint64_t frame_prev = SDL_GetTicks();
    float tick_time = 0;

    uint64_t tick_last = 0;
    uint64_t frame_last = 0;

    uint64_t frame_timer = frame_prev;
    uint64_t frame_total = 0;
    float frame_skip = 0;

	// begin main loop
    while ( self->running )
    {
        // get frame timing
        uint64_t frame_start = SDL_GetTicks();
        uint64_t frame_delta = frame_start - frame_prev;

        // update fps & tps every second
        if ( frame_start - frame_timer >= TIMESCALE )
        {
            // get variables
            int ticks  = self->tick_count - tick_last;
            int frames = self->frame_count - frame_last;

            // store rate per second
            self->frame_rate = frames;
            self->tick_rate = ticks;

            // store this frame/tick
            tick_last  = self->tick_count;
            frame_last = self->frame_count;

            // reset timer
            frame_timer = frame_start;
        }

        frame_prev = frame_start;
        tick_time += frame_delta;
        frame_total += frame_delta;

        // poll/handle events
        if ( input_poll() == INPUT_QUIT )
            goto soft_exit;
        
        // maintain fixed time step for each tick
        while ( tick_time >= self->tick_target )
        {
            internal_tick( self );
            tick_time -= self->tick_target;
        }

        internal_update( self );
        internal_render( self );

        self->frame_delta = frame_delta / TIMESCALE;
        self->frame_avg   = TIMESCALE / ( ( float ) frame_total / self->frame_count );

        // apply fps cap
        int frame_time = frame_start - SDL_GetTicks();
        int delay = self->frame_target - frame_time;
        if ( frame_time < self->frame_target )
        {
            //frame_skip += ( delay - ( int ) delay );
            //if ( frame_skip > 2.0f )
            //{
            //    delay += 1.0f;
            //    frame_skip -= 2.0f;
            //}

            SDL_Delay( delay );
        }

        log_debug( "%f", frame_skip );
    }

soft_exit:
	internal_free( self );
    return 0;
}

int app_init( struct app *self, event_fn init, event_fn free, event_fn tick, event_fn update, event_fn render )
{
    struct app a = {
        .init         = init,
        .free         = free,
        .tick         = tick,
        .update       = update,
        .render       = render,

        .running      = false,
        .skip_ticks   = false,

        .frame_delta  = 0,
        .frame_target = TIMESCALE / 60.0f,
        .frame_avg    = 0.0f,
        .frame_rate   = 0,
        .frame_count  = 0,

        .tick_delta   = 0,
        .tick_target  = TIMESCALE / 30.0f,
        .tick_avg     = 0.0f,
        .tick_rate    = 0,
        .tick_count   = 0
    };

    *self = a;

	return 0;
}

void app_loop( struct app *self )
{
    if ( self == NULL )
        return;

    self->running = true;
    internal_loop( self );
}

void app_stop( struct app *self )
{
    self->running = false;
}

void app_set_target_fps( struct app *self, float target )
{
    self->frame_target = target <= 0.0f ? -1.0f : TIMESCALE / target;
}

void app_set_target_tps( struct app *self, float target )
{
    self->tick_target = target <= 0.0f ? -1.0f : TIMESCALE / target;
}

int app_get_fps( struct app *self )
{
    return self->frame_rate;
}

int app_get_tps( struct app *self )
{
    return self->tick_rate;
}
