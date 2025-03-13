#ifndef VCP_ALLOCATOR_H
#define VCP_ALLOCATOR_H

#include <stddef.h>

typedef void *(*allocator_malloc_fn_t)(size_t);
typedef void *(*allocator_calloc_fn_t)(size_t, size_t);
typedef void *(*allocator_realloc_fn_t)(void *, size_t);
typedef void (*allocator_dealloc_fn_t)(void *);

struct allocator
{
    allocator_malloc_fn_t malloc;
    allocator_calloc_fn_t calloc;
    allocator_realloc_fn_t realloc;
    allocator_dealloc_fn_t dealloc;
};

extern void allocator_restore_original(void);
extern int allocator_set_global(struct allocator allocator);
extern int allocator_set_shallow(struct allocator allocator);
extern struct allocator allocator_get(void);
extern void *allocator_malloc(size_t size);
extern void *allocator_calloc(size_t count, size_t size);
extern void *allocator_realloc(void *mem, size_t size);
extern void allocator_dealloc(void *mem);

#endif