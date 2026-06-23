#include <vcp/vcp.h>

struct FrameClock frame_clock_create(f64 rate)
{
    struct FrameClock fc = { 0 };
    fc.interval = (rate > 0.0) ? 1.0 / rate : 0.0;
    return fc;
}

void frame_clock_start(struct FrameClock *fc)
{
    f64 now = time_now_s();
    fc->last = fc->last == 0.0 ? now : fc->last + fc->delta;
    fc->delta = now - fc->last;
}

void frame_clock_wait(struct FrameClock *fc)
{
    if (fc->delta < fc->interval)
    {
        time_wait_s(fc->interval - fc->delta);
        fc->delta = time_now_s() - fc->last;
    }
}

void frame_clock_tick(struct FrameClock *fc)
{
    frame_clock_start(fc);
    frame_clock_wait(fc);
}

void frame_clock_set_rate(struct FrameClock *fc, f64 rate)
{
    fc->interval = (rate > 0.0) ? 1.0 / rate : 0.0;
}

struct FixedClock fixed_clock_create(f64 rate)
{
    struct FixedClock sc = { 0 };
    sc.interval = (rate > 0.0) ? 1.0 / rate : 1.0 / 60.0;
    return sc;
}

void fixed_clock_set_rate(struct FixedClock *sc, f64 rate)
{
    sc->interval = (rate > 0.0) ? 1.0 / rate : 1.0 / 60.0;
}

void fixed_clock_accumulate(struct FixedClock *sc, f64 dt)
{
    sc->accumulator += dt;
}

bool fixed_clock_consume(struct FixedClock *sc)
{
    if (sc->accumulator >= sc->interval)
    {
        sc->accumulator -= sc->interval;
        return true;
    }
    return false;
}

f64 fixed_clock_alpha(struct FixedClock *sc)
{
    return sc->accumulator / sc->interval;
}

static inline f64
stiff_clamp(f64 v, f64 mn, f64 mx)
{
    return CLAMP(v, mn, mx);
}

static inline void
clock_stats_update(struct ClockStats *s, u64 count, f64 delta)
{
    f64 elapsed = (f64)count * delta;
    f64 instant_rate = delta > 0.0 ? 1.0 / delta : 0.0;

    s->count      += count;
    s->elapsed    += elapsed;
    s->instant_rate = instant_rate;

    s->timer += elapsed;
    if (s->timer >= 1.0)
    {
        s->rate = s->count - s->timer_count;
        s->timer_count = s->count;
        s->timer = 0;
    }

    const f64 stiff = stiff_clamp(s->ceil * pow(1.0 - exp(-elapsed / s->tau), s->power), 0.0, 1.0);
    s->running_average_rate = s->elapsed > 0.0 ? (f64)s->count / s->elapsed : 0.0;
    s->moving_average_rate = (s->instant_rate * stiff) + (s->moving_average_rate * (1.0 - stiff));
}

struct ClockStats clock_stats_create(f64 ceil, f64 tau, f64 power)
{
    struct ClockStats s = { 0 };
    s.ceil = ceil;
    s.tau = tau;
    s.power = power;
    return s;
}

struct ClockStats clock_stats_create_default(void)
{
    return clock_stats_create(1.08, 0.07, 1.50);
}

void clock_stats_reset(struct ClockStats *s)
{
    if (!s)
        return;

    f64 ceil  = s->ceil;
    f64 tau   = s->tau;
    f64 power = s->power;

    *s = (struct ClockStats){ 0 };

    s->ceil  = ceil;
    s->tau   = tau;
    s->power = power;
}

void clock_stats_sample_frame(struct ClockStats *s, const struct FrameClock *fc)
{
    if (!s || !fc)
        return;

    clock_stats_update(s, 1, fc->delta);
}

void clock_stats_sample_fixed(struct ClockStats *s, const struct FixedClock *sc, u64 ticks)
{
    if (!s || !sc || ticks == 0)
        return;

    clock_stats_update(s, ticks, sc->interval);
}