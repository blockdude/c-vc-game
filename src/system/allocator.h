#ifndef VCP_ALLOCATOR_H
#define VCP_ALLOCATOR_H

#include <stddef.h>

typedef void *(*allocator_malloc_fn)(size_t);
typedef void *(*allocator_calloc_fn)(size_t, size_t);
typedef void *(*allocator_realloc_fn)(void *, size_t);
typedef void (*allocator_dealloc_fn)(void *);

struct allocator
{
    allocator_malloc_fn malloc;
    allocator_calloc_fn calloc;
    allocator_realloc_fn realloc;
    allocator_dealloc_fn dealloc;
};

extern void allocator_restore_original(void);
extern int allocator_set_global(struct allocator allocator);
extern int allocator_set_shallow(struct allocator allocator);
extern struct allocator allocator_get_global(void);
extern void *allocator_malloc(size_t size);
extern void *allocator_calloc(size_t count, size_t size);
extern void *allocator_realloc(void *mem, size_t size);
extern void allocator_dealloc(void *mem);

#endif