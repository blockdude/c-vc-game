#include "position.h"
#include "ecs.h"

int ecs_position_init( struct ecs *ecs )
{
    union ecs_system system = { 
        .sys = {
            .init   = NULL,
            .free   = NULL,
            .tick   = NULL,
            .update = NULL,
            .render = NULL
        }
    };

    return ecs_register_component( ecs, ECS_COMPONENT_POSITION, sizeof( struct component_position ), system );
}
