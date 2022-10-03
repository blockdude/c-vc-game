#ifndef COLOR_H
#define COLOR_H

#include "../util/util.h"

struct color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};
void color_split( u32 color, u8 *r, u8 *g, u8 *b, u8 *a );

#endif
