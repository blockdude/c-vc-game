#ifndef COMPONENT_H
#define COMPONENT_H

typedef struct position
{
    double x;
    double y;
	double z;
} position;

typedef struct velocity
{
    float x;
    float y;
    float z;
} velocity;

typedef struct camera
{
    double x;
    double y;

    float scale;
} camera;

#endif
