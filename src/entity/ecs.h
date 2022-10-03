#ifndef ECS_H
#define ECS_H

#include "../util/util.h"

// components
#include "camera.h"
#include "control.h"
#include "movement.h"
#include "physics.h"
#include "position.h"

// forward declaration
struct world;

/*
 * component stuff
 */

enum ecs_component
{
    ECS_COMPONENT_FIRST = 0,

    ECS_COMPONENT_POSITION = 0,
    ECS_COMPONENT_CONTROL,
    ECS_COMPONENT_MOVEMENT,
    ECS_COMPONENT_PHYSICS,
    ECS_COMPONENT_CAMERA,

    ECS_COMPONENT_COUNT,
    ECS_COMPONENT_LAST = ECS_COMPONENT_COUNT - 1
};

struct ecs_component_collection
{
    struct component_position position;
    struct component_control control;
    struct component_movement movement;
    struct component_physics physics;
    struct component_camera camera;
};

/*
 * ecs stuff
 */

struct ecs
{
    struct ecs_component_collection component;
    bool enabled_components[ ECS_COMPONENT_COUNT ];

    struct world *world;
};

struct entity
{
    uint32_t id;
    struct ecs *ecs;
};

/*
 * system stuff
 */

typedef void ( *ecs_event_fn )( struct ecs * );

enum ecs_event
{
    ECS_EVENT_FIRST = 0,

    ECS_EVENT_INIT = 0,
    ECS_EVENT_FREE,
    ECS_EVENT_TICK,
    ECS_EVENT_UPDATE,
    ECS_EVENT_RENDER,

    ECS_EVENT_COUNT,
    ECS_EVENT_LAST = ECS_EVENT_COUNT - 1
};

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

    ecs_event_fn events[ ECS_EVENT_COUNT ];
};

/*
 * global variables
 */

extern union ecs_system ECS_SYSTEMS[ ECS_COMPONENT_COUNT ];

/*
 * functions
 */

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

// ecs creation
int ecs_init( struct ecs *self, struct world *world );
int ecs_free( struct ecs *self );

// entity creation
struct entity ecs_new_entity( struct ecs *self );
int ecs_del_entity( struct entity entity );

// component creation for entities
int ecs_add_component( struct ecs *self, enum ecs_component component );
int ecs_rem_component( struct ecs *self, enum ecs_component component );

// event manager
int ecs_call_event( struct ecs *self, enum ecs_event event );

#endif
