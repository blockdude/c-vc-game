#include "color.h"

void color_split( uint32_t color, uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *a )
{
    if ( r ) *r = color >> 24 & 0xff;
    if ( g ) *g = color >> 16 & 0xff;
    if ( b ) *b = color >> 8 & 0xff;
    if ( a ) *a = color & 0xff;
}
