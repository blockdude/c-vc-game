#include "physics.h"
#include "ecs.h"

static void tick( struct ecs *self )
{
    self->component.position.x += self->component.physics.dx;
    self->component.position.y += self->component.physics.dy;
}

void ecs_physics_init()
{
    enum ecs_component id = COMPONENT_PHYSICS;

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
