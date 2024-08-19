#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * A header only, C++ style dynamic array implementation.
 * Heavly influenced by eteran's c-vector.
 * https://github.com/eteran/c-vector.
 */

#include <stdlib.h>

/**
 * struct _metadata - Structure for list metadata.
 * @size: Number of usable elements.
 * @capacity: Number of elements allowed in the list before reallocating.
 *
 * For internal use only.
 *
 * Structure for list metadata.
 */
struct _metadata
{
    size_t size;
    size_t capacity;
};

/**
 * *_TO_*_() - Macros to move from a list address to the metadata and visa
 *             versa.
 * @lst: Pointer to an existing list.
 *
 * For internal use only.
 *
 * Macros that will take a list address and move to the metadata address and
 * also to cast to the metadata structure.
 *
 * Return: The new address of the given pointer.
 */
#define _LIST_TO_META( lst ) ( ( ( struct _metadata * ) ( lst ) ) - 1 )
#define _META_TO_LIST( lst ) ( ( void * ) ( ( ( struct _metadata * ) ( lst ) ) + 1 ) )
#define _CAST_TO_META( lst ) ( ( struct _metadata * ) ( lst ) )

/**
 * _list_compute_growth() - Calculates the next growth.
 * @size: Initial size to compute next growth.
 *
 * For internal use only.
 *
 * Calculate the next growth which grows exponentially.
 *
 * Return: The next growth rate.
 */
#define _list_compute_growth( size ) ( ( size_t ) ( size * 1.5 + 1 ) )

/**
 * list_*_() - Memory manipulation.
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
#define _list_memset( dst, val, n ) memset( ( dst ), ( val ), ( n ) )
#define _list_memmove( dst, src, n ) memmove( ( dst ), ( src ), ( n ) )
#define _list_memcpy( dst, src, n ) memcpy( ( dst ), ( src ), ( n ) )

/**
 * _list_free() - Free list memory.
 * @lst: The list to be freed.
 *
 * For internal use only.
 *
 * Free list memory.
 */
#define _list_free( lst ) free( _LIST_TO_META( lst ) )

/**
 * list_size() - Gets the size of the list.
 * list_capacity() - Gets the capacity of the list.
 * @lst: Vector to get metadata from.
 *
 * Return: A size_t with size or capacity value.
 */
#define list_size( lst ) ( ( lst ) ? _LIST_TO_META( lst )->size : ( size_t ) 0 )
#define list_capacity( lst ) ( ( lst ) ? _LIST_TO_META( lst )->capacity : ( size_t ) 0 )

/**
 * _list_set_size() - Sets the size in the list's metadata.
 * @lst: Pointer to the list.
 * @s: The new size to assign.
 *
 * For internal use only.
 *
 * Assign the size in a list.
 */
static inline void _list_set_size( void *lst, size_t s )
{
    if ( lst )
    {
        _LIST_TO_META( lst )->size = s;
    }
}

/**
 * _list_set_capacity() - Sets the capacity in the list's metadata.
 * @lst: Pointer to the list.
 * @c: The new capacity to assign.
 *
 * For internal use only.
 *
 * Assign the capacity in a list.
 */
static inline void _list_set_capacity( void *lst, size_t c )
{
    if ( lst )
    {
        _LIST_TO_META( lst )->capacity = c;
    }
}

/**
 * _list_alloc() - Allocates and initialized a new list.
 * @stride: Size of a single element.
 * @n: Number of elements to allocate.
 *
 * For internal use only.
 *
 * Allocates memory for a new list and initializes the metadata.
 *
 * Return: A pointer to the new list. Will return NULL if it failed to
 *         allocate the memory.
 */
static inline void *_list_alloc( size_t stride, size_t n )
{
    size_t size = sizeof( struct _metadata ) + ( stride * n );
    void *base = malloc( size );

    if ( base == NULL )
        return NULL;

    struct _metadata tmp = {
        .size = 0,
        .capacity = n
    };

    *_CAST_TO_META( base ) = tmp;

    return _META_TO_LIST( base );
}

/**
 * _list_realloc() - Realloces a list to a new size.
 * @lst: Vector to reallocate.
 * @stride: Size of a single element.
 * @n: Number of elements to reallocate to.
 *
 * For internal use only.
 *
 * Reallocate memory for a list and assigns capcity of the list. If lst is
 * NULL then it will allocate a new list with n being its initial capacity.
 *
 * Return: A pointer to the new address of the list. Will return NULL if
 *         it failed to allocate the memory.
 */
