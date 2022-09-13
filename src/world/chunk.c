#include "chunk.h"
#include "world.h"

int chunk_init( struct chunk *self, struct world *world, i64 x, i64 y, i64 z )
{
    // init all data of chunk to zero
    *self = ( struct chunk ) { 0 };

    // init new data
    self->world = world;
    self->x = x;
    self->y = y;
    self->z = z;

	return 0;
}

int chunk_free( struct chunk *self )
{
    // just set data to zero
    *self = ( struct chunk ) { 0 };

	return 0;
}
