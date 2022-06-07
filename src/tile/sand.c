#include "tile.h"

void sand_init()
{
    struct Tile tile = DEFAULT_TILE;
    enum TileId id = TILE_SAND;

    tile.id = id;
    tile.use_color = true;
    tile.color = 0xC2B280FF;

    TILES[ id ] = tile;
}
