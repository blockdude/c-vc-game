#include "tile.h"

void dirt_init( void )
{
    struct tile *tile = tile_new( TILE_DIRT );

	tile->use_color = true;
	tile->color = 0x964B00FF;
}
