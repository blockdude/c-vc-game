#include "world.h"

int world_init( struct world *self )
{
    *self = ( struct world ) { 0 };
    ecs_init( &self->ecs );

	return 0;
}

int world_free( struct world *self )
{
    *self = ( struct world ) { 0 };

	return 0;
}
