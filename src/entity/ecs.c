#include "ecs.h"

#define ECS_INIT_COMPONENT( name ) \
    extern int ecs_##name##_init( struct ecs * ); \
    ecs_##name##_init( self );

int ecs_init( struct ecs *self )
{
    // set initial size of ecs ( will hold 128 entities max )
    memset( self, 0, sizeof( *self ) );

    return 0;
}
