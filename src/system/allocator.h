#ifndef VCP_ALLOCATOR_H
#define VCP_ALLOCATOR_H

#include <stddef.h>

typedef void *( *allocator_malloc_fn )( size_t );
typedef void *( *allocator_calloc_fn )( size_t, size_t );
typedef void *( *allocator_realloc_fn )( void *, size_t );
typedef void ( *allocator_dealloc_fn )( void * );

struct allocator
{
	void *( *malloc )( size_t );
	void *( *calloc )( size_t, size_t );
	void *( *realloc )( void *, size_t );
	void ( *dealloc )( void * );
};

void allocator_reset( void );
int allocator_set( struct allocator allocator );
int allocator_set_shallow( struct allocator allocator );
struct allocator allocator_get( void );

void *allocator_malloc( size_t size );
void *allocator_calloc( size_t count, size_t size );
void *allocator_realloc( void *mem, size_t size );
void allocator_dealloc( void *mem );

#endif