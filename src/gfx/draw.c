#include "draw.h"

int draw_rectangle( struct rectangle *rectangle )
{
	SDL_FRect r = {
		.x = rectangle->x,
		.y = rectangle->y,
		.w = rectangle->w,
		.h = rectangle->h
	};

	return SDL_RenderDrawRectF( render.handle, &r );
}

int draw_circle( struct circle *circle );
int draw_triangle( struct triangle *triangle );
