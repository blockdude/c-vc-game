#ifndef ECS_H
#define ECS_H

#include <util/util.h>

/*
 * defines
 */

#define ECS_REGISTER_ERROR UINT64_MAX

/*
 * types
 */

struct ecs;
typedef int ( *ecs_system_fn )( struct ecs * );

typedef uint64_t ecs_id_t;

typedef ecs_id_t ecs_event_t;
typedef ecs_id_t ecs_component_t;
typedef ecs_id_t ecs_system_t;
typedef ecs_id_t ecs_entity_t;

/*
 * ecs stuff
 */

struct ecs
{
    // vector of component pools
    void **component;

    // 2d vector of systems (1 dimension for events and 1 for the systems)
    ecs_system_fn **system;

    // vector of entity ids
    ecs_entity_t *entity;
};

/*
 * functions
 */

// ecs creation
int ecs_init( struct ecs *self );
int ecs_free( struct ecs *self );

// calling events
ecs_event_t ecs_event_create( struct ecs *self );
int ecs_event_delete( struct ecs *self, ecs_event_t event );
int ecs_call_event( struct ecs *self, ecs_event_t event );

// register stuff which return an id to its respective call
ecs_system_t ecs_register_system( struct ecs *self, ecs_system_fn fn, ecs_event_t event );
ecs_component_t ecs_register_component( struct ecs *self, size_t component_size );

void *ecs_get_components( struct ecs *self, ecs_component_t component, size_t *count );

// entity creation
ecs_entity_t ecs_entity_create( struct ecs *self );
int ecs_entity_delete( struct ecs *self, ecs_entity_t entity );

// component creation for entities
int ecs_entity_add_component( struct ecs *self, ecs_entity_t entity, ecs_component_t component, void *data );
int ecs_entity_del_component( struct ecs *self, ecs_entity_t entity, ecs_component_t component );
void *ecs_entity_get_component( struct ecs *self, ecs_entity_t entity, ecs_component_t component );

#endif
