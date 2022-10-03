#ifndef PHYSICS_H
#define PHYSICS_H

#include "../util/util.h"

struct component_physics
{
    // velocity vector
    float dx;
    float dy;
    float dz;

    // do collision
    bool collision;

    // do drag
    bool drag;

    // hitbox template
    float hitbox[ 2 ][ 8 ];
};

#endif
