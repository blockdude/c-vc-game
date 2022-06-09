#include "../tile.h"

void mud_init()
{
    struct Tile tile = DEFAULT_TILE;
    enum TileId id = TILE_MUD;

    tile.id = id;
    tile.use_color = true;
    tile.color = 0x70543EFF;
    tile.drag = 10.0f;

    TILES[ id ] = tile;
}
