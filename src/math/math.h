#ifndef VCP_MATH_H
#define VCP_MATH_H

#include <math.h>
#include "../util/types.h"

#ifdef WIN32

#undef MIN
#undef MAX
#undef min
#undef max

#endif

#define EULER   2.71828182845904523536028747135266249
#define PI_2    1.57079632679489661923132169163975144
#define PI      3.14159265358979323846264338327950288
#define TAU     6.28318530717958647692528676655900576
#define EPSILON 0.0001

#define MAX( a, b ) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )
#define MIN( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )

#define CLAMP( v, mn, mx ) MAX( mn, MIN( mx, v ) )

#define DEGTORAD( x ) ( ( x ) * ( PI / 180.0 ) )
#define RADTODEG( x ) ( ( x ) * ( 180.0 / PI ) )

#define LERP( a, b, t ) ( ( a ) + ( t ) * ( ( b ) - ( a ) ) )
#define NORMALIZE( x, min, max ) ( ( ( x ) - ( min ) ) / ( ( max ) - ( min ) ) )

#define _MATH_FUNC_DECL_INT_DIVIDE_AND_ROUND( T, _name ) \
static inline T _name##_divide_and_round( const T n, const T d ) { return ( ( n < 0 ) == ( d < 0 ) ) ? ( ( n + d / 2 ) / d ) : ( ( n - d / 2 ) / d ); }

_MATH_FUNC_DECL_INT_DIVIDE_AND_ROUND( int, int );
_MATH_FUNC_DECL_INT_DIVIDE_AND_ROUND( i32, int32 );
_MATH_FUNC_DECL_INT_DIVIDE_AND_ROUND( i64, int64 );

#define _MATH_FUNC_DECL_INT_DIVIDE_AND_FLOOR( T, _name ) \
static inline T _name##_divide_and_floor( const T n, const T d ) { return ( n / d ) - ( n < 0 ); }

_MATH_FUNC_DECL_INT_DIVIDE_AND_FLOOR( int, int );
_MATH_FUNC_DECL_INT_DIVIDE_AND_FLOOR( i32, int32 );
_MATH_FUNC_DECL_INT_DIVIDE_AND_FLOOR( i64, int64 );

#define _MATH_FUNC_DECL_FLOAT_EQUALS( T, _name, _abs_fn, _max_fn ) \
static inline int _name##_equals( const T a, const T b, const T epsilon ) { return ( _abs_fn( a - b ) ) <= ( epsilon * _max_fn( 1.0f, _max_fn( _abs_fn( a ), _abs_fn( b ) ) ) ); }

_MATH_FUNC_DECL_FLOAT_EQUALS( float, float, fabsf, fmaxf );
_MATH_FUNC_DECL_FLOAT_EQUALS( f32, float32, fabsf, fmaxf );
_MATH_FUNC_DECL_FLOAT_EQUALS( f64, float64, fabs, fmax );

#endif
