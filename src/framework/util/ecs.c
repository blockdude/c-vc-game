#include "ecs.h"
//#include <data/vector.h>

#define ECS_INIT_COMPONENT( name ) \
    extern int ecs_##name##_init( struct ecs * ); \
    ecs_##name##_init( self );

#define ECS_INIT_CAPACITY 256

//int ecs_init( struct ecs *self )
//{
//    // init vectors
//    self->component = vector_new( sizeof( *self->component ), ECS_INIT_CAPACITY );
//    self->system = vector_new( sizeof( *self->system ), ECS_INIT_CAPACITY );
//    self->entity = vector_new( sizeof( *self->entity ), ECS_INIT_CAPACITY );
//
//    return 0;
//}
//
//int ecs_free( struct ecs *self )
//{
//    for ( size_t i = 0; i < vector_size( self->component ); i++ )
//        vector_free( self->component[ i ] );
//    for ( size_t i = 0; i < vector_size( self->system ); i++ )
//        vector_free( self->system[ i ] );
//    vector_free( self->entity );
//
//    return 0;
//}
//
//ecs_system_t ecs_register_system( struct ecs *self, ecs_system_fn fn, ecs_event_t event )
//{
//    // make sure the event exists
//    if ( event >= vector_size( self->system ) )
//        return ECS_REGISTER_ERROR;
//
//    // add fn to vector
//    self->system[ event ] = vector_push_back( self->system[ event ], NULL );
//    size_t back = vector_size( self->system[ event ] ) - 1;
//    self->system[ event ][ back ] = fn;
//
//    // create system id
//    ecs_system_t sys_id;
//    sys_id = event << 15;
//    sys_id += back;
//
//    return sys_id;
//}
//
//ecs_component_t ecs_register_component( struct ecs *self, size_t component_size );
