#ifndef ECS_H
#define ECS_H

#include "../util/util.h"
#include "ecs-components.h"

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

void ecs_init( struct ecs *self );
void ecs_free( struct ecs *self );
void ecs_add_component( struct ecs *self, enum ecs_component component );
void ecs_rem_component( struct ecs *self, enum ecs_component component );
void ecs_call_event( struct ecs *self, enum ecs_event event );

#endif
