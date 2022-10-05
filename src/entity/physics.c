#include "physics.h"
#include "ecs.h"

static int tick( void *self, struct ecs *ecs )
{
    if ( self == NULL || ecs == NULL )
        return -1;
    return 0;
}

int ecs_physics_init( struct ecs *ecs )
{
    union ecs_system system = { 
        .sys = {
            .init   = NULL,
            .free   = NULL,
            .tick   = &tick,
            .update = NULL,
            .render = NULL
        }
    };

    return ecs_register_component( ecs, ECS_COMPONENT_PHYSICS, sizeof( struct component_physics ), system );
}
