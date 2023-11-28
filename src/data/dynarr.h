#ifndef DYNARR_H
#define DYNARR_H

/*
 * A header only, C++ style dynamic array implementation.
 * Heavly influenced by eteran's c-vector.
 * https://github.com/eteran/c-vector.
 */

#include <stdlib.h>

/**
 * struct metadata_ - Structure for dynarr metadata.
 * @size: Number of usable elements.
 * @capacity: Number of elements allowed in the dynarr before reallocating.
 *
 * For internal use only.
 *
 * Structure for dynarr metadata.
 */
struct metadata_
{
    size_t size;
    size_t capacity;
};

/**
 * *_TO_*_() - Macros to move from a dynarr address to the metadata and visa
 *             versa.
 * @darr: Pointer to an existing dynarr.
 *
 * For internal use only.
 *
 * Macros that will take a dynarr address and move to the metadata address and
 * also to cast to the metadata structure.
 *
 * Return: The new address of the given pointer.
 */
#define DARR_TO_META_( darr ) ( ( ( struct metadata_ * ) ( darr ) ) - 1 )
#define META_TO_DARR( darr ) ( ( void * ) ( ( ( struct metadata_ * ) ( darr ) ) + 1 ) )
#define CAST_TO_META_( darr ) ( ( struct metadata_ * ) ( darr ) )

/**
 * dynarr_compute_growth_() - Calculates the next growth.
 * @size: Initial size to compute next growth.
 *
 * For internal use only.
 *
 * Calculate the next growth which grows exponentially.
 *
 * Return: The next growth rate.
 */
#define dynarr_compute_growth_( size ) ( ( size_t ) ( size * 1.5 + 1 ) )

/**
 * dynarr_*_() - Memory manipulation.
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
#define dynarr_memset_( dst, val, n ) memset( ( dst ), ( val ), ( n ) )
#define dynarr_memmove_( dst, src, n ) memmove( ( dst ), ( src ), ( n ) )
#define dynarr_memcpy_( dst, src, n ) memcpy( ( dst ), ( src ), ( n ) )

/**
 * dynarr_free_() - Free dynarr memory.
 * @darr: The dynarr to be freed.
 *
 * For internal use only.
 *
 * Free dynarr memory.
 */
#define dynarr_free_( darr ) free( DARR_TO_META_( darr ) )

/**
 * dynarr_size() - Gets the size of the dynarr.
 * dynarr_capacity() - Gets the capacity of the dynarr.
 * @darr: Vector to get metadata from.
 *
 * Return: A size_t with size or capacity value.
 */
#define dynarr_size( darr ) ( ( darr ) ? DARR_TO_META_( darr )->size : ( size_t ) 0 )
#define dynarr_capacity( darr ) ( ( darr ) ? DARR_TO_META_( darr )->capacity : ( size_t ) 0 )

/**
 * dynarr_set_size_() - Sets the size in the dynarr's metadata.
 * @darr: Pointer to the dynarr.
 * @s: The new size to assign.
 *
 * For internal use only.
 *
 * Assign the size in a dynarr.
 */
static inline void dynarr_set_size_( void *darr, size_t s )
{
    if ( darr )
    {
        DARR_TO_META_( darr )->size = s;
    }
}

/**
 * dynarr_set_capacity_() - Sets the capacity in the dynarr's metadata.
 * @darr: Pointer to the dynarr.
 * @c: The new capacity to assign.
 *
 * For internal use only.
 *
 * Assign the capacity in a dynarr.
 */
static inline void dynarr_set_capacity_( void *darr, size_t c )
{
    if ( darr )
    {
        DARR_TO_META_( darr )->capacity = c;
    }
}

/**
 * dynarr_alloc_() - Allocates and initialized a new dynarr.
 * @stride: Size of a single element.
 * @n: Number of elements to allocate.
 *
 * For internal use only.
 *
 * Allocates memory for a new dynarr and initializes the metadata.
 *
 * Return: A pointer to the new dynarr. Will return NULL if it failed to
 *         allocate the memory.
 */
static inline void *dynarr_alloc_( size_t stride, size_t n )
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

    return META_TO_DARR( vbase );
}

/**
 * dynarr_realloc_() - Realloces a dynarr to a new size.
 * @darr: Vector to reallocate.
 * @stride: Size of a single element.
 * @n: Number of elements to reallocate to.
 *
 * For internal use only.
 *
 * Reallocate memory for a dynarr and assigns capcity of the dynarr. If darr is
 * NULL then it will allocate a new dynarr with n being its initial capacity.
 *
 * Return: A pointer to the new address of the dynarr. Will return NULL if
 *         it failed to allocate the memory.
 */
