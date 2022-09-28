#include "color.h"

void color_split( u32 color, u8 *r, u8 *g, u8 *b, u8 *a )
{
    if ( r ) *r = color >> 24 & 0xff;
    if ( g ) *g = color >> 16 & 0xff;
    if ( b ) *b = color >> 8 & 0xff;
    if ( a ) *a = color & 0xff;
}
