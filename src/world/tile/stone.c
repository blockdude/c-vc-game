#include "tile.h"

void stone_init( void )
{
    struct tile *tile = tile_new( TILE_STONE );

	tile->use_color = true;
	tile->color = 0x888C8DFF;
}
