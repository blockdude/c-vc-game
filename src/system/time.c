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

int time_init( void )
{
    g_timer_state.initialized = true;
    return 0;
}

void time_deinit( void )
{
    if ( g_timer_state.initialized == false )
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

uint64_t time_now( void )
{
    return SDL_GetTicksNS();
}

double time_now_s( void )
{
    const Uint64 t = SDL_GetTicksNS();
    return ( double ) t / 1.0e9;
}

double time_now_ms( void )
{
    const Uint64 t = SDL_GetTicksNS();
    return ( double ) t / 1.0e6;
}

double time_now_us( void )
{
    const Uint64 t = SDL_GetTicksNS();
    return ( double ) t / 1.0e3;
}

double time_now_ns( void )
{
    const Uint64 t = SDL_GetTicksNS();
    return ( double ) t / 1.0e0;
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

void time_wait( const uint64_t ticks )
{
    const uint64_t stop_time = time_now() + ticks;
    const Uint32 sleep_time = ( Uint32 ) ( ( ticks - ( uint64_t ) ( ticks * 0.1 ) ) / 1000000i64 );
    SDL_Delay( sleep_time );
    while ( time_now() < stop_time );
}

void time_wait_s( const double s )
{
    const Uint64 t = ( Uint64 ) ( s * 1.0e9 );
    time_wait( t );
}

void time_wait_ms( const double ms )
{
    const Uint64 t = ( Uint64 ) ( ms * 1.0e6 );
    time_wait( t );
}

void time_wait_us( const double us )
{
    const Uint64 t = ( Uint64 ) ( us * 1.0e3 );
    time_wait( t );
}

void time_wait_ns( const double ns )
{
    const Uint64 t = ( Uint64 ) ( ns * 1.0e0 );
    time_wait( t );
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

uint64_t time_stot( const double s )
{
    return ( uint64_t ) ( s * 1.0e9 );
}

uint64_t time_mstot( const double ms )
{
    return ( uint64_t ) ( ms * 1.0e6 );
}

uint64_t time_ustot( const double us )
{
    return ( uint64_t ) ( us * 1.0e3 );
}

uint64_t time_nstot( const double ns )
{
    return ( uint64_t ) ( ns * 1.0e0 );
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

double time_ttos( const uint64_t ticks )
{
    return ( double ) ticks / 1.0e9;
}

double time_ttoms( const uint64_t ticks )
{
    return ( double ) ticks / 1.0e6;
}

double time_ttous( const uint64_t ticks )
{
    return ( double ) ticks / 1.0e3;
}

double time_ttons( const uint64_t ticks )
{
    return ( double ) ticks / 1.0e0;
}

/*
 * =============================
 */