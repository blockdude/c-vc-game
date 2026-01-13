#include <vcp/vcp.h>

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

static inline f64 stiffness(f64 dt)
{
    if (dt > 0.012) // 60fps
        return 0.1;
    if (dt > 0.004) // 240fps
        return 0.01;
    if (dt > 0.001) // 500fps
        return 0.001;
    return 0.0001;
}

// ==============================
// END HELPER FUNCTIONS
// ==============================



// ==============================
// TIMESTEP
// ==============================

struct Timestep timestep_create(f64 rate)
{
    struct Timestep result = {
        .target_delta = rate <= 0 ? 0.0 : 1.0 / rate,
        .target_rate = rate,
        .rate = 0.0,
        .mavg_rate = 0.0,
        .ravg_rate = 0.0
    };

    return result;
}

void timestep_set_rate(struct Timestep *timestep, f64 rate)
{
    timestep->target_delta = rate <= 0.0 ? 0.0 : 1.0 / rate;
    timestep->target_rate = rate;
}

static inline bool _timestep_can_proc(struct Timestep *timestep)
{
    return timestep->target_delta >= 0.0;
}

static inline void _timestep_prefix(struct Timestep *timestep)
{
    timestep->_private.current_time = TIMESTEP_TIME_NOW();
    timestep->_private.previous_time = timestep->_private.current_time;
}

static inline void _timestep_postfix(struct Timestep *timestep)
{
    timestep->_private.current_time = TIMESTEP_TIME_NOW();
    timestep->delta = timestep->_private.current_time - timestep->_private.previous_time;
    timestep->_private.previous_time = timestep->_private.current_time;

    // apply fps cap
    if (timestep->delta < timestep->target_delta)
    {
        TIMESTEP_TIME_WAIT(timestep->target_delta - timestep->delta);
        timestep->_private.current_time = TIMESTEP_TIME_NOW();
        timestep->delta += timestep->_private.current_time - timestep->_private.previous_time;
        timestep->_private.previous_time = timestep->_private.current_time;
    }

    timestep->elapsed += timestep->delta;
    timestep->count += 1;

    if (timestep->_private.timer >= 1.0)
    {
        timestep->ps_rate = timestep->count - timestep->_private.ps_count;
        timestep->_private.ps_count = timestep->count;
        timestep->_private.timer = 0;
    }

    f64 s = stiffness(timestep->delta);
    timestep->rate = 1.0 / timestep->delta;
    timestep->ravg_rate = timestep->count / timestep->elapsed;
    timestep->mavg_rate = (timestep->rate * s) + (timestep->mavg_rate * (1.0 - s));
    timestep->_private.timer += timestep->delta;
}

bool timestep_tick(struct Timestep *timestep)
{
    /*
    * this function should mimic a for loop.
    * for ( initalization; condition; update );
    */

    /*
    * initalization
    */
    if (timestep->_private.looping == false)
    {
        _timestep_prefix(timestep);
        timestep->_private.looping = true;
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

    // if fixedstep_can_proc returns false then
    // we have broken out of the loop and should
    // reset our state.
    timestep->_private.looping = false;
    return false;
}

// ==============================
// END TIMESTEP
// ==============================



// ==============================
// TIMESTEP_FIXED
// ==============================

static inline void _fixedstep_prefix(struct Timestep *timestep, f64 delta_time)
{
    //if (timestep->_private.timer >= 1.0)
    //{
    //    timestep->rate = timestep->_private.count;
    //    timestep->_private.timer = 0;
    //    timestep->_private.count = 0;
    //}

    if (timestep->_private.timer >= 1.0)
    {
        timestep->ps_rate = timestep->count - timestep->_private.ps_count;
        timestep->_private.ps_count = timestep->count;
        timestep->_private.timer = 0;
    }

    f64 s = stiffness(delta_time);
    timestep->rate = delta_time > 0 ? timestep->_private.count / delta_time : 0;
    timestep->ravg_rate = timestep->count / timestep->_private.elapsed;
    timestep->mavg_rate = (timestep->rate * s) + (timestep->mavg_rate * (1.0 - s));

    timestep->delta += delta_time;
    timestep->_private.elapsed += delta_time;
    timestep->_private.timer += delta_time;
    timestep->_private.count = 0;
    
}

static inline bool _fixedstep_can_proc(struct Timestep *timestep)
{
    return (timestep->target_delta > 0.0) && (timestep->target_delta <= timestep->delta);
}

static inline void _fixedstep_postfix(struct Timestep *timestep)
{
    timestep->count += 1;
    timestep->delta -= timestep->target_delta;
    timestep->elapsed += timestep->target_delta;
    timestep->_private.count += 1;
}

bool fixedstep_tick(struct Timestep *timestep, f64 delta_time)
{
    /*
    * this function should mimic a for loop.
    * for ( initalization; condition; update );
    */

    /*
    * initalization
    */
    if (timestep->_private.looping == false)
    {
        _fixedstep_prefix(timestep, delta_time);
        timestep->_private.looping = true;
    }

    /*
    * update
    */
    else
    {
        _fixedstep_postfix(timestep);
    }

    /*
    * condition
    */
    if (_fixedstep_can_proc(timestep))
    {
        return true;
    }

    // if fixedstep_can_proc returns false then
    // we have broken out of the loop and should
    // reset our state.
    timestep->_private.looping = false;
    return false;
}

// ==============================
// END TIMESTEP_FIXED
// ==============================