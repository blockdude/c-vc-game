#ifndef RENDER_H
#define RENDER_H

#include "../util/util.h"
#include "../world/world.h"
#include <SDL2/SDL.h>

extern const u32 g_render_flags;

struct render
{
	SDL_Renderer *handle;
	struct world *world;
};

// global render context
extern struct render render;

int render_init( struct world *world );
int render_free( void );

int render_set_color( u8 r, u8 g, u8 b, u8 a );
int render_clear( void );
int render_present( void );

#endif
