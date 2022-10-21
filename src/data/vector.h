#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

void *vector_new( size_t element_size, size_t max_count );
int vector_free( void *self );

void *vector_reserve( void *self, size_t capacity );
void *vector_resize( void *self, size_t size );

size_t vector_size( void *self );
size_t vector_capacity( void *self );

void *vector_push_back( void *self, void *data );
void *vector_pop_back( void *self );

void *vector_insert( void *self, size_t index );
void *vector_remove( void *self, size_t index );

#endif
