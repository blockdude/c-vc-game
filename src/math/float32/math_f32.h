#ifndef MATH_F32_H
#define MATH_F32_H

#include <math.h>

static inline int f32_equals( float a, float b, float epsilon )
{
    int result = ( fabsf( a - b ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( a ), fabsf( b ) ) ) );
    return result;
}

#endif