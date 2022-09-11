#ifndef TILE_H
#define TILE_H

#include "../../util/util.h"

#define TILE_COUNT_MAX		256

enum tile_id
{
	// first tile id
    TILE_FIRST = 0,

	// default
	TILE_DEFAULT = 0,

	// non liquids
    TILE_AIR,
    TILE_GRASS,
    TILE_DIRT,
    TILE_SAND,
    TILE_MUD,
    TILE_STONE,
    TILE_COBBLESTONE,

	// liquids
    TILE_WATER,
    TILE_LAVA,

	// count of all tiles
    TILE_COUNT,
    TILE_LAST = TILE_COUNT - 1
};

// forward declaration
struct world;

// tile definitions
struct tile
{
    // id
	int id;
	char *name;

    // is the tile a liquid
    bool liquid;

    // is the tile animated
    bool animated;

    // is the tile solid (unused)
    bool solid;

    // does the tile have collision
    bool collides;

    // applies color when rendered (useful for greyscale)
    bool use_color;

    // tile color
    u32 color;

    // drag and sliperiness
    float drag;
    float slip;

    // collision details (offset is relative to position)
    float width;
    float height;
    float offset_x;
    float offset_y;

	// return the texture id for the tile
    int ( *texture )( struct world *world, i64 x, i64 y, i64 z );
};

// init data for tiles
void tile_init( void );

// create a new tile type
struct tile *tile_new( char *name );

// get tile data from id
struct tile *tile_get( int id );

#endif
