#ifndef SDL_DRAW_MY_COOL_PRIMITIVES
#define SDL_DRAW_MY_COOL_PRIMITIVES

#include <SDL2/SDL.h>
#include "primitives.h"

int draw_polygon								(SDL_Renderer *renderer, const struct polygon *p);
int draw_polygon_filled					   (SDL_Renderer *renderer, const struct polygon *p);

#endif
