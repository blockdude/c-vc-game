#include <math.h>
#include "vc-util.h"

float magnitude( float x, float y )
{
    return sqrt( x * x + y * y );
}

void normalize( float *x, float *y )
{
    float xsq = ( *x ) * ( *x );
    float ysq = ( *y ) * ( *y );
    float mag = sqrt( xsq + ysq );

    *x = *x != 0 ? *x / mag : 0;
    *y = *y != 0 ? *y / mag : 0;
}

float min( float a, float b )
{
    return a < b ? a : b;
}

float max( float a, float b )
{
    return a > b ? a : b;
}

void split_color( int color, char *r, char *g, char *b, char *a )
{
    if ( r ) *r = color >> 24 & 0xff;
    if ( g ) *g = color >> 16 & 0xff;
    if ( b ) *b = color >> 8 & 0xff;
    if ( a ) *a = color & 0xff;
}
