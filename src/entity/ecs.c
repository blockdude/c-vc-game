#include "ecs.h"
#include "../data-struct/vector.h"

#define ECS_INIT_COMPONENT( name ) \
    extern int ecs_##name##_init( struct ecs * ); \
    ecs_##name##_init( self );

int ecs_init( struct ecs *self )
{
    memset( self, 0, sizeof( *self ) );

    return 0;
}

int ecs_free( struct ecs *self )
{
    memset( self, 0, sizeof( *self ) );

    return 0;
}

ecs_event_t ecs_register_event( struct ecs *self )
{
    return 0;
}

ecs_system_t ecs_register_system( struct ecs *self, ecs_system_fn fn, ecs_event_t event, size_t component_count, ecs_component_t *components )
{
    return 0;
}

ecs_component_t ecs_register_component( struct ecs *self, size_t component_size )
{
    return 0;
}
