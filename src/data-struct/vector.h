#ifndef VECTOR_H
#define VECTOR_H

void *vector_new( size_t element_size, size_t max_count );
int vector_free( void *self );
void *vector_resize( void *self, size_t max_count );

void *vector_push_back( void *self );
void *vector_push_front( void *self );

void *vector_pop_back( void *self );
void *vector_pop_front( void *self );

void *vector_insert( void *self, size_t index );
void *vector_remove( void *self, size_t index );

int vector_get_count( void *self );
int vector_get_size( void *self );

#endif
