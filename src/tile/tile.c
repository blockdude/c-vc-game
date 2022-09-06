#include "tile.h"

struct tile TILES[ TILE_COUNT ];

struct tile DEFAULT_TILE = {
    .id         = -1,
    .liquid     = false,
    .animated   = false,
    .solid      = true,
    .collides   = false,
    .use_color  = false,
    .color      = 0,
    .drag       = 1.0f,
    .slip       = 1.0f,
    .width      = 1.0f,
    .height     = 1.0f,
    .offset_x   = 0.0f,
    .offset_y   = 0.0f,
    .texture    = NULL
};
