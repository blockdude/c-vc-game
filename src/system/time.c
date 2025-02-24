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
    Uint64 t = SDL_GetTicksNS();
    return ( double ) t / 1.0e9;
}

double time_now_ms( void )
{
    Uint64 t = SDL_GetTicksNS();
    return ( double ) t / 1.0e6;
}

double time_now_us( void )
{
    Uint64 t = SDL_GetTicksNS();
    return ( double ) t / 1.0e3;
}

double time_now_ns( void )
{
    Uint64 t = SDL_GetTicksNS();
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

void time_wait( uint64_t ticks )
{
    SDL_DelayNS( ticks );
}

void time_wait_s( double s )
{
    Uint64 t = ( Uint64 ) ( s * 1.0e9 );
    SDL_DelayNS( t );
}

void time_wait_ms( double ms )
{
    Uint64 t = ( Uint64 ) ( ms * 1.0e6 );
    SDL_DelayNS( t );
}

void time_wait_us( double us )
{
    Uint64 t = ( Uint64 ) ( us * 1.0e3 );
    SDL_DelayNS( t );
}

void time_wait_ns( double ns )
{
    Uint64 t = ( Uint64 ) ( ns * 1.0e0 );
    SDL_DelayNS( t );
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

uint64_t time_stot( double s )
{
    return ( uint64_t ) ( s * 1.0e9 );
}

uint64_t time_mstot( double ms )
{
    return ( uint64_t ) ( ms * 1.0e6 );
}

uint64_t time_ustot( double us )
{
    return ( uint64_t ) ( us * 1.0e3 );
}

uint64_t time_nstot( double ns )
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

double time_ttos( uint64_t ticks )
{
    return ( double ) ticks / 1.0e9;
}

double time_ttoms( uint64_t ticks )
{
    return ( double ) ticks / 1.0e6;
}

double time_ttous( uint64_t ticks )
{
    return ( double ) ticks / 1.0e3;
}

double time_ttons( uint64_t ticks )
{
    return ( double ) ticks / 1.0e0;
}

/*
 * =============================
 */