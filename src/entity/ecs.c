#include "ecs.h"

#define ECS_INIT_COMPONENT( name ) \
    extern int ecs_##name##_init( struct ecs * ); \
    ecs_##name##_init( self );

int ecs_register_component( struct ecs *self, enum ecs_component id, size_t size, union ecs_system system )
{
    self->components[ id ].system = system;
    self->components[ id ].size = size;
    self->components[ id ].data = malloc( size * self->capacity );

    return 0;
}

int ecs_init( struct ecs *self, struct world *world, size_t capacity )
{
    // set initial size of ecs ( will hold 128 entities max )
    memset( self, 0, sizeof( *self ) );
    self->world = world;
    self->capacity = capacity;
    self->count = 0;

    // init components for this ecs
    ECS_INIT_COMPONENT( position );
    ECS_INIT_COMPONENT( control );
    ECS_INIT_COMPONENT( physics );
    ECS_INIT_COMPONENT( movement );
    ECS_INIT_COMPONENT( camera );

    return 0;
}

int ecs_free( struct ecs *self )
{
    // free components
    for ( int i = 0; i < ECS_COMPONENT_COUNT; i++ )
        free( self->components[ i ].data );

    memset( self, 0, sizeof( *self ) );
    return 0;
}
