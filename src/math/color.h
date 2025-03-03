#ifndef VCP_COLOR_H
#define VCP_COLOR_H

#include "../util/types.h"

static inline uint32_t rgba8888_to_u32( uint8_t r, uint8_t g, uint8_t b, uint8_t a )
{
    uint32_t result = 0;
    result = ( result | r ) << 24;
    result = ( result | g ) << 16;
    result = ( result | b ) << 8;
    result = ( result | a ) << 0;
    return result;
}

static inline struct color_f32 color_f32_mix( struct color_f32 a, struct color_f32 b, float ratio )
{
    struct color_f32 result = { 0 };

    result.r = a.r * ratio + b.r * ( 1.0f - ratio );
    result.g = a.g * ratio + b.g * ( 1.0f - ratio );
    result.b = a.b * ratio + b.b * ( 1.0f - ratio );
    result.a = a.a * ratio + b.a * ( 1.0f - ratio );

    return result;
}

static inline struct color_f32 color_f32_blend( struct color_f32 a, struct color_f32 b )
{
    struct color_f32 result = { 0 };

    result.r = a.r * b.r;
    result.g = a.g * b.g;
    result.b = a.b * b.b;
    result.a = a.a * b.a;

    return result;
}

#endif