static inline void *_list_realloc( void *lst, size_t stride, size_t n )
{
    size_t size = sizeof( struct _metadata ) + ( stride * n );

    if ( lst )
    {
        void *base = _LIST_TO_META( lst );
        base = realloc( base, size );
        lst = base ? _META_TO_LIST( base ) : NULL;
        _list_set_capacity( lst, n );
    }
    else
    {
        lst = _list_alloc( stride, n );
    }

    return lst;
}

/**
 * _list_increment_size() - Increments the size in list metadata.
 * @lst: Vector to increment.
 * @stride: Size of an element.
 * @n: Number to increment size by.
 *
 * For internal use only.
 *
 * Will increment size of a list by n. Will reallocate memory if size excedes
 * capacity.
 *
 * Return: A pointer to the the list. Can return NULL if memory failed to be
 *         allocated.
 */
static inline void *_list_increment_size( void *lst, size_t stride, size_t n )
{
    size_t size = list_size( lst );
    size_t cap = list_capacity( lst );

    if ( cap <= size + n - 1 )
    {
        lst = _list_realloc(
            lst,
            stride,
            _list_compute_growth( cap + n - 1 )
        );
    }

    _list_set_size( lst, size + n );

    return lst;
}

/**
 * list_init() - Macro to allocate memory for a new list.
 * @lst: Pointer to the list.
 * @c: Capacity to initialize the list with.
 *
 * Macro to allocate memory for a new list then assign it "lst". This could
 * assign "lst" to NULL if it failed to allocate memory.
 */
#define list_init( lst, c ) \
    do                                                              \
    {                                                               \
        if ( !( lst ) )                                             \
        {                                                           \
            ( lst ) = ( __typeof__( lst ) ) _list_alloc(            \
                sizeof( *( lst ) ), ( c )                           \
            );                                                      \
        }                                                           \
    }                                                               \
    while ( 0 )

/**
 * list_free() - Macro to free memory of a list.
 * @lst: Pointer to a list.
 *
 * Macro to free memory of a list and assign "lst" to NULL.
 */
#define list_free( lst ) \
    do                                                              \
    {                                                               \
        if ( lst )                                                  \
        {                                                           \
            _list_free( lst );                                      \
            ( lst ) = NULL;                                         \
        }                                                           \
    }                                                               \
    while ( 0 )

/**
 * list_reserve() - Change the capacity to be at least n elements.
 * @lst: Pointer to list.
 * @n: Capacity goal.
 *
 * Macro to check if the current capacity is at least "n" or more. If it is not
 * then reallocate capacity to "n" and assign "lst" to the new address of the
 * list. Could assign "lst" to NULL if it failed to allocate memory.
 */
#define list_reserve( lst, n ) \
    do                                                              \
    {                                                               \
        if ( list_capacity( lst ) < ( n ) )                         \
        {                                                           \
            ( lst ) = ( __typeof__( lst ) ) _list_realloc(          \
                ( lst ),                                            \
                sizeof( *( lst ) ),                                 \
                ( n )                                               \
            );                                                      \
        }                                                           \
    }                                                               \
    while ( 0 )

/**
 * list_resize() - Change the size of the list.
 * @lst: Pointer to list.
 * @n: New size for list.
 *
 * Macro to change the size of the list and if needed reallocate memory to
 * accomodate the new size. Could assign "lst" to NULL if it failed to allocate
 * memory.
 */
#define list_resize( lst, n ) \
    do                                                              \
    {                                                               \
        size_t size = list_size( lst );                             \
        list_reserve( ( lst ), ( n ) );                             \
        if ( size < ( n ) )                                         \
        {                                                           \
            _list_memset(                                           \
                ( lst ) + size,                                     \
                0,                                                  \
                ( ( n ) - size ) * sizeof( *( lst ) )               \
            );                                                      \
        }                                                           \
        _list_set_size( ( lst ) , ( n ) );                          \
    }                                                               \
    while ( 0 )

/**
 * list_push_back() - Insert an element to the end of a list.
 * @lst: Pointer to a list.
 * @val: Value to store in the list.
 *
 * Macro to store an element to the end of a list and increment the size.
 * Will reallocate the list to the next growth size if needed. Could assign
 * "lst" to NULL if it failed to allocate memory.
 */
