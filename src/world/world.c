#include "world.h"

void world_init( struct world *self )
{
    *self = ( struct world ) { 0 };
    ecs_init( &self->ecs );
}

void world_free( struct world *self )
{
    *self = ( struct world ) { 0 };
}
