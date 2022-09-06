#include "position.h"
#include "ecs.h"

void ecs_position_init()
{
    enum ecs_component id = COMPONENT_POSITION;

    ECS_SYSTEMS[ id ] = ( union ecs_system ) {
        .sys = {
            .init = NULL,
            .free = NULL,
            .tick = NULL,
            .update = NULL,
            .render = NULL
        }
    };
}
