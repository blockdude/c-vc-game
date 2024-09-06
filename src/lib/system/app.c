#include "app.h"
#include "global.h"
#include <util/log.h>

#include <system/input.h>
#include <system/time.h>

#include <assert.h>

int app_init( event_fn init, event_fn free, event_fn tick, event_fn update, event_fn render )
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

        .tick_delta   = TIMESCALE / 30.0f,
        .tick_target  = TIMESCALE / 30.0f,
        .tick_avg     = 0.0f,
        .tick_rate    = 0,
        .tick_count   = 0
    };

    core.app.state = a;

	return 0;
}

void app_loop( void )
{
#define PROC_EVENT( _event ) if ( self->_event != NULL ) { self->_event(); }

    struct app *self = &core.app.state;
    self->running = true;

    float frame_curr  = time_ticks();
    float frame_prev  = time_ticks();
    float frame_timer = frame_prev;
    float frame_last  = 0;

    float tick_last  = 0;
    float tick_time  = 0;

    float elapsed = 0;

    PROC_EVENT( init );

	// begin main loop
    while ( self->running )
    {
        // poll/handle events
        if ( input_poll() == INPUT_QUIT )
            goto exit;
        
        // maintain fixed time step for each tick
        while ( tick_time >= self->tick_target )
        {
            PROC_EVENT( tick );
            self->tick_count++;
            tick_time -= self->tick_target;
        }

        PROC_EVENT( update );
        PROC_EVENT( render );
        self->frame_count++;

        // get frame timing
        frame_curr = time_ticks();
        float delta_time  = frame_curr - frame_prev;

        frame_prev  = frame_curr;
        elapsed    += delta_time;
        tick_time  += delta_time;

        self->frame_delta = delta_time;
        self->frame_avg   = TIMESCALE * ( ( float ) self->frame_count / elapsed );
        self->tick_avg    = TIMESCALE * ( ( float ) self->tick_count  / elapsed );

        // update fps & tps every second
        if ( frame_curr - frame_timer >= TIMESCALE )
        {
            // store rate per second
            self->frame_rate = self->frame_count - frame_last;
            self->tick_rate  = self->tick_count  - tick_last;

            // store this frame/tick
            tick_last  = self->tick_count;
            frame_last = self->frame_count;

            // reset timer
            frame_timer = frame_curr;
        }

        // apply fps cap
        float frame_time = frame_curr - time_ticks();
        if ( frame_time < self->frame_target )
        {
            time_sleep( self->frame_target - frame_time );
        }
    }

exit:
    PROC_EVENT( free );
}

void app_stop( void )
{
    core.app.state.running = false;
}

struct app *app_handle( void )
{
    return &core.app.state;
}

void app_target_fps_set( float target )
{
    core.app.state.frame_target = target <= 0.0f ? -1.0f : TIMESCALE / target;
}

void app_target_tps_set( float target )
{
    core.app.state.tick_target = target <= 0.0f ? -1.0f : TIMESCALE / target;
    core.app.state.tick_delta  = core.app.state.tick_target;
}

int app_fps( void )
{
    return core.app.state.frame_rate;
}

int app_tps( void )
{
    return core.app.state.tick_rate;
}
