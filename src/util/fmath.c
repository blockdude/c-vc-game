#include <math.h>
#include "fmath.h"

float magnitude( float x, float y )
{
    return sqrt( x * x + y * y );
}

void normalize( float x, float y, float *x_norm, float *y_norm )
{
    float mag = sqrt( x * x + y * y );
    if ( x_norm ) *x_norm = x != 0 ? x / mag : 0;
    if ( y_norm ) *y_norm = y != 0 ? y / mag : 0;
}

float clamp( float val, float min, float max )
{
    float t = val < min ? min : val;
    return t > max ? max : t;
}

float min( float a, float b )
{
    return ( a < b ? a : b );
}

float max( float a, float b )
{
    return ( a > b ? a : b );
}

void center_pos( float x, float y, float *x_out, float *y_out )
{
    if ( x_out ) *x_out = x + 0.5f;
    if ( y_out ) *y_out = y + 0.5f;
}

float center_x( float x )
{
    return x + 0.5f;
}

float center_y( float y )
{
    return y + 0.5f;
}
