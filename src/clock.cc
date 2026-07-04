#include <vcp/vcp.h>

// ==============
// FrameClock
// ==============

FrameClock frame_clock_create(f64 rate)
{
    FrameClock fc = {};
    fc.interval = (rate > 0.0) ? 1.0 / rate : 0.0;
    return fc;
}

void frame_clock_start(FrameClock *fc)
{
    f64 now = time_now_s();
    fc->last = fc->last == 0.0 ? now : fc->last + fc->delta;
    fc->delta = now - fc->last;
}

void frame_clock_wait(FrameClock *fc)
{
    if (fc->delta < fc->interval)
    {
        time_wait_s(fc->interval - fc->delta);
        fc->delta = time_now_s() - fc->last;
    }
}

void frame_clock_tick(FrameClock *fc)
{
    frame_clock_start(fc);
    frame_clock_wait(fc);
}

void frame_clock_set_rate(FrameClock *fc, f64 rate)
{
    fc->interval = (rate > 0.0) ? 1.0 / rate : 0.0;
}

// ==============
// FixedClock
// ==============

FixedClock fixed_clock_create(f64 rate)
{
    FixedClock sc = {};
    sc.interval = (rate > 0.0) ? 1.0 / rate : 1.0 / 60.0;
    return sc;
}

void fixed_clock_set_rate(FixedClock *sc, f64 rate)
{
    sc->interval = (rate > 0.0) ? 1.0 / rate : 1.0 / 60.0;
}

void fixed_clock_accumulate(FixedClock *sc, f64 delta)
{
    sc->accumulator += delta;
}

bool fixed_clock_consume(FixedClock *sc)
{
    if (sc->accumulator >= sc->interval)
    {
        sc->accumulator -= sc->interval;
        return true;
    }
    return false;
}

f64 fixed_clock_alpha(FixedClock *sc)
{
    return sc->accumulator / sc->interval;
}

// ==============
// ClockConfig
// ==============

ClockConfig clock_config_default(void)
{
    ClockConfig config = {
        .rise_alpha = 0.1,
        .fall_alpha = 0.1,
        .interval = 1.0
    };

    return config;
}

ClockConfig clock_config_create(f64 delta, f64 time_constant)
{
    ClockConfig config = {
        .rise_alpha = 1.0 - std::exp(-delta / time_constant),
        .fall_alpha = 1.0 - std::exp(-delta / time_constant),
        .interval = 1.0
    };

    return config;
}

void clock_config_set_alpha(ClockConfig *c, f64 alpha)
{
    if (!c)
        return;

    c->rise_alpha = alpha;
    c->fall_alpha = alpha;
}

void clock_config_set_interval(ClockConfig *c, f64 interval)
{
    if (!c)
        return;

    c->interval = interval;
}

void clock_config_set_rise_alpha(ClockConfig *c, f64 rise_alpha)
{
    if (!c)
        return;

    c->rise_alpha = rise_alpha;
}

void clock_config_set_fall_alpha(ClockConfig *c, f64 fall_alpha)
{
    if (!c)
        return;

    c->fall_alpha = fall_alpha;
}

// ==============
// ClockStats
// ==============

ClockStats clock_stats_create(void)
{
    ClockStats s = {};
    return s;
}

void clock_stats_reset(ClockStats *s)
{
    if (!s)
        return;

    *s = ClockStats{};
}

void clock_stats_sample(ClockStats *s, ClockConfig c, f64 delta, u64 ticks)
{
    if (!s)
        return;

    f64 instant_rate = (ticks > 0 && delta > 0.0) ? (f64)ticks / delta : 0.0;

    s->count += ticks;
    s->elapsed += delta;
    s->instant_rate = instant_rate;

    s->timer += delta;
    if (s->timer >= c.interval)
    {
        u64 rate = s->count - s->timer_count;
        s->rate = (f64)rate / s->timer;
        s->raw_rate = rate;
        s->timer_count = s->count;
        s->timer -= c.interval;
    }

    const f64 alpha = s->instant_rate > s->moving_average_rate ? c.rise_alpha : c.fall_alpha;
    s->running_average_rate = s->elapsed > 0.0 ? (f64)s->count / s->elapsed : 0.0;
    s->moving_average_rate = (s->instant_rate * alpha) + (s->moving_average_rate * (1.0 - alpha));
}