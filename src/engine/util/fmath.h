#ifndef FMATH_H
#define FMATH_H

#include <math.h>
#include <float.h>

#ifdef WIN32

#undef MIN
#undef MAX

#endif

#define PI_2    1.57079632679489661923132169163975144f
#define PI      3.14159265358979323846264338327950288f
#define TAU     6.28318530717958647692528676655900576f
#define EPSILON 0.000001f

#define CLAMP( v, mn, mx ) MAX( mn, MIN( mx, v ) )

#define MAX( a, b ) ( ( a ) > ( b ) ? ( a ) : ( b ) )
#define MIN( a, b ) ( ( a ) < ( b ) ? ( a ) : ( b ) )

#define DEGTORAD( x ) ( ( x ) * ( PI / 180.0f ) )
#define RADTODEG( x ) ( ( x ) * ( 180.0f / PI ) )

/*
 * for when i am ready
 */

/*

typedef struct vec2
{
	float x;
	float y;
} vec2;

typedef struct vec3
{
	float x;
	float y;
	float z;
} vec3;

typedef struct vec4
{
	float x;
	float y;
	float z;
	float w;
} vec4;

typedef vec4 quat;

typedef struct mat4
{
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;
} mat4;

*/

static inline int fltcmp( float a, float b, float epsilon )
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

#endif
