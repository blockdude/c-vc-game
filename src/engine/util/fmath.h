#ifndef FMATH_H
#define FMATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>

#define PI_2 GLM_PI_2
#define PI GLM_PI
#define TAU ( 2 * PI )

#define clamp( v, mn, mx ) max( mn, min( mx, v ) )

#ifndef __cplusplus
#define max( a, b ) ( ( a ) > ( b ) ? ( a ) : ( b ) )
#define min( a, b ) ( ( a ) < ( b ) ? ( a ) : ( b ) )
#endif

#define degtorad( x ) ( ( x ) * ( PI / 180.0f ) )
#define radtodeg( x ) ( ( x ) * ( 180.0f / PI ) )

static inline int fltcmp( float x, float y, float epsilon )
{
    return ( fabs( x - y ) <= epsilon );
}

static inline float magnitude( float x, float y )
{
    return sqrt( x * x + y * y );
}

static inline void normalize( float x, float y, float *x_norm, float *y_norm )
{
    float mag = sqrt( x * x + y * y );
    if ( x_norm ) *x_norm = x != 0 ? x / mag : 0;
    if ( y_norm ) *y_norm = y != 0 ? y / mag : 0;
}

#ifdef __cplusplus
}
#endif

#endif
