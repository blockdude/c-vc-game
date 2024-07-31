#ifndef WORLD_H
#define WORLD_H

#include "../util/util.h"
#include "tile/tile.h"
#include "chunk.h"

struct world
{
    // temp camera
    struct
    {
        float x;
        float y;
        float scale;
    } camera;

    // world tick counter (used to get time of day?)
    uint64_t tick;

    // seed of world
    uint64_t seed;

    // all chunks in the world
    size_t world_size_x;
    size_t world_size_y;
    size_t world_size_z;
    size_t chunks_count;
    struct chunk *chunks;
};

int world_init( struct world *self, size_t world_size_x, size_t world_size_y, size_t world_size_z );
int world_free( struct world *self );
int world_tick( struct world *self );
int world_update( struct world *self );
int world_render( struct world *self );

//void world_to_screen( float world_x, float world_y, int *screen_x, int *screen_y );
//void screen_to_world( float world_x, float world_y, int *screen_x, int *screen_y );

//void screen_to_world( int screen_x, int screen_y, float *world_x, float *world_y )
//{
//    float offset_x = window_w / 2.0f;
//    float offset_y = window_h / 2.0f;
//
//    *world_x = ( float ) ( ( screen_x - offset_x ) / scale_x + camera_x );
//    *world_y = ( float ) ( ( screen_y - offset_y ) / scale_y + camera_y );
//}
//
//void world_to_screen( float world_x, float world_y, int *screen_x, int *screen_y )
//{
//    float offset_x = window_w / 2.0f;
//    float offset_y = window_h / 2.0f;
//
//    *screen_x = ( int ) ( ( world_x - camera_x ) * scale_x + offset_x );
//    *screen_y = ( int ) ( ( world_y - camera_y ) * scale_y + offset_y );
//}

#endif
