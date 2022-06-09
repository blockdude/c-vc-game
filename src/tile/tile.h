#ifndef TILE_H
#define TILE_H

#include "../util/util.h"

enum TileId
{
    TILE_FIRST = 0,

    TILE_AIR = 0,
    TILE_GRASS,
    TILE_DIRT,
    TILE_SAND,
    TILE_MUD,
    TILE_WATER,
    TILE_STONE,
    TILE_COBBLESTONE,
    TILE_LAVA,

    TILE_COUNT,
    TILE_LAST = TILE_COUNT - 1
};

// tile definitions
struct Tile
{
    enum TileId id;

    // is the tile a liquid
    bool liquid;

    // is the tile animated
    bool animated;

    // is the tile solid (unused)
    bool solid;

    // does the tile have collision
    bool collides;

    // applies color when rendered (useful for greyscale)
    bool use_color;

    // default tile color
    u32 color;

    // drag and sliperiness
    float drag;
    float slip;

    // collision details (offset is relative to position)
    float width;
    float height;
    float offset_x;
    float offset_y;
};

extern struct Tile DEFAULT_TILE;
extern struct Tile TILES[ TILE_COUNT ];

#define _TILE_DECL(_name)\
    extern void _name##_init();\
    _name##_init();

static inline void tile_init() {
    _TILE_DECL( air );
    _TILE_DECL( grass );
    _TILE_DECL( dirt );
    _TILE_DECL( sand );
    _TILE_DECL( mud );
    _TILE_DECL( water );
    _TILE_DECL( stone );
    _TILE_DECL( cobblestone );
    _TILE_DECL( lava );
}

#endif
