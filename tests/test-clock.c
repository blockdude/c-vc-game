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
    fixed_clock_set_rate(&fc, 60.0);
    EXPECT_TRUE(fabs(fc.interval - 1.0 / 60.0) < 0.0001);
}

UTEST(clock, fixed_set_rate_zero)
{
    struct FixedClock fc = fixed_clock_create(30.0);
    fixed_clock_set_rate(&fc, 0.0);
    EXPECT_TRUE(fabs(fc.interval - 1.0 / 60.0) < 0.0001);
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

UTEST(clock, clock_stats_sample_frame)
{
    struct FrameClock fc = frame_clock_create(60.0);
    struct ClockConfig cfg = clock_config_default();
    struct ClockStats s = { 0 };

    frame_clock_tick(&fc);  /* first call: delta = 0 (last == 0 guard) */
    frame_clock_tick(&fc);  /* second call: delta > 0 */
    clock_stats_sample(&s, cfg, fc.delta, 1);

    EXPECT_EQ(s.count, 1);
    EXPECT_TRUE(s.elapsed > 0.0);
    EXPECT_TRUE(s.instant_rate > 0.0);
}

UTEST(clock, clock_stats_sample_fixed)
{
    struct FixedClock fc = fixed_clock_create(60.0);
    struct ClockConfig cfg = clock_config_default();
    struct ClockStats s = { 0 };

    fixed_clock_accumulate(&fc, 1.0 / 60.0);
    u64 ticks = 0;
    while (fixed_clock_consume(&fc))
        ticks++;

    clock_stats_sample(&s, cfg, (f64)ticks * fc.interval, ticks);

    EXPECT_EQ(s.count, 1);
    EXPECT_TRUE(s.instant_rate > 0.0);
}

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
