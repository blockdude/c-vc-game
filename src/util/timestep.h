#ifndef VCP_TIMESTEP_H
#define VCP_TIMESTEP_H

/*
 * TS_TIME expects a function that returns seconds since the program has started
 * TS_SLEEP expects a function that takes in seconds and sleeps the calling thread for that amount of seconds
 */

#include "../vcp_common.h"
#include "types.h"

#ifndef TIMESTEP_CAPTURE_COUNT
#define TIMESTEP_CAPTURE_COUNT 60
#endif

#define _TIMESTEP_TEMPLATE \
{                                           \
    f64 rate;                               \
    f64 avg;                                \
    f64 delta;                              \
    f64 target_delta;                       \
    f64 target_rate;                        \
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
        } record[TIMESTEP_CAPTURE_COUNT];   \
    } _snapshot;                            \
                                            \
    struct                                  \
    {                                       \
        bool looping;                       \
    } _state;                               \
}

struct timestep _TIMESTEP_TEMPLATE;
struct timestep_fixed _TIMESTEP_TEMPLATE;

#ifdef __cplusplus
extern "C" {
#endif

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
extern bool timestep_tick(struct timestep *timestep);
extern void timestep_set_rate(struct timestep *timestep, f64 rate);
extern struct timestep timestep_create(f64 rate);

/*
This function updates the state of a timestep, recording
time of each iteration and the frequency of updates.

fixed timestep is used if you want updates to be
decoupled from the refresh rate of the computer.

This function should be used inside a timestep. EX:
while ( timestep_tick( &timestep ) )
{
    while ( timestep_fixed_tick( &fixed_timestep, timestep.delta ) )
    {
        physics_tick();
    }
}
*/
extern bool timestep_fixed_tick(struct timestep_fixed *timestep, f64 delta_time);
extern void timestep_fixed_set_rate(struct timestep_fixed *timestep, f64 rate);
extern struct timestep_fixed timestep_fixed_create(f64 rate);

#ifdef __cplusplus
}
#endif

#endif