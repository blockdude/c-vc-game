#ifndef MATH_F64_H
#define MATH_F64_H

#include <math.h>

static inline int f64_equals( double a, double b, double epsilon )
{
    int result = ( fabs( a - b ) ) <= ( epsilon * fmax( 1.0f, fmax( fabs( a ), fabs( b ) ) ) );
    return result;
}

#endif