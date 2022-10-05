#include "control.h"
#include "ecs.h"
#include "../input/input.h"

static int update( void *self, struct ecs *ecs )
{
    if ( self == NULL || ecs == NULL )
        return -1;
    return 0;
}

int ecs_control_init( struct ecs *ecs )
{
    union ecs_system system = {
        .sys = {
            .init   = NULL,
            .free   = NULL,
            .tick   = NULL,
            .update = &update,
            .render = NULL
        }
    };

    return ecs_register_component( ecs, ECS_COMPONENT_CONTROL, sizeof( struct component_control ), system );
}
