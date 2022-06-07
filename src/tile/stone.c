#include "tile.h"

void stone_init()
{
    struct Tile tile = DEFAULT_TILE;
    enum TileId id = TILE_STONE;

    tile.id = id;
    tile.use_color = true;
    tile.color = 0x888C8DFF;

    TILES[ id ] = tile;
}
