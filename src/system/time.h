#ifndef TIME_H
#define TIME_H

// units per second.
#define TIMESCALE 1.0f

#define NANOSECONDS( t )  ( ( double ) ( t ) * 1000000000.0 )
#define MICROSECONDS( t ) ( ( double ) ( t ) * 1000000.0	)
#define MILLISECONDS( t ) ( ( double ) ( t ) * 1000.0		)
#define SECONDS( t )      ( ( double ) ( t )           		)
#define MINUTES( t )      ( ( double ) ( t ) / 60.0    		)
#define HOURS( t )        ( ( double ) ( t ) / 3600.0  		)
#define DAYS( t )         ( ( double ) ( t ) / 86400.0 		)

#ifdef __cplusplus
extern "C" {
#endif

double time_elapsed( void );
void   time_delay( double s );

#ifdef __cplusplus
}
#endif

#endif
