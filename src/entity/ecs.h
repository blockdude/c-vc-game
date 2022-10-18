#ifndef ECS_H
#define ECS_H

#include "../util/util.h"

/*
 * defines
 */

#define ECS_REGISTER_ERROR UINT64_MAX

/*
 * types
 */

typedef int ( *ecs_system_fn )( struct ecs * );

typedef uint64_t ecs_id_t;

typedef ecs_id_t ecs_event_t;
typedef ecs_id_t ecs_component_t;
typedef ecs_id_t ecs_system_t;
typedef ecs_id_t ecs_entity_t;

/*
 * component stuff
 */

struct ecs_component_data
{
    /* array of individual components */
    void *data;
    size_t size;
};

/*
 * system stuff
 */

struct ecs_system_data
{
    ecs_system_fn fn;
    ecs_component_t *components;
    size_t component_count;
};

/*
 * lists
 */

struct ecs_system_list
{
    struct ecs_system_data *list;
    size_t count;
    size_t max;
};

struct ecs_event_list
{
    struct ecs_system_list *system;
    size_t count;
    size_t max;
};

struct ecs_component_list
{
    struct ecs_component_data *list;
    size_t count;
    size_t max;
};

struct ecs_entity_list
{
    ecs_entity_t *list;
    size_t count;
    size_t max;
};

/*
 * ecs stuff
 */

struct ecs
{

};

/*
 * functions
 */

// ecs creation
int ecs_init( struct ecs *self );
int ecs_free( struct ecs *self );

void *ecs_get_components( struct ecs *self, ecs_component_t component, size_t *count );

// entity creation
ecs_entity_t ecs_entity_new( struct ecs *self );
int ecs_entity_del( struct ecs *self, ecs_entity_t entity );

// component creation for entities
int ecs_entity_add_component( struct ecs *self, ecs_entity_t entity, ecs_component_t component, void *data );
int ecs_entity_del_component( struct ecs *self, ecs_entity_t entity, ecs_component_t component );
void *ecs_entity_get_component( struct ecs *self, ecs_entity_t entity, ecs_component_t component );

// calling events
ecs_event_t ecs_event_new( struct ecs *self );
int ecs_event_del( struct ecs *self, ecs_event_t event );
int ecs_call_event( struct ecs *self, ecs_event_t event );

// register stuff which return an id to its respective call
ecs_system_t ecs_register_system( struct ecs *self, ecs_system_fn fn, ecs_event_t event, size_t component_count, ecs_component_t *components );
ecs_component_t ecs_register_component( struct ecs *self, size_t component_size );

#endif
