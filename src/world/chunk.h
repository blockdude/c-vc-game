#ifndef CHUNK_H
#define CHUNK_H

#include "../util/util.h"
#include "tile/tile.h"

#define CHUNK_SIZE_X 32
#define CHUNK_SIZE_Y 32
#define CHUNK_SIZE_Z 32

#define CHUNK_VOLUME ( CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z )

// forward declartion of world
struct world;

// chunk data
struct chunk
{
    // position of chunk
    i64 x;
    i64 y;
    i64 z;

    // world where chunk is set in
    struct world *world;

    // tile data
    struct
    {
        int light_level;
        enum tile_id id;
    } data[ CHUNK_VOLUME ];
};

int chunk_init( struct chunk *self, struct world *world, i64 x, i64 y, i64 z );
int chunk_free( struct chunk *self );
int chunk_update( struct chunk *self );
int chunk_tick( struct chunk *self );

#endif
