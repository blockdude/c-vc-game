#ifndef CAMERA_H
#define CAMERA_H

#include "../util/util.h"

struct component_camera
{
    f64 x;
    f64 y;

    int offset_x;
    int offset_y;

    float zoom_level;
};

#endif
