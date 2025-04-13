#include "timestep.h"
#include "../system/time.h"

// ==============================
// HELPER FUNCTIONS
// ==============================

// by default, timestep time units are in seconds
#define TIMESTEP_TIME_NOW time_now_s
#define TIMESTEP_TIME_WAIT time_wait_s

static inline f64 compute_rate(u64 n, f64 d)
{
    return (f64)(u64)((n + d / 2) / d);
}

// ==============================
// END HELPER FUNCTIONS
// ==============================



// ==============================
// TIMESTEP
// ==============================

static inline bool _timestep_can_proc(struct timestep *timestep)
{
    VCP_UNUSED_VAR(timestep);
    return true;
}

static inline void _timestep_prefix(struct timestep *timestep)
{
    timestep->current = TIMESTEP_TIME_NOW();
    timestep->previous = timestep->current;
}

static inline void _timestep_postfix(struct timestep *timestep)
{
    timestep->current = TIMESTEP_TIME_NOW();
    timestep->delta = timestep->current - timestep->previous;
    timestep->previous = timestep->current;

    // apply fps cap
    if (timestep->delta < timestep->target_delta)
    {
        TIMESTEP_TIME_WAIT(timestep->target_delta - timestep->delta);
        timestep->current = TIMESTEP_TIME_NOW();
        timestep->delta += timestep->current - timestep->previous;
        timestep->previous = timestep->current;
    }

    timestep->elapsed += timestep->delta;
    timestep->count += 1;

    // calculate the average fps over TIMESTEP_CAPTURE_COUNT frames
    const int index = (timestep->_snapshot.index + 1) % TIMESTEP_CAPTURE_COUNT;
    timestep->_snapshot.index = index;

    timestep->_snapshot.elapsed -= timestep->_snapshot.record[index].delta;
    timestep->_snapshot.record[index].delta = timestep->delta;
    timestep->_snapshot.elapsed += timestep->_snapshot.record[index].delta;

    timestep->_snapshot.count -= timestep->_snapshot.record[index].count;
    timestep->_snapshot.record[index].count = timestep->count - timestep->_snapshot.last;
    timestep->_snapshot.count += timestep->_snapshot.record[index].count;

    timestep->_snapshot.last = timestep->count;

    timestep->rate = compute_rate(timestep->_snapshot.count, timestep->_snapshot.elapsed);
    timestep->avg = compute_rate(timestep->count, timestep->elapsed);
}

bool timestep_tick(struct timestep *timestep)
{
    /*
    * this function should mimic a for loop.
    * for ( initalization; condition; update );
    */

    /*
    * initalization
    */
    if (timestep->_state.looping == false)
    {
        _timestep_prefix(timestep);
        timestep->_state.looping = true;
    }

    /*
    * update
    */
    else
    {
        _timestep_postfix(timestep);
    }

    /*
    * condition
    */
    if (_timestep_can_proc(timestep))
    {
        return true;
    }

    // if timestep_fixed_can_proc returns false then
    // we have broken out of the loop and should
    // reset our state.
    timestep->_state.looping = false;
    return false;
}

void timestep_set_rate(struct timestep *timestep, f64 rate)
{
    timestep->target_delta = rate <= 0 ? 0.0 : 1.0 / rate;
    timestep->target_rate = rate <= 0 ? 0 : rate;
}

struct timestep timestep_create(f64 rate)
{
    struct timestep result = {
        .target_delta = 1.0 / rate,
        .target_rate = rate
    };

    return result;
}

// ==============================
// END TIMESTEP
// ==============================



// ==============================
// TIMESTEP_FIXED
// ==============================

static inline void _timestep_fixed_prefix(struct timestep_fixed *timestep, f64 delta_time)
{
    timestep->delta += delta_time;

    const int index = (timestep->_snapshot.index + 1) % TIMESTEP_CAPTURE_COUNT;
    timestep->_snapshot.index = index;

    timestep->_snapshot.elapsed -= timestep->_snapshot.record[index].delta;
    timestep->_snapshot.record[index].delta = delta_time;
    timestep->_snapshot.elapsed += timestep->_snapshot.record[index].delta;

    timestep->_snapshot.count -= timestep->_snapshot.record[index].count;
    timestep->_snapshot.record[index].count = timestep->count - timestep->_snapshot.last;
    timestep->_snapshot.count += timestep->_snapshot.record[index].count;

    timestep->_snapshot.last = timestep->count;

    timestep->rate = compute_rate(timestep->_snapshot.count, timestep->_snapshot.elapsed);
    timestep->avg = compute_rate(timestep->count, timestep->elapsed);
}

static inline bool _timestep_fixed_can_proc(struct timestep_fixed *timestep)
{
    return ((timestep->target_delta > 0.0) && (timestep->target_delta <= timestep->delta));
}

static inline void _timestep_fixed_postfix(struct timestep_fixed *timestep)
{
    timestep->count += 1;
    timestep->delta -= timestep->target_delta;
    timestep->elapsed += timestep->target_delta;
}

bool timestep_fixed_tick(struct timestep_fixed *timestep, f64 delta_time)
{
    /*
    * this function should mimic a for loop.
    * for ( initalization; condition; update );
    */

    /*
    * initalization
    */
    if (timestep->_state.looping == false)
    {
        _timestep_fixed_prefix(timestep, delta_time);
        timestep->_state.looping = true;
    }

    /*
    * update
    */
    else
    {
        _timestep_fixed_postfix(timestep);
    }

    /*
    * condition
    */
    if (_timestep_fixed_can_proc(timestep))
    {
        return true;
    }

    // if timestep_fixed_can_proc returns false then
    // we have broken out of the loop and should
    // reset our state.
    timestep->_state.looping = false;
    return false;
}

void timestep_fixed_set_rate(struct timestep_fixed *timestep, f64 rate)
{
    timestep->target_delta = rate <= 0 ? 0.0 : 1.0 / rate;
    timestep->target_rate = rate <= 0 ? 0 : rate;
}

struct timestep_fixed timestep_fixed_create(f64 rate)
{
    struct timestep_fixed result = {
        .target_delta = 1.0 / rate,
        .target_rate = rate
    };

    return result;
}

// ==============================
// END TIMESTEP_FIXED
// ==============================