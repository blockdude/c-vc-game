#ifndef VCP_TIMESTEP_H
#define VCP_TIMESTEP_H

/*
 * TS_TIME expects a function that returns seconds since the program has started
 * TS_SLEEP expects a function that takes in seconds and sleeps the calling thread for that amount of seconds
 */

#include "../common.h"
#include <stdint.h>
#include <stdbool.h>

#ifndef TIMESTEP_TIME_NOW
#error "define TIMESTEP_TIME_NOW"
#endif

#ifndef TIMESTEP_TIME_WAIT
#error "define TIMESTEP_TIME_WAIT"
#endif

#ifndef TIMESTEP_CAPTURE_COUNT
#define TIMESTEP_CAPTURE_COUNT 512
#endif

#define _timestep_type \
{                                           \
    int rate;                               \
    int avg;                                \
    f64 delta;                              \
    f64 target_delta;                       \
    int target_rate;                        \
    u64 count;                              \
                                            \
    f64 elapsed;                            \
    f64 current;                            \
    f64 previous;                           \
                                            \
    struct                                  \
    {                                       \
        f64 elapsed;                        \
        u64 count;                          \
        u64 last;                           \
        int index;                          \
                                            \
        struct                              \
        {                                   \
            f64 delta;                      \
            u64 count;                      \
        } record[ TIMESTEP_CAPTURE_COUNT ]; \
    } _snapshot;                            \
                                            \
    struct                                  \
    {                                       \
        bool looping;                       \
    } _state;                               \
}

struct timestep _timestep_type;
struct timestep_fixed _timestep_type;

#define _TIMESTEP_FUNC_DECL_SET_RATE( T, _name ) \
static inline void _name##_set_rate( T *const ts, const int rate ) { ts->target_delta = rate <= 0 ? 0.0 : 1.0 / rate; ts->target_rate = rate <= 0 ? 0 : rate; }

_TIMESTEP_FUNC_DECL_SET_RATE( struct timestep, timestep );
_TIMESTEP_FUNC_DECL_SET_RATE( struct timestep_fixed, timestep_fixed );

#define _TIMESTEP_PRESET_DECL_RATE( _rate ) \
static const struct timestep       TIMESTEP_##_rate##HZ       = { .target_delta = 1.0 / _rate##.0, .target_rate = _rate }; \
static const struct timestep_fixed TIMESTEP_FIXED_##_rate##HZ = { .target_delta = 1.0 / _rate##.0, .target_rate = _rate };

_TIMESTEP_PRESET_DECL_RATE( 30 );
_TIMESTEP_PRESET_DECL_RATE( 35 );
_TIMESTEP_PRESET_DECL_RATE( 40 );
_TIMESTEP_PRESET_DECL_RATE( 45 );
_TIMESTEP_PRESET_DECL_RATE( 50 );
_TIMESTEP_PRESET_DECL_RATE( 55 );
_TIMESTEP_PRESET_DECL_RATE( 60 );
_TIMESTEP_PRESET_DECL_RATE( 120 );
_TIMESTEP_PRESET_DECL_RATE( 144 );
_TIMESTEP_PRESET_DECL_RATE( 240 );
_TIMESTEP_PRESET_DECL_RATE( 360 );

#define TIMESTEP_TICK_WHILE( _ts, _cnd ) \
    for ( _timestep_prefix( _ts ); ( _cnd ) && _timestep_can_proc( _ts ); _timestep_postfix( _ts ) )

#define TIMESTEP_TICK( _ts ) \
    for ( _timestep_prefix( _ts ); _timestep_can_proc( _ts ); _timestep_postfix( _ts ) )

#define TIMESTEP_FIXED_TICK_WHILE( _ts, _dt, _cnd ) \
    for ( _timestep_fixed_prefix( _ts, _dt ); ( _cnd ) && _timestep_fixed_can_proc( _ts ); _timestep_fixed_postfix( _ts ) )

#define TIMESTEP_FIXED_TICK( _ts, _dt ) \
    for ( _timestep_fixed_prefix( _ts, _dt ); _timestep_fixed_can_proc( _ts ); _timestep_fixed_postfix( _ts ) )

static inline int _timestep_compute_rate( const i64 n, const f64 d )
{
    return ( ( n < 0 ) == ( d < 0 ) ) ? ( int ) ( ( n + d / 2 ) / d ) : ( int ) ( ( n - d / 2 ) / d );
}

static inline void _timestep_fixed_prefix( struct timestep_fixed *const timestep, const f64 delta_time )
{
    timestep->delta += delta_time;

    const int index = ( timestep->_snapshot.index + 1 ) % TIMESTEP_CAPTURE_COUNT;
    timestep->_snapshot.index = index;

    timestep->_snapshot.elapsed -= timestep->_snapshot.record[ index ].delta;
    timestep->_snapshot.record[ index ].delta = delta_time;
    timestep->_snapshot.elapsed += timestep->_snapshot.record[ index ].delta;

    timestep->_snapshot.count -= timestep->_snapshot.record[ index ].count;
    timestep->_snapshot.record[ index ].count = timestep->count - timestep->_snapshot.last;
    timestep->_snapshot.count += timestep->_snapshot.record[ index ].count;

    timestep->_snapshot.last = timestep->count;

    timestep->rate = _timestep_compute_rate( timestep->_snapshot.count, timestep->_snapshot.elapsed );
    timestep->avg = _timestep_compute_rate( timestep->count, timestep->elapsed );
}

