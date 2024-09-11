#ifndef TIME_H
#define TIME_H

// units per second.
#define TIMESCALE 1.0f

#ifdef __cplusplus
extern "C" {
#endif

#define NANOSECONDS( t )  ( ( double ) ( t ) * 1000000000.0 )
#define MICROSECONDS( t ) ( ( double ) ( t ) * 1000000.0	)
#define MILLISECONDS( t ) ( ( double ) ( t ) * 1000.0		)
#define SECONDS( t )      ( ( double ) ( t )           		)
#define MINUTES( t )      ( ( double ) ( t ) / 60.0    		)
#define HOURS( t )        ( ( double ) ( t ) / 3600.0  		)
#define DAYS( t )         ( ( double ) ( t ) / 86400.0 		)

double time_ticks( void );
void   time_delay( double s );

#ifdef __cplusplus
}
#endif

#endif
