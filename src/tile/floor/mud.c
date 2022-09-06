#include "../tile.h"

void mud_init( void )
{
    struct tile tile = DEFAULT_TILE;
    enum tile_id id = TILE_MUD;

    tile.id = id;
    tile.use_color = true;
    tile.color = 0x70543EFF;
    tile.drag = 10.0f;

    TILES[ id ] = tile;
}
