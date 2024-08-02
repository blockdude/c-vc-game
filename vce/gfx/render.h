#ifndef RENDER_H
#define RENDER_H

#include <gfx/shape.h>
#include <util/util.h>
#include <SDL3/SDL.h>

#define RENDER_SUCCESS	0
#define RENDER_ERROR	-1

struct render
{
	SDL_Renderer *handle;
};

#ifdef __cplusplus
extern "C" {
#endif

// global render context
extern struct render render;

int render_init( void );
int render_free( void );

/*
 * drawing stuff
 */

int render_set_color( uint8_t r, uint8_t g, uint8_t b, uint8_t a );
int render_clear( void );
int render_present( void );

int render_line( struct line line );
int render_rectangle( struct rectangle rectangle );
int render_circle( struct circle circle );
int render_triangle( struct triangle triangle );

int render_filled_rectangle( struct rectangle rectangle );
int render_filled_circle( struct circle circle );
int render_filled_triangle( struct triangle triangle );

#ifdef __cplusplus
}
#endif

#endif
