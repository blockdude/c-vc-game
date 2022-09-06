#include "movement.h"
#include "ecs.h"

static void tick( struct ecs *self )
{
    f32 dx = 0;
    f32 dy = 0;

    if ( self->component.movement.left )
    {
        dx -= 1;
    }

    if ( self->component.movement.right )
    {
        dx += 1;
    }

    if ( self->component.movement.up )
    {
        dy -= 1;
    }

    if ( self->component.movement.down )
    {
        dy += 1;
    }

    normalize( dx, dy, &dx, &dy );
    self->component.physics.dx = dx * self->component.movement.speed;
    self->component.physics.dy = dy * self->component.movement.speed;
}

void ecs_movement_init()
{
    enum ecs_component id = COMPONENT_MOVEMENT;

    ECS_SYSTEMS[ id ] = ( union ecs_system ) {
        .sys = {
            .init = NULL,
            .free = NULL,
            .tick = &tick,
            .update = NULL,
            .render = NULL
        }
    };
}
