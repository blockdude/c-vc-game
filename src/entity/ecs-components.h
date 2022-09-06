#ifndef COMPONENT_H
#define COMPONENT_H

#include "camera.h"
#include "control.h"
#include "movement.h"
#include "physics.h"
#include "position.h"

enum ecs_component
{
    COMPONENT_FIRST = 0,

    COMPONENT_POSITION = 0,
    COMPONENT_CONTROL,
    COMPONENT_MOVEMENT,
    COMPONENT_PHYSICS,
    COMPONENT_CAMERA,

    COMPONENT_COUNT,
    COMPONENT_LAST = COMPONENT_COUNT - 1
};

struct ecs_component_collection
{
    struct component_position position;
    struct component_control control;
    struct component_movement movement;
    struct component_physics physics;
    struct component_camera camera;
};

#define _ECS_DECL_COMPONENT( _name )\
    extern void ecs_##_name##_init();\
    ecs_##_name##_init();

static inline void ecs_init_components()
{
    _ECS_DECL_COMPONENT( position );
    _ECS_DECL_COMPONENT( control );
    _ECS_DECL_COMPONENT( physics );
    _ECS_DECL_COMPONENT( movement );
    _ECS_DECL_COMPONENT( camera );
}

#endif
