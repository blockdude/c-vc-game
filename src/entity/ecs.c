#include "ecs.h"
#include "../data-struct/vector.h"

#define ECS_INIT_COMPONENT( name ) \
    extern int ecs_##name##_init( struct ecs * ); \
    ecs_##name##_init( self );
