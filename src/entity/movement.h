#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../util/util.h"

struct component_movement
{
    f32 speed;

    // change to a vector
    bool up;
    bool down;
    bool left;
    bool right;

    // like this
    f32 dx;
    f32 dy;
};

#endif
