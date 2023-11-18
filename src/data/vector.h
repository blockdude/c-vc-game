#ifndef VECTOR_H
#define VECTOR_H

/*
 * A header only C++ style dynamic array implementation.
 * Heavly influenced by eteran's c-vector.
 * https://github.com/eteran/c-vector.
 */

#include <stdlib.h>

/**
 * struct metadata_ - Structure for vector metadata.
 * @size: Number of usable elements.
 * @capacity: Number of elements allowed in the vector before reallocating.
 *
 * For internal use only.
 *
 * Structure for vector metadata.
 */
struct metadata_
{
    size_t size;
    size_t capacity;
};

/**
 * *_TO_*_() - Macros to move from a vector address to the metadata and visa
 *             versa.
 * @vec: Pointer to an existing vector.
 *
 * For internal use only.
 *
 * Macros that will take a vector address and move to the metadata address and
 * also to cast to the metadata structure.
 *
 * Return: The new address of the given pointer.
 */
#define VECT_TO_META_( vec ) ( ( ( struct metadata_ * ) ( vec ) ) - 1 )
#define META_TO_VECT_( vec ) ( ( void * ) ( ( ( struct metadata_ * ) ( vec ) ) + 1 ) )
#define CAST_TO_META_( vec ) ( ( struct metadata_ * ) ( vec ) )

/**
 * vector_compute_growth_() - Calculates the next growth.
 * @size: Initial size to compute next growth.
 *
 * For internal use only.
 *
 * Calculate the next growth which grows exponentially.
 *
 * Return: The next growth rate.
 */
#define vector_compute_growth_( size ) ( ( size_t ) ( size * 1.5 + 1 ) )

/**
 * vector_*_() - Memory manipulation.
 * @dst: The array to be written to.
 * @val: Value to assign to destination.
 * @src: The array to be read from.
 * @n: number of bytes to read and write.
 *
 * For internal use only.
 *
 * Collection of memory manipulation macros.
 *
 * Return: The destination pointer.
 */
#define vector_memset_( dst, val, n ) memset( ( dst ), ( val ), ( n ) )
#define vector_memmove_( dst, src, n ) memmove( ( dst ), ( src ), ( n ) )
#define vector_memcpy_( dst, src, n ) memcpy( ( dst ), ( src ), ( n ) )

/**
 * vector_free_() - Free vector memory.
 * @vec: The vector to be freed.
 *
 * For internal use only.
 *
 * Free vector memory.
 */
#define vector_free_( vec ) free( VECT_TO_META_( vec ) )

/**
 * vector_size() - Gets the size of the vector.
 * vector_capacity() - Gets the capacity of the vector.
 * @vec: Vector to get metadata from.
 *
 * Return: A size_t with size or capacity value.
 */
#define vector_size( vec ) ( ( vec ) ? VECT_TO_META_( vec )->size : ( size_t ) 0 )
#define vector_capacity( vec ) ( ( vec ) ? VECT_TO_META_( vec )->capacity : ( size_t ) 0 )

/**
 * vector_set_size_() - Sets the size in the vector's metadata.
 * @vec: Pointer to the vector.
 * @s: The new size to assign.
 *
 * For internal use only.
 *
 * Assign the size in a vector.
 */
static inline void vector_set_size_( void *vec, size_t s )
{
    if ( vec )
    {
        VECT_TO_META_( vec )->size = s;
    }
}

/**
 * vector_set_capacity_() - Sets the capacity in the vector's metadata.
 * @vec: Pointer to the vector.
 * @c: The new capacity to assign.
 *
 * For internal use only.
 *
 * Assign the capacity in a vector.
 */
static inline void vector_set_capacity_( void *vec, size_t c )
{
    if ( vec )
    {
        VECT_TO_META_( vec )->capacity = c;
    }
}

/**
 * vector_alloc_() - Allocates and initialized a new vector.
 * @stride: Size of a single element.
 * @n: Number of elements to allocate.
 *
 * For internal use only.
 *
 * Allocates memory for a new vector and initializes the metadata.
 *
 * Return: A pointer to the new vector. Will return NULL if it failed to
 *         allocate the memory.
 */
static inline void *vector_alloc_( size_t stride, size_t n )
{
    size_t v_size = sizeof( struct metadata_ ) + ( stride * n );
    void *vbase = malloc( v_size );

    if ( vbase == NULL )
        return NULL;

    ( *CAST_TO_META_( vbase ) ) =
    ( struct metadata_ ) {
        .size     = 0,
        .capacity = n
    };

    return META_TO_VECT_( vbase );
}

/**
 * vector_realloc_() - Realloces a vector to a new size.
 * @vec: Vector to reallocate.
 * @stride: Size of a single element.
 * @n: Number of elements to reallocate to.
 *
 * For internal use only.
 *
 * Reallocate memory for a vector and assigns capcity of the vector. If vec is
 * NULL then it will allocate a new vector with n being its initial capacity.
 *
 * Return: A pointer to the new address of the vector. Will return NULL if
 *         it failed to allocate the memory.
 */
static inline void *vector_realloc_( void *vec, size_t stride, size_t n )
{
    size_t v_size = sizeof( struct metadata_ ) + ( stride * n );

    if ( vec )
    {
        void *vbase = VECT_TO_META_( vec );
        vbase = realloc( vbase, v_size );
        vec = vbase ? META_TO_VECT_( vbase ) : NULL;
        vector_set_capacity_( vec, n );
    }
    else
    {
        vec = vector_alloc_( stride, n );
    }

    return vec;
}