#define list_push_back( lst, val ) \
    do                                                              \
    {                                                               \
        size_t size = list_size( lst );                             \
        size_t cap = list_capacity( lst );                          \
        if ( cap <= size )                                          \
        {                                                           \
            ( lst ) = ( __typeof__( lst ) ) _list_realloc(          \
                ( lst ),                                            \
                sizeof( *( lst ) ),                                 \
                _list_compute_growth( cap )                         \
            );                                                      \
        }                                                           \
        ( lst )[ size ] = ( val );                                  \
        _list_set_size( ( lst ), size + 1 );                        \
    }                                                               \
    while ( 0 )

/**
 * list_pop_back() - Remove an element from the end of a list
 * @lst: Pointer to list.
 *
 * Macro to remove an element from the end of a list. Just decrements the size
 * by one. Does NOT deallocate memory from the list.
 */
#define list_pop_back( lst ) \
    do                                                              \
    {                                                               \
        _list_set_size( ( lst ), list_size( lst ) - 1 );            \
    }                                                               \
    while ( 0 )

/**
 * list_clear() - Removes all elements from a list.
 * @lst: Pointer to list.
 *
 * Macro that sets the size to zero effectivly removing all elements from a
 * list. Does NOT deallocate memory from the list.
 */
#define list_clear( lst ) \
    do                                                              \
    {                                                               \
        _list_set_size( ( lst ), 0 );                               \
    }                                                               \
    while ( 0 )

/**
 * list_insert() - Insert an element at an index.
 * @lst: Pointer to a list.
 * @i: Index to insert to.
 * @val: Element to insert.
 *
 * Macro that will insert into an index and move upper elements up one index.
 * Will reallocate memory if needed.
 */
#define list_insert( lst, i, val ) \
    do                                                              \
    {                                                               \
        size_t size = list_size( lst );                             \
        size_t cap = list_capacity( lst );                          \
        if ( cap <= size )                                          \
        {                                                           \
            ( lst ) = ( __typeof__( lst ) ) _list_realloc(          \
                ( lst ),                                            \
                sizeof( *( lst ) ),                                 \
                _list_compute_growth( cap )                         \
            );                                                      \
        }                                                           \
        if ( ( i ) < size )                                         \
        {                                                           \
            _list_memmove(                                          \
                ( lst ) + ( i ) + 1,                                \
                ( lst ) + ( i ),                                    \
                ( size - ( i ) ) * sizeof( *( lst ) )               \
            );                                                      \
        }                                                           \
        ( lst )[ ( i ) ] = ( val );                                 \
        _list_set_size( ( lst ), size + 1 );                        \
    }                                                               \
    while ( 0 )

/**
 * list_remove() - Remove an element from an index.
 * @lst: Pointer to a list.
 * @i: Index to remove from.
 *
 * Macro that will remove an element from an index and move upper elements down
 * one. Does NOT reallocate memory.
 */
#define list_remove( lst, i ) \
    do                                                              \
    {                                                               \
        if ( lst )                                                  \
        {                                                           \
            size_t size = list_size( lst );                         \
            if ( ( i ) < size )                                     \
            {                                                       \
                _list_memmove(                                      \
                    ( lst ) + ( i ),                                \
                    ( lst ) + ( i ) + 1,                            \
                    ( size - ( i ) - 1 ) * sizeof( *( lst ) )       \
                );                                                  \
                _list_set_size( ( lst ), size - 1 );                \
            }                                                       \
        }                                                           \
    }                                                               \
    while ( 0 )

/**
 * list_condense() - Reduce capacity to match size.
 * @lst: Pointer to a list.
 *
 * Macro to that will reduce the capacity of a list to match its size. Will
 * reallocate memory if capacity > size.
 */
#define list_condense( lst ) \
    do                                                              \
    {                                                               \
        if ( lst )                                                  \
        {                                                           \
            ( lst ) = ( __typeof__( lst ) ) _list_realloc(          \
                ( lst ),                                            \
                sizeof( *( lst ) ),                                 \
                list_size( lst )                                    \
            );                                                      \
        }                                                           \
    }                                                               \
    while ( 0 )

#ifdef __cplusplus
}
#endif

#endif
