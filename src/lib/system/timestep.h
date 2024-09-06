#ifndef TIMESTEP_H
#define TIMESTEP_H

/*
 * There is no global state and is ment to only help quickly
 * create a game loop.
 *
 * Calling macros such as - FPS() - from other translation units
 * will not do much.
 *
 * TODO: Allow the loop to edit a global struct if a macro is
 * defined?
 *
 * Note: GETTIME and DELAY must be in seconds.
 * Note: POLLEVENTS must return an int where 0 is success.
 */

#include <util/types.h>

struct timestep
{
    bool			quit;

    int          	f_rate;
    float        	f_avg;
    float        	f_delta;
    float        	f_target;
    uint64_t     	f_count;

    int          	t_rate;
    float        	t_avg;
    float        	t_delta;
    float        	t_target;
    uint64_t     	t_count;

    // capture the frame rate & tick rate of the last second
    float           timer;
    uint64_t        f_last;
    uint64_t        t_last;

    double          elapsed;
    double          current;
    double          previous;
};

#ifndef EXTERNAL_LOOP_DATA
static struct timestep __loop_local;
static struct timestep *__loop = &__loop_local;
#else
extern struct timestep *__loop;
#endif

#ifndef GETTIME
#include <system/time.h>
#define GETTIME() time_ticks()
#endif

#ifndef DELAY 
#include <system/time.h>
#define DELAY( _s ) time_sleep( _s )
#endif

#ifndef POLLEVENTS
#include <system/input.h>
#define POLLEVENTS() input_poll()
#endif

#define FPS()        ( __loop->f_rate )
#define TPS()        ( __loop->t_rate )
#define SETFPS( _t ) ( __loop->f_target = ( _t ) <= 0.0f ? -1.0f : 1.0f / ( _t ) )
#define SETTPS( _t ) ( __loop->t_target = ( _t ) <= 0.0f ? -1.0f : 1.0f / ( _t ) )
#define STOPPING()   ( __loop->quit )
#define STOPLOOP()   ( __loop->quit = true )

#define LOOPWHILE( __c ) \
    for ( _loop_init(); ( __c ) && _loop_poll(); _loop_update() )

#define LOOP() \
    LOOPWHILE( !STOPPING() )

#define TICK() \
    for ( _tick_init(); _tick_proc(); _tick_update() )

static inline void _tick_init( void )
{
    __loop->t_delta += __loop->f_delta;
}

static inline bool _tick_proc( void )
{
    return __loop->t_delta >= __loop->t_target;
}

static inline void _tick_update( void )
{
    __loop->t_count += 1;
    __loop->t_delta -= __loop->t_target;
}

static inline bool _loop_poll( void )
{
    if ( POLLEVENTS() != 0 )
        return false;
    return true;
}

static inline void _loop_init( void )
{
    __loop->quit     = false;

    __loop->current  = GETTIME();
    __loop->previous = __loop->current;

    __loop->f_delta  = 0.0f;
    __loop->f_last   = 0;

    __loop->t_delta  = 0.0f;
    __loop->t_last   = 0;

    __loop->elapsed  = 0.0f;
    __loop->timer    = 1.0f;
}

static inline void _loop_update( void )
{
    __loop->current  = GETTIME();
    __loop->f_delta  = __loop->current - __loop->previous;
    __loop->previous = __loop->current;

    __loop->f_avg = __loop->f_count / __loop->elapsed;
    __loop->t_avg = __loop->t_count / __loop->elapsed;

    // update fps & tps every second
    if ( __loop->timer <= 0.0f )
    {
        __loop->f_rate = __loop->f_count - __loop->f_last;
        __loop->t_rate = __loop->t_count - __loop->t_last;
        __loop->f_last = __loop->f_count;
        __loop->t_last = __loop->t_count;
        __loop->timer = 1.0f;
    }

    // apply fps cap
    if ( __loop->f_delta < __loop->f_target )
    {
        DELAY( __loop->f_target - __loop->f_delta );

        __loop->current = GETTIME();
        float wait = __loop->current - __loop->previous;
        __loop->previous = __loop->current;

        __loop->f_delta += wait;
    }

    __loop->elapsed += __loop->f_delta;
    __loop->timer   -= __loop->f_delta;
    __loop->f_count += 1;
}

#endif
