#ifndef FMATH_H
#define FMATH_H

#include <math.h>

#define PI 3.1415926535897932384626433832795f

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

static inline float clamp( float val, float min, float max )
{
    float t = val < min ? min : val;
    return t > max ? max : t;
}

static inline float f32min( float a, float b )
{
    return ( a < b ? a : b );
}

static inline float f32max( float a, float b )
{
    return ( a > b ? a : b );
}

#endif
