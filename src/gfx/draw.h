#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>

#include "render.h"
#include "../util/util.h"

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

int draw_rectangle( struct rectangle *rectangle );
int draw_circle( struct circle *circle );
int draw_triangle( struct triangle *triangle );

int draw_filled_rectangle( struct rectangle *rectangle );
int draw_filled_circle( struct circle *circle );
int draw_filled_triangle( struct triangle *triangle );

#endif
