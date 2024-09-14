#ifndef COLOR_H
#define COLOR_H

#include <util/types.h>
#include "math.h"

static inline color_t color_mix( color_t a, color_t b, float r )
{
    color_t result = { 0 };

    result.r = a.r * r + b.r * ( 1.0f - r );
    result.g = a.g * r + b.g * ( 1.0f - r );
    result.b = a.b * r + b.b * ( 1.0f - r );
    result.a = a.a * r + b.a * ( 1.0f - r );

    return result;
}

static inline color_t color_blend( color_t a, color_t b )
{
    color_t result = { 0 };

    result.r = a.r * b.r;
    result.g = a.g * b.g;
    result.b = a.b * b.b;
    result.a = a.a * b.a;

    return result;
}

#endif
