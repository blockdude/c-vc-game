#ifndef ECS_H
#define ECS_H

#include "../util/util.h"

/*
 * component stuff
 */

/*
 * ecs stuff
 */

struct ecs
{
    struct
    {
        uint32_t *ids;
        size_t count;
    } event;

    struct
    {
        uint32_t *ids;
        size_t count;
    } system;

    struct
    {
        uint32_t *ids;
        size_t count;
    } component;

    struct
    {
        uint32_t *ids;
        size_t count;
    } entity;
};

/*
 * system stuff
 */

typedef int ( *ecs_system_fn )( struct ecs * );

/*
 * functions
 */

// ecs creation
int ecs_init( struct ecs *self );
int ecs_free( struct ecs *self );

// entity creation
uint32_t ecs_entity_new( struct ecs *self );
int ecs_entity_del( struct ecs *self, int entity_id );

// component creation for entities
int ecs_entity_add_component( struct ecs *self, int entity_id, int component_id, void *data );
void *ecs_entity_get_component( struct ecs *self, int entity_id, int component_id );
int ecs_entity_del_component( struct ecs *self, int entity_id, int component_id );

// calling events
int ecs_call_event( struct ecs *self, int event_id );

// register stuff which return an id to its respective call
uint32_t ecs_register_event( struct ecs *self );
uint32_t ecs_register_system( struct ecs *self, ecs_system_fn fn, int event_id, int component_count, int *component_ids );
uint32_t ecs_register_component( struct ecs *self, size_t component_size );

#endif
