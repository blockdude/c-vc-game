#include <vcp/vcp.h>

struct FrameClock frame_clock_create(f64 rate)
{
    struct FrameClock fc = { 0 };
    fc.interval = (rate > 0.0) ? 1.0 / rate : 0.0;
    return fc;
}

void frame_clock_start(struct FrameClock *fc)
{
    fc->last = fc->now;
    fc->now = time_now_s();
    if (fc->last == 0.0)
        fc->last = fc->now;
    fc->delta = fc->now - fc->last;
}

void frame_clock_wait(struct FrameClock *fc)
{
    if (fc->delta < fc->interval)
    {
        time_wait_s(fc->interval - fc->delta);
        fc->now = time_now_s();
        fc->delta = fc->now - fc->last;
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

void clock_stats_sample_frame(struct ClockStats *s, struct FrameClock *fc)
{
    if (!s || !fc)
        return;

    s->count++;
    s->elapsed += fc->delta;
    s->instant_rate = 1.0 / fc->delta;

    s->timer += fc->delta;
    if (s->timer >= 1.0)
    {
        s->rate = s->count - s->timer_count;
        s->timer_count = s->count;
        s->timer = 0;
    }

    s->running_average_rate = s->elapsed > 0.0 ? s->count / s->elapsed : 0.0;

    f64 stiff = (fc->delta > 0.012) ? 0.1
              : (fc->delta > 0.004) ? 0.01
              : (fc->delta > 0.0004) ? 0.001
              : 0.0001;

    s->moving_average_rate = (s->instant_rate * stiff) + (s->moving_average_rate * (1.0 - stiff));
}

void clock_stats_sample_step(struct ClockStats *s, struct FixedClock *sc, int ticks)
{
    if (!s || !sc || ticks <= 0)
        return;

    f64 elapsed = sc->interval * ticks;
    s->count += ticks;
    s->elapsed += elapsed;
    s->instant_rate = 1.0 / sc->interval;

    s->timer += elapsed;
    if (s->timer >= 1.0)
    {
        s->rate = s->count - s->timer_count;
        s->timer_count = s->count;
        s->timer = 0;
    }

    s->running_average_rate = s->elapsed > 0.0 ? s->count / s->elapsed : 0.0;

    f64 stiff = (sc->interval > 0.012) ? 0.1
              : (sc->interval > 0.004) ? 0.01
              : (sc->interval > 0.0004) ? 0.001
              : 0.0001;

    s->moving_average_rate = (s->instant_rate * stiff) + (s->moving_average_rate * (1.0 - stiff));
}