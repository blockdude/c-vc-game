#ifndef WORLD_H
#define WORLD_H

#include "../util/util.h"
#include "../entity/ecs.h"
#include "tile/tile.h"
#include "chunk.h"

#define WORLD_SIZE_X 1
#define WORLD_SIZE_Y 1
#define WORLD_SIZE_Z 1
#define WORLD_VOLUME ( WORLD_SIZE_X * WORLD_SIZE_Y * WORLD_SIZE_Z )

struct world
{
    // collection of all world entities
    struct ecs ecs;

    // entity to follow with camera
    struct entity entity_view;

    // entity to load world around
    struct entity entity_load;

    // world tick counter (used to get time of day?)
    u64 tick;

    // seed of world
    u64 seed;

    // size in each dimension of the world
    int world_size;

    // all chunks in the world
    struct chunk chunks[ WORLD_VOLUME ];
};

int world_init( struct world *self );
int world_free( struct world *self );
int world_update( struct world *self );
int world_tick( struct world *self );

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