/**
 * vector_increment_size_() - Increments the size in vector metadata.
 * @vec: Vector to increment.
 * @stride: Size of an element.
 * @n: Number to increment size by.
 *
 * For internal use only.
 *
 * Will increment size of a vector by n. Will reallocate memory if size excedes
 * capacity.
 *
 * Return: A pointer to the the vector. Can return NULL if memory failed to be
 *         allocated.
 */
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

/**
 * vector_init() - Macro to allocate memory for a new vector.
 * @vec: Pointer to the vector.
 * @c: Capacity to initialize the vector with.
 *
 * Macro to allocate memory for a new vector then assign it "vec". This could
 * assign "vec" to NULL if it failed to allocate memory.
 */
#define vector_init( vec, c ) \
    do                                                              \
    {                                                               \
        if ( !( vec ) )                                             \
        {                                                           \
            ( vec ) = vector_alloc_( sizeof( *( vec ) ), ( c ) );   \
        }                                                           \
    }                                                               \
    while ( 0 )

/**
 * vector_free() - Macro to free memory of a vector.
 * @vec: Pointer to a vector.
 *
 * Macro to free memory of a vector and assign "vec" to NULL.
 */
#define vector_free( vec ) \
    do                                                              \
    {                                                               \
        if ( vec )                                                  \
        {                                                           \
            vector_free_( vec );                                    \
            ( vec ) = NULL;                                         \
        }                                                           \
    }                                                               \
    while ( 0 )

/**
 * vector_reserve() - Change the capacity to be at least n elements.
 * @vec: Pointer to vector.
 * @n: Capacity goal.
 *
 * Macro to check if the current capacity is at least "n" or more. If it is not
 * then reallocate capacity to "n" and assign "vec" to the new address of the
 * vector. Could assign "vec" to NULL if it failed to allocate memory.
 */
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

/**
 * vector_resize() - Change the size of the vector.
 * @vec: Pointer to vector.
 * @n: New size for vector.
 *
 * Macro to change the size of the vector and if needed reallocate memory to
 * accomodate the new size. Could assign "vec" to NULL if it failed to allocate
 * memory.
 */
#define vector_resize( vec, n ) \
    do                                                              \
    {                                                               \
        size_t vsize = vector_size( vec );                          \
        vector_reserve( ( vec ), ( n ) );                           \
        if ( vsize < ( n ) )                                        \
        {                                                           \
            vector_memset_(                                         \
                ( vec ) + vsize,                                    \
                0,                                                  \
                ( ( n ) - vsize ) * sizeof( *( vec ) )              \
            );                                                      \
        }                                                           \
        vector_set_size_( ( vec ) , ( n ) );                        \
    }                                                               \
    while ( 0 )

/**
 * vector_push_back() - Insert an element to the end of a vector.
 * @vec: Pointer to a vector.
 * @val: Value to store in the vector.
 *
 * Macro to store an element to the end of a vector and increment the size.
 * Will reallocate the vector to the next growth size if needed. Could assign
 * "vec" to NULL if it failed to allocate memory.
 */
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

/**
 * vector_pop_back() - Remove an element from the end of a vector
 * @vec: Pointer to vector.
 *
 * Macro to remove an element from the end of a vector. Just decrements the size
 * by one. Does NOT deallocate memory from the vector.
 */
#define vector_pop_back( vec ) \
    do                                                              \
    {                                                               \
        vector_set_size_( ( vec ), vector_size( vec ) - 1 );        \
    }                                                               \
    while ( 0 )

/**
 * vector_clear() - Removes all elements from a vector.
 * @vec: Pointer to vector.
 *
 * Macro that sets the size to zero effectivly removing all elements from a
 * vector. Does NOT deallocate memory from the vector.
 */
#define vector_clear( vec ) \
    do                                                              \
    {                                                               \
        vector_set_size_( ( vec ), 0 );                             \
    }                                                               \
    while ( 0 )

/**
 * vector_insert() - Insert an element at an index.
 * @vec: Pointer to a vector.
 * @i: Index to insert to.
 * @val: Element to insert.
 *
 * Macro that will insert into an index and move upper elements up one index.
 * Will reallocate memory if needed.
 */
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
            vector_memmove_(                                        \
                ( vec ) + ( i ) + 1,                                \
                ( vec ) + ( i ),                                    \
                ( vsize - ( i ) ) * sizeof( *( vec ) )              \
            );                                                      \
        }                                                           \
        ( vec )[ ( i ) ] = ( val );                                 \
        vector_set_size_( ( vec ), vsize + 1 );                     \
    }                                                               \
    while ( 0 )

/**
 * vector_remove() - Remove an element from an index.
 * @vec: Pointer to a vector.
 * @i: Index to remove from.
 *
 * Macro that will remove an element from an index and move upper elements down
 * one. Does NOT reallocate memory.
 */
#define vector_remove( vec, i ) \
    do                                                              \
    {                                                               \
        if ( vec )                                                  \
        {                                                           \
            size_t vsize = vector_size( vec );                      \
            if ( ( i ) < vsize )                                    \
            {                                                       \
                vector_memmove_(                                    \
                    ( vec ) + ( i ),                                \
                    ( vec ) + ( i ) + 1,                            \
                    ( vsize - ( i ) - 1 ) * sizeof( *( vec ) )      \
                );                                                  \
                vector_set_size_( ( vec ), vsize - 1 );             \
            }                                                       \
        }                                                           \
    }                                                               \
    while ( 0 )

/**
 * vector_shrink_to_fit() - Reduce capacity to match size.
 * @vec: Pointer to a vector.
 *
 * Macro to that will reduce the capacity of a vector to match its size. Will
 * reallocate memory if capacity > size.
 */
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
