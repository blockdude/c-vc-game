#ifndef VCP_MATH_H
#define VCP_MATH_H

#include "float32/math_f32.h"
#include "float64/math_f64.h"

#ifdef WIN32

#undef MIN
#undef MAX

#endif

#define EULER   2.71828182845904523536028747135266249
#define PI_2    1.57079632679489661923132169163975144
#define PI      3.14159265358979323846264338327950288
#define TAU     6.28318530717958647692528676655900576
#define EPSILON 0.0001

#define MAX( a, b ) ( ( a ) > ( b ) ? ( a ) : ( b ) )
#define MIN( a, b ) ( ( a ) < ( b ) ? ( a ) : ( b ) )

#define CLAMP( v, mn, mx ) MAX( mn, MIN( mx, v ) )

#define DEGTORAD( x ) ( ( x ) * ( PI / 180.0 ) )
#define RADTODEG( x ) ( ( x ) * ( 180.0 / PI ) )

#define LERP( a, b, t ) ( ( a ) + ( t ) * ( ( b ) - ( a ) ) )
#define NORMALIZE( x, min, max ) ( ( ( x ) - ( min ) ) / ( ( max ) - ( min ) ) )

#endif
