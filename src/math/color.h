#ifndef VCP_COLOR_H
#define VCP_COLOR_H

#include "../util/types.h"

static inline u32 rgba8888_to_uint32(const u8 r, const u8 g, const u8 b, const u8 a)
{
    u32 result = 0;
    result = (result | r) << 24;
    result = (result | g) << 16;
    result = (result | b) << 8;
    result = (result | a) << 0;
    return result;
}

static inline struct colorf colorf_mix(const struct colorf a, const struct colorf b, const float ratio)
{
    struct colorf result = { 0 };
    result.r = a.r * ratio + b.r * (1.0f - ratio);
    result.g = a.g * ratio + b.g * (1.0f - ratio);
    result.b = a.b * ratio + b.b * (1.0f - ratio);
    result.a = a.a * ratio + b.a * (1.0f - ratio);
    return result;
}

static inline struct colorf colorf_blend(const struct colorf a, const struct colorf b)
{
    struct colorf result = { 0 };
    result.r = a.r * b.r;
    result.g = a.g * b.g;
    result.b = a.b * b.b;
    result.a = a.a * b.a;
    return result;
}

#endif