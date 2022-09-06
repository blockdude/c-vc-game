#ifndef PHYSICS_H
#define PHYSICS_H

#include "../util/util.h"

struct component_physics
{
    // velocity vector
    f32 dx;
    f32 dy;

    // do collision
    bool collision;

    // do drag
    bool drag;

    // hitbox template
    f32 hitbox[ 2 ][ 8 ];
};

#endif
