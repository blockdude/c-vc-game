#ifndef MATH_H
#define MATH_H

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

#define LERP( a, b, t ) ( ( a ) + ( t ) * ( ( b ) - ( a ) ) )
#define NORMALIZE( x, min, max ) ( ( ( x ) - ( min ) ) / ( ( max ) - ( min ) ) )

/*
 * check if two floats are equal within an epsilon value
 */
static inline int flteq( float a, float b, float epsilon )
{
	int result = ( fabsf( a - b ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( a ), fabsf( b ) ) ) );
    return result;
}

#endif
