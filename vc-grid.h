#ifndef VC_GRID
#define VC_GRID

#include <SDL2/SDL.h>
#include "vc-world.h"

extern float scale_x;
extern float scale_y;
extern float camera_x;
extern float camera_y;
extern SDL_Rect view;

void screen_to_world( int screen_x, int screen_y, float *world_x, float *world_y );
void screen_to_world_f( float screen_x, float screen_y, float *world_x, float *world_y );

void world_to_screen( float world_x, float world_y, int *screen_x, int *screen_y );
void world_to_screen_f( float world_x, float world_y, float *screen_x, float *screen_y );

void draw_object( SDL_Renderer *renderer, vc_object *object );
void draw_circle_f( SDL_Renderer *renderer, float x0, float y0, float r );

#endif
