#ifndef TILE_H
#define TILE_H

#include "../../util/util.h"

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
    TILE_STONE,

	// liquids
    TILE_WATER,

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
	
	// string ids
	char *str_id;

	// is the tile transparent (should the tiles below it be rendered)
	bool transparent;

    // is the tile a liquid
    bool liquid;

    // is the tile animated
    bool animated;

    // is the tile solid (unused)
    bool solid;

	// use tile color
    bool use_color;

    // tile color
    uint32_t color;

    // drag and sliperiness to use with physics
    float drag;
    float slip;

	// aabb
    float width;
    float height;
    float offset_x;
    float offset_y;

	// return the texture id for the tile
    int ( *texture )( struct world *world, int64_t x, int64_t y, int64_t z );
};

// init data for tiles
int tile_init( void );

// create tile type
struct tile *tile_new( int id );

// get tile data
struct tile *tile_get( int id );

#endif
