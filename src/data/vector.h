#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

struct metadata_
{
    size_t size;
    size_t capacity;
};

#define VECT_TO_META( vec ) ( ( ( struct metadata_ * ) ( vec ) ) - 1 )
#define META_TO_VECT( vec ) ( ( void * ) ( ( ( struct metadata_ * ) ( vec ) ) + 1 ) )
#define CAST_TO_META( vec ) ( ( struct metadata_ * ) ( vec ) )

#define vector_compute_growth_( size ) ( ( size_t ) ( size * 1.5 + 1 ) )
#define vector_size( vec ) ( ( vec ) ? VECT_TO_META( vec )->size : ( size_t ) 0 )
#define vector_capacity( vec ) ( ( vec ) ? VECT_TO_META( vec )->capacity : ( size_t ) 0 )

static inline void vector_set_size_( void *vec, size_t s )
{
    if ( vec )
    {
        VECT_TO_META( vec )->size = s;
    }
}

static inline void vector_set_capacity_( void *vec, size_t c )
{
    if ( vec )
    {
        VECT_TO_META( vec )->capacity = c;
    }
}

/*
 * internal alloc function used to allocate and init metadata then return the
 * start of the vector array
 */
static inline void *vector_alloc_( size_t stride, size_t n )
{
    size_t v_size = sizeof( struct metadata_ ) + ( stride * n );
    void *vbase = malloc( v_size );

    if ( vbase == NULL )
        return NULL;

    ( *CAST_TO_META( vbase ) ) =
    ( struct metadata_ ) {
        .size     = 0,
        .capacity = n
    };

    return META_TO_VECT( vbase );
}

/*
 * internal realloc function used to allocate and init metadata then return the
 * start of the vector array
 */
static inline void *vector_realloc_( void *vec, size_t stride, size_t n )
{
    size_t v_size = sizeof( struct metadata_ ) + ( stride * n );

    if ( vec )
    {
        void *vbase = VECT_TO_META( vec );
        vbase = realloc( vbase, v_size );
        vec = vbase ? META_TO_VECT( vbase ) : NULL;
        vector_set_capacity_( vec, n );
    }
    else
    {
        vec = vector_alloc_( stride, n );
    }

    return vec;
}

static inline void *vector_increment_size_( void *vec, size_t stride, size_t n )
{
        size_t vsize = vector_size( vec );
        size_t vcap = vector_capacity( vec );

        if ( vcap <= vsize + n - 1 )
        {
            vec = vector_realloc_(
                vec,
                stride,
                vector_compute_growth_( vcap + n - 1 )
            );
        }

        vector_set_size_( vec, vsize + n );

        return vec;
}

#define vector_init( vec ) \
    do                                                              \
    {                                                               \
        if ( !( vec ) )                                             \
        {                                                           \
            ( vec ) = vector_alloc_( sizeof( *( vec ) ), 0 );       \
        }                                                           \
    }                                                               \
    while ( 0 )

#define vector_free( vec ) \
    do                                                              \
    {                                                               \
        if ( vec )                                                  \
        {                                                           \
            free( VECT_TO_META( vec ) );                            \
            ( vec ) = NULL;                                         \
        }                                                           \
    }                                                               \
    while ( 0 )

#define vector_reserve( vec, n ) \
    do                                                              \
    {                                                               \
        if ( vector_capacity( vec ) < ( n ) )                       \
        {                                                           \
            ( vec ) = vector_realloc_(                              \
                ( vec ),                                            \
                sizeof( *( vec ) ),                                 \
                ( n )                                               \
            );                                                      \
        }                                                           \
    }                                                               \
    while ( 0 )

#define vector_resize( vec, n ) \
    do                                                              \
    {                                                               \
        vector_reserve( ( vec ), ( n ) );                           \
        vector_set_size_( ( vec ) , ( n ) );                        \
    }                                                               \
    while ( 0 )

#define vector_push_back( vec, val ) \
    do                                                              \
    {                                                               \
        size_t vsize = vector_size( vec );                          \
        size_t vcap = vector_capacity( vec );                       \
        if ( vcap <= vsize )                                        \
        {                                                           \
            ( vec ) = vector_realloc_(                              \
                ( vec ),                                            \
                sizeof( *( vec ) ),                                 \
                vector_compute_growth_( vcap )                      \
            );                                                      \
        }                                                           \
        ( vec )[ vsize ] = ( val );                                 \
        vector_set_size_( ( vec ), vsize + 1 );                     \
    }                                                               \
    while ( 0 )

#define vector_pop_back( vec ) \
    do                                                              \
    {                                                               \
        vector_set_size_( ( vec ), vector_size( vec ) - 1 );        \
    }                                                               \
    while ( 0 )

#define vector_clear( vec ) \
    do                                                              \
    {                                                               \
        vector_set_size_( ( vec ), 0 );                             \
    }                                                               \
    while ( 0 )

#define vector_insert( vec, i, val ) \
    do                                                              \
    {                                                               \
        size_t vsize = vector_size( vec );                          \
        size_t vcap = vector_capacity( vec );                       \
        if ( vcap <= vsize )                                        \
        {                                                           \
            ( vec ) = vector_realloc_(                              \
                ( vec ),                                            \
                sizeof( *( vec ) ),                                 \
                vector_compute_growth_( vcap )                      \
            );                                                      \
        }                                                           \
        if ( ( i ) < vsize )                                        \
        {                                                           \
            memmove(                                                \
                ( vec ) + ( i ) + 1,                                \
                ( vec ) + ( i ),                                    \
                ( vsize - ( i ) ) * sizeof( *( vec ) )              \
            );                                                      \
        }                                                           \
        ( vec )[ ( i ) ] = ( val );                                 \
        vector_set_size_( ( vec ), vsize + 1 );                     \
    }                                                               \
    while ( 0 )

#define vector_remove( vec, i ) \
    do                                                              \
    {                                                               \
        if ( vec )                                                  \
        {                                                           \
            size_t vsize = vector_size( vec );                      \
            if ( ( i ) < vsize )                                    \
            {                                                       \
                memmove(                                            \
                    ( vec ) + ( i ),                                \
                    ( vec ) + ( i ) + 1,                            \
                    ( vsize - ( i ) - 1 ) * sizeof( *( vec ) )      \
                );                                                  \
                vector_set_size_( ( vec ), vsize - 1 );             \
            }                                                       \
        }                                                           \
    }                                                               \
    while ( 0 )

#define vector_shrink_to_fit( vec ) \
    do                                                              \
    {                                                               \
        if ( vec )                                                  \
        {                                                           \
            ( vec ) = vector_realloc_(                              \
                ( vec ),                                            \
                sizeof( *( vec ) ),                                 \
                vector_size( vec )                                  \
            );                                                      \
        }                                                           \
    }                                                               \
    while ( 0 )

#endif
