#ifndef VCP_TIME_H
#define VCP_TIME_H

#include "../common.h"
#include <stdint.h>

#define TIME_NS_PER_S  1000000000
#define TIME_NS_PER_MS 1000000
#define TIME_NS_PER_US 1000

extern int time_init( void );
extern void time_deinit( void );

extern uint64_t time_now( void );
extern double time_now_s( void );
extern double time_now_ms( void );
extern double time_now_us( void );
extern double time_now_ns( void );

extern void time_wait( uint64_t ticks );
extern void time_wait_s( double s );
extern void time_wait_ms( double ms );
extern void time_wait_us( double us );
extern void time_wait_ns( double ns );

extern uint64_t time_stot( double s );
extern uint64_t time_mstot( double ms );
extern uint64_t time_ustot( double us );
extern uint64_t time_nstot( double ns );

extern double time_ttos( uint64_t ticks );
extern double time_ttoms( uint64_t ticks );
extern double time_ttous( uint64_t ticks );
extern double time_ttons( uint64_t ticks );

#endif
