#ifndef VCP_TIMESTEP_H
#define VCP_TIMESTEP_H

/*
 * TS_TIME expects a function that returns seconds since the program has started
 * TS_SLEEP expects a function that takes in seconds and sleeps the calling thread for that amount of seconds
 */

#include <stdint.h>
#include <stdbool.h>

#ifndef TS_TIME
#error "define TS_TIME"
#endif

#ifndef TS_SLEEP
#error "define TS_SLEEP"
#endif

#define TS_FRAME_CAPTURE_COUNT 256

struct _ts_record
{
    double delta;
    uint64_t count;
};

struct _ts_snapshot
{
    uint64_t count;
    double elapsed;
    uint64_t last;
    int index;
    struct _ts_record record[TS_FRAME_CAPTURE_COUNT];
};

struct _timestep
{
    int   	        rate;
    int         	avg;
    double        	delta;
    double        	target_delta;
    int             target_rate;
    uint64_t     	count;

    double          elapsed;
    double          current;
    double          previous;

    // frame rate capture history
    struct _ts_snapshot snapshot;
};

static inline void set_rate( struct _timestep *t, int rate )
{
    t->target_delta = rate <= 0 ? -1.0 : 1.0 / ( double ) rate;
    t->target_rate = rate;
}

typedef struct _timestep frame_control_t;
typedef struct _timestep tick_control_t;

static const struct _timestep DEFAULT_TIMESTEP = { .target_delta = -1.0, .target_rate = 0 };
static const struct _timestep TIMESTEP_30HZ = { .target_delta = 1.0 / 30.0, .target_rate = 30 };
static const struct _timestep TIMESTEP_40HZ = { .target_delta = 1.0 / 40.0, .target_rate = 40 };
static const struct _timestep TIMESTEP_60HZ = { .target_delta = 1.0 / 60.0, .target_rate = 60 };
static const struct _timestep TIMESTEP_144HZ = { .target_delta = 1.0 / 144.0, .target_rate = 144 };
static const struct _timestep TIMESTEP_240HZ = { .target_delta = 1.0 / 240.0, .target_rate = 240 };

#define DEFAULT_FRAME DEFAULT_TIMESTEP
#define FRAME_30HZ TIMESTEP_30HZ
#define FRAME_40HZ TIMESTEP_40HZ
#define FRAME_60HZ TIMESTEP_60HZ
#define FRAME_144HZ TIMESTEP_144HZ
#define FRAME_240HZ TIMESTEP_240HZ

#define DEFAULT_TICK DEFAULT_TIMESTEP
#define TICK_30HZ TIMESTEP_30HZ
#define TICK_40HZ TIMESTEP_40HZ
#define TICK_60HZ TIMESTEP_60HZ
#define TICK_144HZ TIMESTEP_144HZ
#define TICK_240HZ TIMESTEP_240HZ

#define TS_FRAME_WHILE(_f, _c) \
    for (_frame_prefix(_f); (_c) && _frame_can_proc(_f); _frame_postfix(_f))

#define TS_FRAME_LOOP(_f) \
    for (_frame_prefix(_f); _frame_can_proc(_f); _frame_postfix(_f))

#define TS_TICK_LOOP(_t, _f) \
    for (_tick_prefix(_t, _f); _tick_can_proc(_t); _tick_postfix(_t))

static inline void _tick_prefix(tick_control_t *tick, frame_control_t *frame)
{
    tick->delta += frame->delta;

    int index = (tick->snapshot.index + 1) % TS_FRAME_CAPTURE_COUNT;
    tick->snapshot.index = index;

    tick->snapshot.elapsed -= tick->snapshot.record[index].delta;
    tick->snapshot.record[index].delta = frame->delta;
    tick->snapshot.elapsed += tick->snapshot.record[index].delta;

    tick->snapshot.count -= tick->snapshot.record[index].count;
    tick->snapshot.record[index].count = tick->count - tick->snapshot.last;
    tick->snapshot.count += tick->snapshot.record[index].count;

    tick->snapshot.last = tick->count;

    tick->rate = round((double) tick->snapshot.count / tick->snapshot.elapsed);
    tick->avg = round((double) tick->count / tick->elapsed);
}

static inline bool _tick_can_proc(tick_control_t *tick)
{
    return ((tick->target_delta > 0.0) && (tick->target_delta <= tick->delta));
}

static inline void _tick_postfix(tick_control_t *tick)
{
    tick->count += 1;
    tick->delta -= tick->target_delta;
    tick->elapsed += tick->target_delta;
}

static inline bool _frame_can_proc(frame_control_t *frame)
{
    return true;
}

static inline void _frame_prefix(frame_control_t *frame)
{
    frame->current = TS_TIME();
    frame->previous = frame->current;
}

static inline void _frame_postfix(frame_control_t *frame)
{
    frame->current = TS_TIME();
    frame->delta = frame->current - frame->previous;
    frame->previous = frame->current;

    // apply fps cap
    if (frame->delta < frame->target_delta)
    {
        TS_SLEEP(frame->target_delta - frame->delta);
        frame->current = TS_TIME();
        frame->delta += frame->current - frame->previous;
        frame->previous = frame->current;
    }

    frame->elapsed += frame->delta;
    frame->count += 1;

    // calculate the average fps over TS_FRAME_CAPTURE_COUNT frames
    int index = (frame->snapshot.index + 1) % TS_FRAME_CAPTURE_COUNT;
    frame->snapshot.index = index;

    frame->snapshot.elapsed -= frame->snapshot.record[index].delta;
    frame->snapshot.record[index].delta = frame->delta;
    frame->snapshot.elapsed += frame->snapshot.record[index].delta;

    frame->snapshot.count -= frame->snapshot.record[index].count;
    frame->snapshot.record[index].count = frame->count - frame->snapshot.last;
    frame->snapshot.count += frame->snapshot.record[index].count;

    frame->snapshot.last = frame->count;

    frame->rate = round((double) frame->snapshot.count / frame->snapshot.elapsed);
    frame->avg = round((double) frame->count / frame->elapsed);
}

#endif