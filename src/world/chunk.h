#ifndef CHUNK_H
#define CHUNK_H

#include "../util/util.h"
#include "tile/tile.h"

#define CHUNK_SIZE_X        48
#define CHUNK_SIZE_Y        48
#define CHUNK_SIZE_Z        48
#define CHUNK_VOLUME        ( CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z )

// forward declartion of world
struct world;

struct tile_data
{
    uint8_t light_level;
    uint8_t id;
};

// chunk data
struct chunk
{
    // world containing this chunk
    struct world *world;

    // index in world chunks array
    size_t index;

    // tile data
    struct tile_data *tiles;
};

int chunk_init( struct chunk *self, struct world *world, size_t index );
int chunk_free( struct chunk *self );
int chunk_update( struct chunk *self );
int chunk_tick( struct chunk *self );
int chunk_render( struct chunk *self );

#endif
