#ifndef FMATH_H
#define FMATH_H

#include <math.h>
#include <float.h>

#ifdef WIN32
#undef min
#undef max
#endif

#define PI_2 GLM_PI_2
#define PI   GLM_PI
#define TAU  ( 2 * PI )

#define clamp( v, mn, mx ) max( mn, min( mx, v ) )

#ifndef __cplusplus
#define max( a, b ) ( ( a ) > ( b ) ? ( a ) : ( b ) )
#define min( a, b ) ( ( a ) < ( b ) ? ( a ) : ( b ) )
#endif

#define degtorad( x ) ( ( x ) * ( PI / 180.0f ) )
#define radtodeg( x ) ( ( x ) * ( 180.0f / PI ) )

#ifdef __cplusplus
extern "C" {
#endif

static inline int fltcmp( double a, double b, double epsilon )
{
	const float ab_a = fabs( a );
	const float ab_b = fabs( b );
	const float diff = ( a - b );

	if ( a == b )
		return 1;

	if ( a == 0 || b == 0 || ( ab_a + ab_b < DBL_MIN ) )
		return diff < ( epsilon * DBL_MIN );

	return diff / fmin( ( ab_a + ab_b ), DBL_MAX ) < epsilon;
}

#ifdef __cplusplus
}
#endif

#endif
