#include "time.h"
#include "../util/log.h"
#include <SDL3/SDL.h>

static struct
{
    bool initialized;
} g_timer_state = { 0 };

/*
 * =============================
 * -----------------------------
 * INIT
 * -----------------------------
 */

int time_init(void)
{
    g_timer_state.initialized = true;
    return 0;
}

void time_deinit(void)
{
    if (g_timer_state.initialized == false)
        return;

    g_timer_state.initialized = false;
}

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * GET TIME
 * -----------------------------
 */

u64 time_now(void)
{
    return (u64)SDL_GetTicksNS();
}

f64 time_now_s(void)
{
    const Uint64 t = SDL_GetTicksNS();
    return (f64)t / 1.0e9;
}

f64 time_now_ms(void)
{
    const Uint64 t = SDL_GetTicksNS();
    return (f64)t / 1.0e6;
}

f64 time_now_us(void)
{
    const Uint64 t = SDL_GetTicksNS();
    return (f64)t / 1.0e3;
}

f64 time_now_ns(void)
{
    const Uint64 t = SDL_GetTicksNS();
    return (f64)t / 1.0e0;
}

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * WAIT TIME
 * -----------------------------
 */

void time_wait(u64 ticks)
{
    const u64 stop_time = time_now() + ticks;
    SDL_Delay((Uint32)((ticks - (u64)(ticks * 0.1)) / 1000000));
    while (time_now() < stop_time);
}

void time_wait_s(f64 s)
{
    const u64 t = (u64)(s * 1.0e9);
    time_wait(t);
}

void time_wait_ms(f64 ms)
{
    const u64 t = (u64)(ms * 1.0e6);
    time_wait(t);
}

void time_wait_us(f64 us)
{
    const u64 t = (u64)(us * 1.0e3);
    time_wait(t);
}

void time_wait_ns(f64 ns)
{
    const u64 t = (u64)(ns * 1.0e0);
    time_wait(t);
}

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * CONVERT TIME TO TICKS
 * -----------------------------
 */

u64 time_stot(f64 s)
{
    return (u64)(s * 1.0e9);
}

u64 time_mstot(f64 ms)
{
    return (u64)(ms * 1.0e6);
}

u64 time_ustot(f64 us)
{
    return (u64)(us * 1.0e3);
}

u64 time_nstot(f64 ns)
{
    return (u64)(ns * 1.0e0);
}

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * CONVERT TICKS TO TIME
 * -----------------------------
 */

f64 time_ttos(u64 ticks)
{
    return (f64)ticks / 1.0e9;
}

f64 time_ttoms(u64 ticks)
{
    return (f64)ticks / 1.0e6;
}

f64 time_ttous(u64 ticks)
{
    return (f64)ticks / 1.0e3;
}

f64 time_ttons(u64 ticks)
{
    return (f64)ticks / 1.0e0;
}

/*
 * =============================
 */