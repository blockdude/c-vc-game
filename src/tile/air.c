#include "tile.h"

void air_init()
{
    struct Tile tile = DEFAULT_TILE;
    enum TileId id = TILE_AIR;

    tile.id = id;
    tile.solid = false;

    TILES[ id ] = tile;
}
