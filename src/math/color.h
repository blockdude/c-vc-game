#ifndef VCP_COLOR_H
#define VCP_COLOR_H

#include "../vcp_common.h"
#include "../util/types.h"

static inline u32 rgba8888_to_uint32(u8 r, u8 g, u8 b, u8 a)
{
    u32 result = 0;
    result = (result | r) << 24;
    result = (result | g) << 16;
    result = (result | b) << 8;
    result = (result | a) << 0;
    return result;
}

static inline struct colorf colorf_mix(struct colorf a, struct colorf b, float ratio)
{
    struct colorf result;
    result.r = a.r * ratio + b.r * (1.0f - ratio);
    result.g = a.g * ratio + b.g * (1.0f - ratio);
    result.b = a.b * ratio + b.b * (1.0f - ratio);
    result.a = a.a * ratio + b.a * (1.0f - ratio);
    return result;
}

static inline struct colorf colorf_blend(struct colorf a, struct colorf b)
{
    struct colorf result;
    result.r = a.r * b.r;
    result.g = a.g * b.g;
    result.b = a.b * b.b;
    result.a = a.a * b.a;
    return result;
}

#endif