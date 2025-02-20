#ifndef VCP_TIME_H
#define VCP_TIME_H

#include "../common.h"
#include <stdint.h>

#define TIME_NS_PER_S  1000000000
#define TIME_NS_PER_MS 1000000
#define TIME_NS_PER_US 1000

int time_init( void );
void time_deinit( void );

uint64_t time_now( void );
double time_now_s( void );
double time_now_ms( void );
double time_now_us( void );
double time_now_ns( void );

void time_wait( uint64_t ticks );
void time_wait_s( double s );
void time_wait_ms( double ms );
void time_wait_us( double us );
void time_wait_ns( double ns );

uint64_t time_stot( double s );
uint64_t time_mstot( double ms );
uint64_t time_ustot( double us );
uint64_t time_nstot( double ns );

double time_ttos( uint64_t ticks );
double time_ttoms( uint64_t ticks );
double time_ttous( uint64_t ticks );
double time_ttons( uint64_t ticks );

#endif
