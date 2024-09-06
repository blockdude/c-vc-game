#ifndef TIMESTEP_H
#define TIMESTEP_H

#include <util/types.h>

#include "time.h"
#include "input.h"
#include "global.h"

#define FPS()        ( core.timestep.f_rate )
#define TPS()        ( core.timestep.t_rate )
#define SETFPS( _t ) ( core.timestep.f_target = ( _t ) <= 0.0f ? -1.0f : TIMESCALE / ( _t ) )
#define SETTPS( _t ) ( core.timestep.t_target = ( _t ) <= 0.0f ? -1.0f : TIMESCALE / ( _t ) )

#define STARTLOOP() \
    do                                                                                              \
    {                                                                                               \
        core.timestep.running  = true;                                                              \
        core.timestep.current  = time_ticks();                                                      \
        core.timestep.previous = core.timestep.current;                                             \
                                                                                                    \
        core.timestep.f_delta  = 0.0f;                                                              \
        core.timestep.f_last   = 0;                                                                 \
                                                                                                    \
        core.timestep.t_delta  = 0.0f;                                                              \
        core.timestep.t_last   = 0;                                                                 \
                                                                                                    \
        core.timestep.elapsed  = 0.0f;                                                              \
        core.timestep.timer    = 1.0f;                                                              \
                                                                                                    \
        while ( core.timestep.running )                                                             \
        {                                                                                           \
            core.timestep.elapsed += core.timestep.f_delta;                                         \
            core.timestep.t_delta += core.timestep.f_delta;                                         \
            core.timestep.timer   -= core.timestep.f_delta;                                         \
                                                                                                    \
            if ( input_poll() == INPUT_QUIT )                                                       \
                break;

#define STARTTICK() \
    while ( core.timestep.t_delta >= core.timestep.t_target )                                       \
    {

#define ENDTICK() \
        core.timestep.t_count++;                                                                    \
        core.timestep.t_delta -= core.timestep.t_target;                                            \
    }

#define STARTUPDATE()
#define ENDUPDATE() \
        core.timestep.current  = time_ticks();                                                      \
        core.timestep.f_delta  = core.timestep.current - core.timestep.previous;                    \
        core.timestep.previous = core.timestep.current;                                             \
                                                                                                    \
        core.timestep.f_avg = TIMESCALE * ( core.timestep.f_count / core.timestep.elapsed );        \
        core.timestep.t_avg = TIMESCALE * ( core.timestep.t_count / core.timestep.elapsed );        \
                                                                                                    \
        if ( core.timestep.timer <= 0.0f )                                                          \
        {                                                                                           \
            core.timestep.f_rate = core.timestep.f_count - core.timestep.f_last;                    \
            core.timestep.t_rate = core.timestep.t_count - core.timestep.t_last;                    \
            core.timestep.f_last = core.timestep.f_count;                                           \
            core.timestep.t_last = core.timestep.t_count;                                           \
            core.timestep.timer = 1.0f;                                                             \
        }                                                                                           \
                                                                                                    \
        if ( core.timestep.f_delta < core.timestep.f_target )                                       \
        {                                                                                           \
            time_sleep( core.timestep.f_target - core.timestep.f_delta );                           \
                                                                                                    \
            core.timestep.current = time_ticks();                                                   \
            float wait = core.timestep.current - core.timestep.previous;                            \
            core.timestep.previous = core.timestep.current;                                         \
                                                                                                    \
            core.timestep.f_delta += wait;                                                          \
        }                                                                                           \
                                                                                                    \
        core.timestep.f_count++;                                                                    \
    }

#define ENDLOOP() \
    }                                                                                               \
    while ( 0 )

#define LOOP( _tick, _update, _render ) \
    do                                                                                              \
    {                                                                                               \
		STARTLOOP();                                                                                \
		STARTTICK();                                                                                \
		_tick();                                                                                    \
		ENDTICK();                                                                                  \
		STARTUPDATE();                                                                              \
		_update();                                                                                  \
		_render();                                                                                  \
		ENDUPDATE();                                                                                \
		ENDLOOP();                                                                                  \
    }                                                                                               \
    while ( 0 )

#endif
