#ifndef CAMERA_H
#define CAMERA_H

#include "../util/util.h"

struct component_camera
{
    double x;
    double y;

    int offset_x;
    int offset_y;

    float zoom_level;
};

#endif
