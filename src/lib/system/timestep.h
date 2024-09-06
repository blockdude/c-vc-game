#ifndef TIMESTEP_H
#define TIMESTEP_H

#include <util/types.h>
#include <util/log.h>

#include "time.h"
#include "input.h"
#include "global.h"

#define FPS()        ( core.timestep.f_rate )
#define TPS()        ( core.timestep.t_rate )
#define SETFPS( _t ) ( core.timestep.f_target = ( _t ) <= 0.0f ? -1.0f : TIMESCALE / ( _t ) )
#define SETTPS( _t ) ( core.timestep.t_target = ( _t ) <= 0.0f ? -1.0f : TIMESCALE / ( _t ) )
#define STOPPING()   ( core.timestep.quit )
#define STOPLOOP()   ( core.timestep.quit = true )

#define LOOPWHILE( __c ) \
    for ( __loop_init(); ( __c ) && __loop_poll(); __loop_update() )

#define LOOP() \
    LOOPWHILE( !STOPPING() )

#define TICK() \
    for ( __tick_init(); __tick_proc(); __tick_update() )

static void __tick_init( void )
{
    core.timestep.t_delta += core.timestep.f_delta;
}

static bool __tick_proc( void )
{
    return core.timestep.t_delta >= core.timestep.t_target;
}

static void __tick_update( void )
{
    core.timestep.t_count += 1;
    core.timestep.t_delta -= core.timestep.t_target;
}

static bool __loop_poll( void )
{
    if ( input_poll() == INPUT_QUIT )
        return false;
    return true;
}

static void __loop_init( void )
{
    core.timestep.quit     = false;

    core.timestep.current  = time_ticks();
    core.timestep.previous = core.timestep.current;

    core.timestep.f_delta  = 0.0f;
    core.timestep.f_last   = 0;

    core.timestep.t_delta  = 0.0f;
    core.timestep.t_last   = 0;

    core.timestep.elapsed  = 0.0f;
    core.timestep.timer    = 1.0f;
}

static void __loop_update( void )
{
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
    core.timestep.timer   -= core.timestep.f_delta;
    core.timestep.f_count += 1;
}

#endif
