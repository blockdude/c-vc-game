#ifndef VCP_TIME_H
#define VCP_TIME_H

#include "../common.h"

#define TIME_NS_PER_S  1000000000
#define TIME_NS_PER_MS 1000000
#define TIME_NS_PER_US 1000

extern int time_init( void );
extern void time_deinit( void );

extern u64 time_now( void );
extern f64 time_now_s( void );
extern f64 time_now_ms( void );
extern f64 time_now_us( void );
extern f64 time_now_ns( void );

extern void time_wait( u64 ticks );
extern void time_wait_s( f64 s );
extern void time_wait_ms( f64 ms );
extern void time_wait_us( f64 us );
extern void time_wait_ns( f64 ns );

extern u64 time_stot( f64 s );
extern u64 time_mstot( f64 ms );
extern u64 time_ustot( f64 us );
extern u64 time_nstot( f64 ns );

extern f64 time_ttos( u64 ticks );
extern f64 time_ttoms( u64 ticks );
extern f64 time_ttous( u64 ticks );
extern f64 time_ttons( u64 ticks );

#endif
