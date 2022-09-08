#include "../tile.h"

void lava_init( void )
{
    struct tile tile = DEFAULT_TILE;
    enum tile_id id = TILE_LAVA;

    tile.id = id;
    tile.liquid = true;
    tile.solid = false;
    tile.use_color = true;
    tile.color = 0xCF1020FF;
    tile.drag = 10.0f;

    TILES[ id ] = tile;
}
