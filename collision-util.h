#ifndef COLLISION_UTIL
#define COLLISION_UTIL

int pt_in_rect( int ax, int ay, int bx, int by, int w, int h )
{
    return ( ax >= bx && ax <= bx + w && ay >= by && ay <= by + h );
}

int pt_in_rect_f( int ax, int ay, float bx, float by, float w, float h )
{
    return ( ax >= bx && ax <= bx + w && ay >= by && ay <= by + h );
}

#endif
