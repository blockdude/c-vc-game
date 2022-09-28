#ifndef COLOR_H
#define COLOR_H

#include "../util/util.h"

union color
{
    struct
    {
        u8 r;
        u8 g;
        u8 b;
        u8 a;
    } val;

    u32 raw;
};

void color_split( u32 color, u8 *r, u8 *g, u8 *b, u8 *a );

#endif
