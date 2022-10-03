#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../util/util.h"

struct component_movement
{
    float speed;

    // change to a vector
    bool up;
    bool down;
    bool left;
    bool right;

    // like this
    float dx;
    float dy;
};

#endif
