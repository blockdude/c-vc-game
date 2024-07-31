#include "tile.h"

void grass_init( void )
{
    struct tile *tile = tile_new( TILE_GRASS );

	tile->use_color = true;
	tile->color = 0x00FF00FF;
}
