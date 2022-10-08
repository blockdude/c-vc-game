#ifndef COMPONENT_H
#define COMPONENT_H

struct component_position
{
    double x;
    double y;
	double z;
};

struct component_velocity
{
    float vx;
    float vy;
    float vz;
};

struct component_direction
{
    float a;
};

struct component_camera
{
    double x;
    double y;

    float scale;
};

#endif
