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

// all data types
struct ecs_component_data;
union ecs_system;
struct ecs;

/*
 * system stuff
 */

typedef int ( *ecs_event_fn )( void *, struct ecs * );

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
 * component stuff
 */

enum ecs_component
{
    ECS_COMPONENT_FIRST = 0,

    // order matters
    ECS_COMPONENT_POSITION = 0,
    ECS_COMPONENT_CONTROL,
    ECS_COMPONENT_MOVEMENT,
    ECS_COMPONENT_PHYSICS,
    ECS_COMPONENT_CAMERA,

    ECS_COMPONENT_COUNT,
    ECS_COMPONENT_LAST = ECS_COMPONENT_COUNT - 1
};

/*
 * ecs stuff
 */

struct ecs
{
    struct
    {
        // system of component type
        union ecs_system system;

        // array of all data with this component type
        void *data;

        // size of this component type
        size_t size;
    } components[ ECS_COMPONENT_COUNT ];

    // will be the count of data
    size_t capacity;

    // number of entities
    size_t count;

    // world this ecs is attached to
    struct world *world;
};

/*
 * functions
 */

// ecs creation
int ecs_init( struct ecs *self, struct world *world, size_t capacity );
int ecs_free( struct ecs *self );

// entity creation
int ecs_new_entity( struct ecs *self );
int ecs_del_entity( struct ecs *self, int entity_id );

// component creation for entities
// add and get returns a pointer to the component
void *ecs_add_component( struct ecs *self, int entity_id, enum ecs_component component_id );
void *ecs_get_component( struct ecs *self, int entity_id, enum ecs_component component_id );
int ecs_rem_component( struct ecs *self, int entity_id, enum ecs_component component_id );

// event manager
int ecs_call_event( struct ecs *self, enum ecs_event event );
int ecs_call_event_entity( struct ecs *self, enum ecs_event, int entity_id );

// for components only
int ecs_register_component( struct ecs *self, enum ecs_component id, size_t size, union ecs_system system );

#endif
