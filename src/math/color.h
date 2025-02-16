#ifndef COLOR_H
#define COLOR_H

#include <util/types.h>

static inline color_t color_mix( color_t a, color_t b, float ratio )
{
    color_t result = { 0 };

    result.r = a.r * ratio + b.r * ( 1.0f - ratio );
    result.g = a.g * ratio + b.g * ( 1.0f - ratio );
    result.b = a.b * ratio + b.b * ( 1.0f - ratio );
    result.a = a.a * ratio + b.a * ( 1.0f - ratio );

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
