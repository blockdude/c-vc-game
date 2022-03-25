#include "math.h"
#include "util.h"

float magnitude( float x, float y )
{
    return sqrt( x * x + y * y );
}

void normalize( float x, float y, float *x_out, float *y_out )
{
    float mag = sqrt( x * x + y * y );
    if ( x_out ) *x_out = x != 0 ? x / mag : 0;
    if ( y_out ) *y_out = y != 0 ? y / mag : 0;
}

inline float min( float a, float b )
{
    return ( a < b ? a : b );
}

inline float max( float a, float b )
{
    return ( a > b ? a : b );
}

inline float clamp( float val, float min, float max )
{
    float t = val < min ? min : val;
    return t > max ? max : t;
}

void split_color( int color, char *r, char *g, char *b, char *a )
{
    if ( r ) *r = color >> 24 & 0xff;
    if ( g ) *g = color >> 16 & 0xff;
    if ( b ) *b = color >> 8 & 0xff;
    if ( a ) *a = color & 0xff;
}

void center_pos( float x, float y, float *x_out, float *y_out )
{
    if ( x_out ) *x_out = x + 0.5f;
    if ( y_out ) *y_out = y + 0.5f;
}
