#ifndef UTIL_H
#define UTIL_H

#include <math.h>

#ifdef WIN32

#undef MIN
#undef MAX

#endif

#define EULER   2.71828182845904523536028747135266249f
#define PI_2    1.57079632679489661923132169163975144f
#define PI      3.14159265358979323846264338327950288f
#define TAU     6.28318530717958647692528676655900576f
#define EPSILON 0.0001f

#define CLAMP( v, mn, mx ) MAX( mn, MIN( mx, v ) )

#define MAX( a, b ) ( ( a ) > ( b ) ? ( a ) : ( b ) )
#define MIN( a, b ) ( ( a ) < ( b ) ? ( a ) : ( b ) )

#define DEGTORAD( x ) ( ( x ) * ( PI / 180.0f ) )
#define RADTODEG( x ) ( ( x ) * ( 180.0f / PI ) )

/*
 * linear interpolation
 */
static inline float llerp( float a, float b, float t )
{
	return a + t * ( b - a );
}

/*
 * normalize input between 0 and 1
 */
static inline float normalize( float x, float min, float max )
{
	return ( x - min ) / ( max - min );
}

/*
 * check if two floats are equal within an epsilon value
 */
static inline int flteq( float a, float b, float epsilon )
{
	int result = ( fabsf( a - b ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( a ), fabsf( b ) ) ) );
    return result;
}

#endif
