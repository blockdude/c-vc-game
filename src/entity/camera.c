#include "camera.h"
#include "ecs.h"

static void tick( struct ecs *self )
{
    self->component.camera.x = self->component.position.x + self->component.camera.offset_x;
    self->component.camera.y = self->component.position.y + self->component.camera.offset_y;
}

void ecs_camera_init()
{
    enum ecs_component type = ECS_COMPONENT_CAMERA;

    ECS_SYSTEMS[ type ] = ( union ecs_system ) {
        .sys = {
            .init = NULL,
            .free = NULL,
            .tick = &tick,
            .update = NULL,
            .render = NULL
        }
    };
}