static inline void *dynarr_realloc_( void *darr, size_t stride, size_t n )
{
    size_t v_size = sizeof( struct metadata_ ) + ( stride * n );

    if ( darr )
    {
        void *vbase = DARR_TO_META_( darr );
        vbase = realloc( vbase, v_size );
        darr = vbase ? META_TO_DARR( vbase ) : NULL;
        dynarr_set_capacity_( darr, n );
    }
    else
    {
        darr = dynarr_alloc_( stride, n );
    }

    return darr;
}

/**
 * dynarr_increment_size_() - Increments the size in dynarr metadata.
 * @darr: Vector to increment.
 * @stride: Size of an element.
 * @n: Number to increment size by.
 *
 * For internal use only.
 *
 * Will increment size of a dynarr by n. Will reallocate memory if size excedes
 * capacity.
 *
 * Return: A pointer to the the dynarr. Can return NULL if memory failed to be
 *         allocated.
 */
static inline void *dynarr_increment_size_( void *darr, size_t stride, size_t n )
{
        size_t vsize = dynarr_size( darr );
        size_t vcap = dynarr_capacity( darr );

        if ( vcap <= vsize + n - 1 )
        {
            darr = dynarr_realloc_(
                darr,
                stride,
                dynarr_compute_growth_( vcap + n - 1 )
            );
        }

        dynarr_set_size_( darr, vsize + n );

        return darr;
}

/**
 * dynarr_init() - Macro to allocate memory for a new dynarr.
 * @darr: Pointer to the dynarr.
 * @c: Capacity to initialize the dynarr with.
 *
 * Macro to allocate memory for a new dynarr then assign it "darr". This could
 * assign "darr" to NULL if it failed to allocate memory.
 */
#define dynarr_init( darr, c ) \
    do                                                              \
    {                                                               \
        if ( !( darr ) )                                            \
        {                                                           \
            ( darr ) = dynarr_alloc_( sizeof( *( darr ) ), ( c ) ); \
        }                                                           \
    }                                                               \
    while ( 0 )

/**
 * dynarr_free() - Macro to free memory of a dynarr.
 * @darr: Pointer to a dynarr.
 *
 * Macro to free memory of a dynarr and assign "darr" to NULL.
 */
#define dynarr_free( darr ) \
    do                                                              \
    {                                                               \
        if ( darr )                                                 \
        {                                                           \
            dynarr_free_( darr );                                   \
            ( darr ) = NULL;                                        \
        }                                                           \
    }                                                               \
    while ( 0 )

/**
 * dynarr_reserve() - Change the capacity to be at least n elements.
 * @darr: Pointer to dynarr.
 * @n: Capacity goal.
 *
 * Macro to check if the current capacity is at least "n" or more. If it is not
 * then reallocate capacity to "n" and assign "darr" to the new address of the
 * dynarr. Could assign "darr" to NULL if it failed to allocate memory.
 */
#define dynarr_reserve( darr, n ) \
    do                                                              \
    {                                                               \
        if ( dynarr_capacity( darr ) < ( n ) )                      \
        {                                                           \
            ( darr ) = dynarr_realloc_(                             \
                ( darr ),                                           \
                sizeof( *( darr ) ),                                \
                ( n )                                               \
            );                                                      \
        }                                                           \
    }                                                               \
    while ( 0 )

/**
 * dynarr_resize() - Change the size of the dynarr.
 * @darr: Pointer to dynarr.
 * @n: New size for dynarr.
 *
 * Macro to change the size of the dynarr and if needed reallocate memory to
 * accomodate the new size. Could assign "darr" to NULL if it failed to allocate
 * memory.
 */
#define dynarr_resize( darr, n ) \
    do                                                              \
    {                                                               \
        size_t vsize = dynarr_size( darr );                         \
        dynarr_reserve( ( darr ), ( n ) );                          \
        if ( vsize < ( n ) )                                        \
        {                                                           \
            dynarr_memset_(                                         \
                ( darr ) + vsize,                                   \
                0,                                                  \
                ( ( n ) - vsize ) * sizeof( *( darr ) )             \
            );                                                      \
        }                                                           \
        dynarr_set_size_( ( darr ) , ( n ) );                       \
    }                                                               \
    while ( 0 )

/**
 * dynarr_push_back() - Insert an element to the end of a dynarr.
 * @darr: Pointer to a dynarr.
 * @val: Value to store in the dynarr.
 *
 * Macro to store an element to the end of a dynarr and increment the size.
 * Will reallocate the dynarr to the next growth size if needed. Could assign
 * "darr" to NULL if it failed to allocate memory.
 */
