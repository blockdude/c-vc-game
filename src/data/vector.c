#include <stdlib.h>
#include <string.h>
#include "vector.h"

//void *vector_new( size_t stride, size_t capacity )
//{
//    struct vector_metadata *vec = malloc( sizeof( *vec ) + stride * capacity );
//
//    // init hidden data
//    vec->size = 0;
//    vec->capacity = capacity;
//    vec->stride = stride;
//
//    // return the address of next element
//    return BASE_TO_DATA( vec );
//}
//
//int vector_free( void *self )
//{
//    if ( self == NULL )
//        return -1;
//
//    free( DATA_TO_BASE( self ) );
//    return 0;
//}
//
//void *vector_reserve( void *self, size_t capacity )
//{
//    if ( self == NULL )
//        return NULL;
//
//    struct vector_metadata *vec = DATA_TO_BASE( self );
//
//    // do nothing if current capacity is greater or equal to new capacity
//    if ( vec->capacity < capacity )
//    {
//        vec = realloc( vec, sizeof( *vec ) + vec->stride * capacity );
//        vec->capacity = capacity;
//    }
//
//    return BASE_TO_DATA( vec );
//}
//
//void *vector_resize( void *self, size_t size )
//{
//    if ( self == NULL )
//        return NULL;
//
//    struct vector_metadata *vec = DATA_TO_BASE( self );
//
//    // realloc if we need to
//    if ( vec->capacity < size )
//    {
//        vec = realloc( vec, sizeof( *vec ) + vec->stride * size );
//        vec->capacity = size;
//    }
//
//    // store new size
//    vec->size = size;
//
//    return BASE_TO_DATA( vec );
//}
//
//size_t vector_size( void *self )
//{
//    if ( self == NULL )
//        return 0;
//
//    struct vector_metadata *vec = DATA_TO_BASE( self );
//    return vec->size;
//}
//
//size_t vector_capacity( void *self )
//{
//    if ( self == NULL )
//        return 0;
//
//    struct vector_metadata *vec = DATA_TO_BASE( self );
//    return vec->capacity;
//}
//
//void *vector_push_back( void *self, void *data )
//{
//    if ( self == NULL )
//        return 0;
//
//    struct vector_metadata *vec = DATA_TO_BASE( self );
//
//    if ( vec->size == vec->capacity )
//    {
//        vec->capacity *= 2;
//        vec = realloc( vec, sizeof( *vec ) + vec->stride * vec->capacity );
//    }
//
//    // copy data
//    if ( data != NULL )
//    {
//        char *data_dest = self;
//        data_dest += vec->stride * vec->size;
//        memcpy( data_dest, data, vec->stride );
//    }
//
//    vec->size++;
//
//    return BASE_TO_DATA( vec );
//}
//
//void *vector_pop_back( void *self )
//{
//    if ( self == NULL )
//        return 0;
//
//    struct vector_metadata *vec = DATA_TO_BASE( self );
//
//    if ( vec->size > 0 )
//        vec->size--;
//
//    return BASE_TO_DATA( vec );
//}
