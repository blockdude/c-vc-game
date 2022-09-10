#include "tile.h"

static struct tile tiles[ TILE_COUNT_MAX ];
static struct tile default_tile = {
	.id         = 0,
	.liquid     = false,
	.animated   = false,
	.solid      = true,
	.collides   = false,
	.use_color  = false,
	.color      = 0,
	.drag       = 1.0f,
	.slip       = 1.0f,
	.width      = 1.0f,
	.height     = 1.0f,
	.offset_x   = 0.0f,
	.offset_y   = 0.0f,
	.texture    = NULL
};

#define TILE_DECL( name ) \
	extern void name##_init( void ); \
	name##_init();

void tile_init( void )
{
	TILE_DECL( air );
	TILE_DECL( grass );
	TILE_DECL( dirt );
	TILE_DECL( sand );
	TILE_DECL( mud );
	TILE_DECL( stone );
	TILE_DECL( cobblestone );

	TILE_DECL( water );
	TILE_DECL( lava );
}

struct tile *tile_new( char *name )
{
	// track next available id
	static int next_id = 0;

	// don't create new tile type when no available ids
	if ( next_id >= TILE_COUNT_MAX )
		return NULL;

	// set tile id and return
	struct tile *new_tile = &tiles[ next_id ];
	new_tile->id = next_id++;
	return new_tile;
}

struct tile *tile_get( enum tile_id id )
{
	return &tiles[ id ];
}