#define dynarr_push_back( darr, val ) \
    do                                                              \
    {                                                               \
        size_t vsize = dynarr_size( darr );                         \
        size_t vcap = dynarr_capacity( darr );                      \
        if ( vcap <= vsize )                                        \
        {                                                           \
            ( darr ) = dynarr_realloc_(                             \
                ( darr ),                                           \
                sizeof( *( darr ) ),                                \
                dynarr_compute_growth_( vcap )                      \
            );                                                      \
        }                                                           \
        ( darr )[ vsize ] = ( val );                                \
        dynarr_set_size_( ( darr ), vsize + 1 );                    \
    }                                                               \
    while ( 0 )

/**
 * dynarr_pop_back() - Remove an element from the end of a dynarr
 * @darr: Pointer to dynarr.
 *
 * Macro to remove an element from the end of a dynarr. Just decrements the size
 * by one. Does NOT deallocate memory from the dynarr.
 */
#define dynarr_pop_back( darr ) \
    do                                                              \
    {                                                               \
        dynarr_set_size_( ( darr ), dynarr_size( darr ) - 1 );      \
    }                                                               \
    while ( 0 )

/**
 * dynarr_clear() - Removes all elements from a dynarr.
 * @darr: Pointer to dynarr.
 *
 * Macro that sets the size to zero effectivly removing all elements from a
 * dynarr. Does NOT deallocate memory from the dynarr.
 */
#define dynarr_clear( darr ) \
    do                                                              \
    {                                                               \
        dynarr_set_size_( ( darr ), 0 );                            \
    }                                                               \
    while ( 0 )

/**
 * dynarr_insert() - Insert an element at an index.
 * @darr: Pointer to a dynarr.
 * @i: Index to insert to.
 * @val: Element to insert.
 *
 * Macro that will insert into an index and move upper elements up one index.
 * Will reallocate memory if needed.
 */
#define dynarr_insert( darr, i, val ) \
    do                                                              \
    {                                                               \
        size_t vsize = dynarr_size( darr );                         \
        size_t vcap = dynarr_capacity( darr );                      \
        if ( vcap <= vsize )                                        \
        {                                                           \
            ( darr ) = dynarr_realloc_(                             \
                ( darr ),                                           \
                sizeof( *( darr ) ),                                \
                dynarr_compute_growth_( vcap )                      \
            );                                                      \
        }                                                           \
        if ( ( i ) < vsize )                                        \
        {                                                           \
            dynarr_memmove_(                                        \
                ( darr ) + ( i ) + 1,                               \
                ( darr ) + ( i ),                                   \
                ( vsize - ( i ) ) * sizeof( *( darr ) )             \
            );                                                      \
        }                                                           \
        ( darr )[ ( i ) ] = ( val );                                \
        dynarr_set_size_( ( darr ), vsize + 1 );                    \
    }                                                               \
    while ( 0 )

/**
 * dynarr_remove() - Remove an element from an index.
 * @darr: Pointer to a dynarr.
 * @i: Index to remove from.
 *
 * Macro that will remove an element from an index and move upper elements down
 * one. Does NOT reallocate memory.
 */
#define dynarr_remove( darr, i ) \
    do                                                              \
    {                                                               \
        if ( darr )                                                 \
        {                                                           \
            size_t vsize = dynarr_size( darr );                     \
            if ( ( i ) < vsize )                                    \
            {                                                       \
                dynarr_memmove_(                                    \
                    ( darr ) + ( i ),                               \
                    ( darr ) + ( i ) + 1,                           \
                    ( vsize - ( i ) - 1 ) * sizeof( *( darr ) )     \
                );                                                  \
                dynarr_set_size_( ( darr ), vsize - 1 );            \
            }                                                       \
        }                                                           \
    }                                                               \
    while ( 0 )

/**
 * dynarr_condense() - Reduce capacity to match size.
 * @darr: Pointer to a dynarr.
 *
 * Macro to that will reduce the capacity of a dynarr to match its size. Will
 * reallocate memory if capacity > size.
 */
#define dynarr_condense( darr ) \
    do                                                              \
    {                                                               \
        if ( darr )                                                 \
        {                                                           \
            ( darr ) = dynarr_realloc_(                             \
                ( darr ),                                           \
                sizeof( *( darr ) ),                                \
                dynarr_size( darr )                                 \
            );                                                      \
        }                                                           \
    }                                                               \
    while ( 0 )

#endif
