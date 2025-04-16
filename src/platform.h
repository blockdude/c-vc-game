#ifndef VCP_PLATFORM_H
#define VCP_PLATFORM_H

#include "vcp_common.h"
#include "util/types.h"

typedef void *(*platform_malloc_fn)(size_t);
typedef void *(*platform_calloc_fn)(size_t, size_t);
typedef void *(*platform_realloc_fn)(void *, size_t);
typedef void (*platform_dealloc_fn)(void *);

enum platform_init_flags
{
    PLATFORM_WINDOW  = 0x01,
    PLATFORM_INPUT   = 0x02,
    PLATFORM_AUDIO   = 0x04,
    PLATFORM_TIMER   = 0x08,
    PLATFORM_NETWORK = 0x10 // TODO?
};

#ifdef __cplusplus
extern "C" {
#endif

extern int platform_init(u32 flags);
extern void platform_deinit(void);
extern int platform_set_allocator(platform_malloc_fn malloc, platform_calloc_fn calloc, platform_realloc_fn realloc, platform_dealloc_fn dealloc);
extern void platform_get_allocator(platform_malloc_fn *malloc, platform_calloc_fn *calloc, platform_realloc_fn *realloc, platform_dealloc_fn *dealloc);
extern void *platform_malloc(size_t size);
extern void *platform_calloc(size_t count, size_t size);
extern void *platform_realloc(void *mem, size_t size);
extern void platform_dealloc(void *mem);

#ifdef __cplusplus
}
#endif

#endif
