#ifndef RENDER_H
#define RENDER_H

#include "../util/util.h"
#include "../world/world.h"
#include <SDL2/SDL.h>

#define RENDER_SUCCESS	0
#define RENDER_ERROR	-1

extern const u32 g_render_flags;

struct render
{
	SDL_Renderer *handle;
};

// global render context
extern struct render render;

int render_init( void );
int render_free( void );

/*
 * drawing stuff
 */

int render_set_color( u8 r, u8 g, u8 b, u8 a );
int render_clear( void );
int render_present( void );

int render_line( float x0, float y0, float x1, float y1 );
int render_rectangle( struct rectangle rectangle );
int render_circle( struct circle circle );
int render_triangle( struct triangle triangle );

int render_filled_rectangle( struct rectangle rectangle );
int render_filled_circle( struct circle circle );
int render_filled_triangle( struct triangle triangle );

#endif
