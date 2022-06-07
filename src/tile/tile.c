#include "tile.h"

struct Tile TILES[ TILE_COUNT ];

struct Tile DEFAULT_TILE = {
    .id = -1,
    .liquid = false,
    .animated = false,
    .solid = false,
    .collides = false,
    .use_color = false,
    .color = 0,
    .drag = 1.0f,
    .slip = 1.0f,
    .width = 100,
    .height = 100,
    .offset_x = 0,
    .offset_y = 0
};
