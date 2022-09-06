#include "control.h"
#include "ecs.h"
#include "../input/input.h"

static void update( struct ecs *self )
{
    self->component.movement.up = key_press( KB_NORTH );
    self->component.movement.down = key_press( KB_SOUTH );
    self->component.movement.right = key_press( KB_EAST );
    self->component.movement.left = key_press( KB_WEST );
}

void ecs_control_init()
{
    enum ecs_component type = COMPONENT_CONTROL;

    ECS_SYSTEMS[ type ] = ( union ecs_system ) {
        .sys = {
            .init = NULL,
            .free = NULL,
            .tick = NULL,
            .update = &update,
            .render = NULL
        }
    };
}
