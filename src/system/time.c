#include "time.h"
#include "../internal.h"
#include "../util/log.h"
#include <SDL3/SDL.h>

/*
 * =============================
 * -----------------------------
 * INIT
 * -----------------------------
 */

int time_init( void )
{
    if ( SDL_InitSubSystem( SDL_INIT_TIMER ) != 0 )
    {
        log_warn( "Unable to initialize SDL timer system: %s", SDL_GetError() );
        return -1;
    }

    core.timer.initialized = true;
    return 0;
}

void time_deinit( void )
{
    if ( core.timer.initialized == false )
        return;

    SDL_QuitSubSystem( SDL_INIT_TIMER );
    core.timer.initialized = false;
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