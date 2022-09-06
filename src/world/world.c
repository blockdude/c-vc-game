#include "world.h"
#include "generate.h"

void world_init( struct world *self )
{
    *self = ( struct world ) { 0 };
    ecs_init( &self->ecs );
}

void world_free( struct world *self )
{
    *self = ( struct world ) { 0 };
}

void world_update( struct world *self )
{
}

void world_tick( struct world *self )
{
}

void world_render( struct world *self )
{
}
