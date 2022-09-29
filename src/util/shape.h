#ifndef SHAPE_H
#define SHAPE_H

struct point
{
	float x, y;
};

struct line
{
	float x0, y0;
	float x1, y1;
};

struct rectangle
{
	float x;
	float y;
	float w;
	float h;
};

struct circle
{
	float x;
	float y;
	float r;
};

struct triangle
{
	float x0, y0;
	float x1, y1;
	float x2, y2;
};

#endif
