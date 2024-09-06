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
#define PROC_EVENT( _event ) if ( core.app.state._event != NULL ) { core.app.state._event(); }

    core.timestep.running = true;

    PROC_EVENT( init );

    core.timestep.current  = time_ticks();
    core.timestep.previous = core.timestep.current;

    core.timestep.f_delta  = 0.0f;
    core.timestep.f_last   = 0;

    core.timestep.t_delta  = 0.0f;
    core.timestep.t_last   = 0;

    core.timestep.elapsed  = 0.0f;
    core.timestep.timer    = 1.0f;

	// begin main loop
    while ( core.timestep.running )
    {
        // poll/handle events
        if ( input_poll() == INPUT_QUIT )
            break;

        // maintain fixed time step for each tick
        core.timestep.t_delta += core.timestep.f_delta;
        while ( core.timestep.t_delta >= core.timestep.t_target )
        {
            PROC_EVENT( tick );
            core.timestep.t_count++;
            core.timestep.t_delta -= core.timestep.t_target;
        }

        PROC_EVENT( update );
        PROC_EVENT( render );

        core.timestep.current  = time_ticks();
        core.timestep.f_delta  = core.timestep.current - core.timestep.previous;
        core.timestep.previous = core.timestep.current;

        core.timestep.f_avg = TIMESCALE * ( core.timestep.f_count / core.timestep.elapsed );
        core.timestep.t_avg = TIMESCALE * ( core.timestep.t_count / core.timestep.elapsed );

        // update fps & tps every second
        if ( core.timestep.timer <= 0.0f )
        {
            core.timestep.f_rate = core.timestep.f_count - core.timestep.f_last;
            core.timestep.t_rate = core.timestep.t_count - core.timestep.t_last;
            core.timestep.f_last = core.timestep.f_count;
            core.timestep.t_last = core.timestep.t_count;
            core.timestep.timer = 1.0f;
        }

        // apply fps cap
        if ( core.timestep.f_delta < core.timestep.f_target )
        {
            time_sleep( core.timestep.f_target - core.timestep.f_delta );

            core.timestep.current = time_ticks();
            float wait = core.timestep.current - core.timestep.previous;
            core.timestep.previous = core.timestep.current;

            core.timestep.f_delta += wait;
        }

        core.timestep.elapsed += core.timestep.f_delta;
        core.timestep.timer -= core.timestep.f_delta;
        core.timestep.f_count++;
    }

    PROC_EVENT( free );
}


void app_stop( void )
{
    core.timestep.running = false;
}

struct app *app_handle( void )
{
    return &core.app.state;
}

void app_target_fps_set( float target )
{
    core.timestep.f_target = target <= 0.0f ? -1.0f : TIMESCALE / target;
}

void app_target_tps_set( float target )
{
    core.timestep.t_target = target <= 0.0f ? -1.0f : TIMESCALE / target;
}

int app_fps( void )
{
    return core.timestep.f_rate;
}

int app_tps( void )
{
    return core.timestep.t_rate;
}
