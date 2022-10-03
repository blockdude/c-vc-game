#include "ecs.h"

union ecs_system ECS_SYSTEMS[ ECS_COMPONENT_COUNT ];

int ecs_init( struct ecs *self, struct world *world )
{
    memset( self, 0, sizeof( *self ) );
    self->world = world;
    return 0;
}

int ecs_free( struct ecs *self )
{
    memset( self, 0, sizeof( *self ) );
    return 0;
}

int ecs_add_component( struct ecs *self, enum ecs_component component )
{
    self->enabled_components[ component ] = true;
    return 0;
}

int ecs_rem_component( struct ecs *self, enum ecs_component component )
{
    self->enabled_components[ component ] = false;
    return 0;
}

int ecs_call_event( struct ecs *self, enum ecs_event event )
{
    // call every enabled component event
    for ( int i = 0; i < ECS_COMPONENT_COUNT; i++ )
    {
        if ( self->enabled_components[ i ] == true )
        {
            ecs_event_fn fn = ECS_SYSTEMS[ i ].events[ event ];

            if ( fn )
            {
                fn( self );
            }
        }
    }

    return 0;
}
