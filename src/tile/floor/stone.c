#include "../tile.h"

void stone_init( void )
{
    struct tile tile = DEFAULT_TILE;
    enum tile_id id = TILE_STONE;

    tile.id = id;
    tile.use_color = true;
    tile.color = 0x888C8DFF;

    TILES[ id ] = tile;
}
