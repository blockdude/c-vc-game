#include "ecs.h"

union ecs_system ECS_SYSTEMS[ COMPONENT_COUNT ];

void ecs_init( struct ecs *self )
{
    memset( self, 0, sizeof( *self ) );
}

void ecs_free( struct ecs *self )
{
    memset( self, 0, sizeof( *self ) );
}

void ecs_add_component( struct ecs *self, enum ecs_component component )
{
    self->enabled_components[ component ] = true;
}

void ecs_rem_component( struct ecs *self, enum ecs_component component )
{
    self->enabled_components[ component ] = false;
}

void ecs_call_event( struct ecs *self, enum ecs_event event )
{
    // call every enabled component event
    for ( int i = 0; i < COMPONENT_COUNT; i++ )
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
}
