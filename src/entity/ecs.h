#ifndef ECS_H
#define ECS_H

#include "../util/util.h"

// components
#include "camera.h"
#include "control.h"
#include "movement.h"
#include "physics.h"
#include "position.h"

// forward declaration of world
struct world;

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

struct ecs
{
    struct ecs_component_collection component;
    bool enabled_components[ COMPONENT_COUNT ];

    // pointer to world to allow systems to interact with the world
    struct world *world;
};

struct entity
{
    u64 id;
    struct ecs *ecs;
};

enum ecs_event
{
    EVENT_FIRST = 0,

    EVENT_INIT = 0,
    EVENT_FREE,
    EVENT_TICK,
    EVENT_UPDATE,
    EVENT_RENDER,

    EVENT_COUNT,
    EVENT_LAST = EVENT_COUNT - 1
};

typedef void ( *ecs_event_fn )( struct ecs * );

union ecs_system
{
    struct
    {
        ecs_event_fn init;
        ecs_event_fn free;
        ecs_event_fn tick;
        ecs_event_fn update;
        ecs_event_fn render;
    } sys;

    ecs_event_fn events[ EVENT_COUNT ];
};

extern union ecs_system ECS_SYSTEMS[ COMPONENT_COUNT ];

void ecs_init( struct ecs *self, struct world *world );
void ecs_free( struct ecs *self );
void ecs_add_component( struct ecs *self, enum ecs_component component );
void ecs_rem_component( struct ecs *self, enum ecs_component component );
void ecs_call_event( struct ecs *self, enum ecs_event event );

#endif
