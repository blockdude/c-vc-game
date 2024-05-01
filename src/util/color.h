#ifndef COLOR_H
#define COLOR_H

#include "types.h"

struct color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};
void color_split( uint32_t color, uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *a );

#endif
