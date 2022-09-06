#ifndef CHUNK_H
#define CHUNK_H

#include "../util/util.h"
#include "../tile/tile.h"

#define CHUNK_SIZE_X 32
#define CHUNK_SIZE_Y 32
#define CHUNK_SIZE_Z 32

#define CHUNK_VOLUME ( CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z )

// forward declartion of world
struct world;

// tile data for chunk
struct tile_data
{
    int light_level;
    enum tile_id id;
};

// chunk data
struct chunk
{
    // position of chunk
    i64 x;
    i64 y;
    i64 z;

    // world where chunk is set in
    struct world *world;

    // chunk data
    struct tile_data data[ CHUNK_VOLUME ];
};

void chunk_init( struct chunk *self, struct world *world, i64 x, i64 y, i64 z );
void chunk_free( struct chunk *self );
void chunk_update( struct chunk *self );
void chunk_tick( struct chunk *self );
void chunk_render( struct chunk *self );

#endif
