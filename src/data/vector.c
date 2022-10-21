#include <stdlib.h>
#include <string.h>
#include "vector.h"

struct vector
{
    size_t size;
    size_t capacity;
    size_t element_size;
};

#define VECTOR_HEAD( vec )      ( ( ( struct vector * ) vec ) - 1 )
#define VECTOR_FIRST( vec )     ( ( ( struct vector * ) vec ) + 1 )

void *vector_new( size_t element_size, size_t capacity )
{
    struct vector *vec = malloc( sizeof( *vec ) + element_size * capacity );

    // init hidden data
    vec->size = 0;
    vec->capacity = capacity;
    vec->element_size = element_size;

    // return the address of next element
    return VECTOR_FIRST( vec );
}

int vector_free( void *self )
{
    if ( self == NULL )
        return -1;

    free( VECTOR_HEAD( self ) );
    return 0;
}

void *vector_reserve( void *self, size_t capacity )
{
    if ( self == NULL )
        return NULL;

    struct vector *vec = VECTOR_HEAD( self );

    // do nothing if current capacity is greater or equal to new capacity
    if ( vec->capacity < capacity )
    {
        vec = realloc( vec, sizeof( *vec ) + vec->element_size * capacity );
        vec->capacity = capacity;
    }

    return VECTOR_FIRST( vec );
}

void *vector_resize( void *self, size_t size )
{
    if ( self == NULL )
        return NULL;

    struct vector *vec = VECTOR_HEAD( self );

    // realloc if we need to
    if ( vec->capacity < size )
    {
        vec = realloc( vec, sizeof( *vec ) + vec->element_size * size );
        vec->capacity = size;
    }

    // store new size
    vec->size = size;

    return VECTOR_FIRST( vec );
}

size_t vector_size( void *self )
{
    if ( self == NULL )
        return 0;

    struct vector *vec = VECTOR_HEAD( self );
    return vec->size;
}

size_t vector_capacity( void *self )
{
    if ( self == NULL )
        return 0;

    struct vector *vec = VECTOR_HEAD( self );
    return vec->capacity;
}

void *vector_push_back( void *self, void *data )
{
    if ( self == NULL )
        return 0;

    struct vector *vec = VECTOR_HEAD( self );

    if ( vec->size == vec->capacity )
    {
        vec->capacity *= 2;
        vec = realloc( vec, sizeof( *vec ) + vec->element_size * vec->capacity );
    }

    // copy data
    char *data_dest = self;
    data_dest += vec->element_size * vec->size;
    memcpy( data_dest, data, vec->element_size );
    vec->size++;

    return VECTOR_FIRST( vec );
}

void *vector_pop_back( void *self )
{
    if ( self == NULL )
        return 0;

    struct vector *vec = VECTOR_HEAD( self );

    if ( vec->size > 0 )
        vec->size--;

    return VECTOR_FIRST( vec );
}
