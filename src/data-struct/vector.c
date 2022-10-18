#include <stdlib.h>
#include "vector.h"

struct vector
{
    size_t count;
    size_t max_count;
    size_t element_size;
};

void *vector_new( size_t element_size, size_t max_count )
{
    struct vector *vec = malloc( sizeof( *vec ) + element_size * max_count );

    // init hidden data
    vec->count = 0;
    vec->max_count = max_count;
    vec->element_size = element_size;

    // return the next element
    return &vec[ 1 ];
}

int vector_free( void *self )
{
    struct vector *vec = self;
    free( &vec[ -1 ] );
    return 0;
}

void *vector_resize( void *self, size_t max_count )
{
    struct vector *vec = self;
    vec = &vec[ -1 ];

    vec = realloc( vec, sizeof( *vec ) + vec->element_size * max_count );
    vec->max_count = max_count;

    return &vec[ 1 ];
}