static inline bool _timestep_fixed_can_proc( struct timestep_fixed *const timestep )
{
    return ( ( timestep->target_delta > 0.0 ) && ( timestep->target_delta <= timestep->delta ) );
}

static inline void _timestep_fixed_postfix( struct timestep_fixed *const timestep )
{
    timestep->count += 1;
    timestep->delta -= timestep->target_delta;
    timestep->elapsed += timestep->target_delta;
}

static inline bool _timestep_can_proc( struct timestep *const timestep )
{
    VCP_UNUSED_VAR( timestep );
    return true;
}

static inline void _timestep_prefix( struct timestep *const timestep )
{
    timestep->current = TIMESTEP_TIME_NOW();
    timestep->previous = timestep->current;
}

static inline void _timestep_postfix( struct timestep *const timestep )
{
    timestep->current = TIMESTEP_TIME_NOW();
    timestep->delta = timestep->current - timestep->previous;
    timestep->previous = timestep->current;

    // apply fps cap
    if ( timestep->delta < timestep->target_delta )
    {
        TIMESTEP_TIME_WAIT( timestep->target_delta - timestep->delta );
        timestep->current = TIMESTEP_TIME_NOW();
        timestep->delta += timestep->current - timestep->previous;
        timestep->previous = timestep->current;
    }

    timestep->elapsed += timestep->delta;
    timestep->count += 1;

    // calculate the average fps over TIMESTEP_CAPTURE_COUNT frames
    const int index = ( timestep->_snapshot.index + 1 ) % TIMESTEP_CAPTURE_COUNT;
    timestep->_snapshot.index = index;

    timestep->_snapshot.elapsed -= timestep->_snapshot.record[ index ].delta;
    timestep->_snapshot.record[ index ].delta = timestep->delta;
    timestep->_snapshot.elapsed += timestep->_snapshot.record[ index ].delta;

    timestep->_snapshot.count -= timestep->_snapshot.record[ index ].count;
    timestep->_snapshot.record[ index ].count = timestep->count - timestep->_snapshot.last;
    timestep->_snapshot.count += timestep->_snapshot.record[ index ].count;

    timestep->_snapshot.last = timestep->count;

    timestep->rate = _timestep_compute_rate( timestep->_snapshot.count, timestep->_snapshot.elapsed );
    timestep->avg = _timestep_compute_rate( timestep->count, timestep->elapsed );
}

/*
This function updates the state of a timestep, recording
time of each iteration and the frequency of updates.

This function should be used inside a while loop. ex:
while ( timestep_tick( &timestep ) );

However this does not have to be used in a while loop
and can be used as a fancy timer system.

EXAMPLE:

timestep_tick( &timestep );
somefunction();
timestep_tick( &timestep );
printf( "somefunction() took %f seconds to run", timestep.delta );
*/
static inline bool timestep_tick( struct timestep *const timestep )
{
    /*
    * this function should mimic a for loop.
    * for ( initalization; condition; update );
    */

    /*
    * initalization
    */
    if ( timestep->_state.looping == false )
    {
        _timestep_prefix( timestep );
        timestep->_state.looping = true;
    }

    /*
    * update
    */
    else
    {
        _timestep_postfix( timestep );
    }

    /*
    * condition
    */
    if ( _timestep_can_proc( timestep ) )
    {
        return true;
    }

    // if timestep_fixed_can_proc returns false then
    // we have broken out of the loop and should
    // reset our state.
    timestep->_state.looping = false;
    return false;
}

/*
This function updates the state of a timestep, recording
time of each iteration and the frequency of updates.

fixed timestep is used if you want updates to be
decoupled from the refresh rate of the computer.

This function should be used inside a within a
variable timestep loop. ex:
while ( timestep_tick( &timestep ) )
{
    while ( timestep_fixed_tick( &fixed_timestep, timestep.delta ) )
    {
        physics_tick();
    }
}
*/
static inline bool timestep_fixed_tick( struct timestep_fixed *const timestep, const f64 delta_time )
{
    /*
    * this function should mimic a for loop.
    * for ( initalization; condition; update );
    */

    /*
    * initalization
    */
    if ( timestep->_state.looping == false )
    {
        _timestep_fixed_prefix( timestep, delta_time );
        timestep->_state.looping = true;
    }

    /*
    * update
    */
    else
    {
        _timestep_fixed_postfix( timestep );
    }

    /*
    * condition
    */
    if ( _timestep_fixed_can_proc( timestep ) )
    {
        return true;
    }

    // if timestep_fixed_can_proc returns false then
    // we have broken out of the loop and should
    // reset our state.
    timestep->_state.looping = false;
    return false;
}

#endif