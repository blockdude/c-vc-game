#include "utest.h"
#include <vcp/vcp.h>

UTEST(clock, frame_create_60fps)
{
    struct FrameClock fc = frame_clock_create(60.0);
    EXPECT_TRUE(fabs(fc.interval - 1.0 / 60.0) < 0.0001);
}

UTEST(clock, frame_create_zero_rate)
{
    struct FrameClock fc = frame_clock_create(0.0);
    EXPECT_EQ(fc.interval, 0.0);
}

UTEST(clock, frame_create_negative_rate)
{
    struct FrameClock fc = frame_clock_create(-30.0);
    EXPECT_EQ(fc.interval, 0.0);
}

UTEST(clock, frame_set_rate)
{
    struct FrameClock fc = frame_clock_create(30.0);
    frame_clock_set_rate(&fc, 60.0);
    EXPECT_TRUE(fabs(fc.interval - 1.0 / 60.0) < 0.0001);
}

UTEST(clock, frame_set_rate_zero)
{
    struct FrameClock fc = frame_clock_create(60.0);
    frame_clock_set_rate(&fc, 0.0);
    EXPECT_EQ(fc.interval, 0.0);
}

UTEST(clock, fixed_create_60fps)
{
    struct FixedClock fc = fixed_clock_create(60.0);
    EXPECT_TRUE(fabs(fc.interval - 1.0 / 60.0) < 0.0001);
}

UTEST(clock, fixed_create_zero_rate)
{
    struct FixedClock fc = fixed_clock_create(0.0);
    EXPECT_TRUE(fabs(fc.interval - 1.0 / 60.0) < 0.0001);
}

UTEST(clock, fixed_set_rate)
{
    struct FixedClock fc = fixed_clock_create(30.0);
    fc.interval = 0.0;
    fixed_clock_accumulate(&fc, 1.0 / 60.0);
    EXPECT_TRUE(fabs(fc.accumulator - 1.0 / 60.0) < 0.0001);
}

UTEST(clock, fixed_consume)
{
    struct FixedClock fc = fixed_clock_create(60.0);
    fixed_clock_accumulate(&fc, 1.0 / 60.0);
    EXPECT_TRUE(fixed_clock_consume(&fc));
    EXPECT_FALSE(fixed_clock_consume(&fc));
}

UTEST(clock, fixed_alpha)
{
    struct FixedClock fc = fixed_clock_create(60.0);
    fixed_clock_accumulate(&fc, 1.0 / 120.0);
    EXPECT_TRUE(fabs(fixed_clock_alpha(&fc) - 0.5) < 0.0001);
}

UTEST(clock, no_wait_delta_matches_timestep)
{
    struct Timestep ts = timestep_create(0.0);
    struct FrameClock fc = frame_clock_create(0.0);

    /* both clocks skip the first frame (no delta), so warm up first */
    timestep_tick(&ts);
    frame_clock_tick(&fc);

    for (int i = 0; i < 100; i++)
    {
        timestep_tick(&ts);
        frame_clock_tick(&fc);
        EXPECT_TRUE(fabs(ts.delta - fc.delta) < 0.001);
    }
}

UTEST(clock, fixedstep_matches_fixedclock)
{
    f64 deltas[200];
    struct FrameClock measure = frame_clock_create(0.0);

    for (int i = 0; i < 200; i++)
    {
        frame_clock_tick(&measure);
        deltas[i] = measure.delta;
    }

    struct Timestep ts = timestep_create(60);
    int old_ticks = 0;
    for (int i = 0; i < 200; i++)
    {
        while (fixedstep_tick(&ts, deltas[i]))
            old_ticks++;
    }
    f64 old_residual = ts.target_delta > 0.0 ? ts.delta / ts.target_delta : 0.0;

    struct FixedClock fc = fixed_clock_create(60);
    int new_ticks = 0;
    for (int i = 0; i < 200; i++)
    {
        fixed_clock_accumulate(&fc, deltas[i]);
        while (fixed_clock_consume(&fc))
            new_ticks++;
    }
    f64 new_residual = fixed_clock_alpha(&fc);

    EXPECT_EQ(old_ticks, new_ticks);
    EXPECT_TRUE(fabs(old_residual - new_residual) < 0.001);
}

UTEST(clock, clock_stats_sample_frame)
{
    struct FrameClock fc = frame_clock_create(60.0);
    struct ClockStats s = { 0 };

    frame_clock_tick(&fc);  /* first call: delta = 0 (last == 0 guard) */
    frame_clock_tick(&fc);  /* second call: delta > 0 */
    clock_stats_sample_frame(&s, &fc);

    EXPECT_EQ(s.count, 1);
    EXPECT_TRUE(s.elapsed > 0.0);
    EXPECT_TRUE(s.instant_rate > 0.0);
}

UTEST(clock, clock_stats_sample_step)
{
    struct FixedClock fc = fixed_clock_create(60.0);
    struct ClockStats s = { 0 };

    fixed_clock_accumulate(&fc, 1.0 / 60.0);
    int ticks = 0;
    while (fixed_clock_consume(&fc))
        ticks++;

    clock_stats_sample_step(&s, &fc, ticks);

    EXPECT_EQ(s.count, 1);
    EXPECT_TRUE(s.instant_rate > 0.0);
}

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
