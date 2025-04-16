#include "platform.h"
#include "util/log.h"
#include "system/audio.h"
#include "system/input.h"
#include "system/time.h"
#include "system/window.h"
#include <SDL3/SDL.h>

struct
{
    u32 flags;
    platform_malloc_fn malloc;
    platform_calloc_fn calloc;
    platform_realloc_fn realloc;
    platform_dealloc_fn dealloc;
} g_platform_state = { 0 };

int platform_init(u32 flags)
{
    g_platform_state.flags = flags;

    log_info("SDL Version: %d.%d.%d",
        SDL_VERSIONNUM_MAJOR(SDL_VERSION),
        SDL_VERSIONNUM_MINOR(SDL_VERSION),
        SDL_VERSIONNUM_MICRO(SDL_VERSION));

    if (flags & PLATFORM_TIMER)
        time_init();

    if (flags & PLATFORM_INPUT)
        input_init();

    if (flags & PLATFORM_AUDIO)
        audio_init();

    if (flags & PLATFORM_WINDOW)
        window_init();

    return 0;
}

void platform_deinit(void)
{
    time_deinit();
    input_deinit();
    audio_deinit();
    window_deinit();
    SDL_Quit();
    g_platform_state.flags = 0;
}

int platform_set_allocator(platform_malloc_fn malloc, platform_calloc_fn calloc, platform_realloc_fn realloc, platform_dealloc_fn dealloc)
{
    const bool invalid =
        malloc == NULL ||
        calloc == NULL ||
        realloc == NULL ||
        dealloc == NULL;

    if (invalid)
        return -1;

    g_platform_state.malloc = malloc;
    g_platform_state.calloc = calloc;
    g_platform_state.realloc = realloc;
    g_platform_state.dealloc = dealloc;
    SDL_SetMemoryFunctions(malloc, calloc, realloc, dealloc);
    return 0;
}

void platform_get_allocator(platform_malloc_fn *malloc, platform_calloc_fn *calloc, platform_realloc_fn *realloc, platform_dealloc_fn *dealloc)
{
    *malloc = g_platform_state.malloc;
    *calloc = g_platform_state.calloc;
    *realloc = g_platform_state.realloc;
    *dealloc = g_platform_state.dealloc;
}

void *platform_malloc(size_t size)
{
    return g_platform_state.malloc(size);
}

void *platform_calloc(size_t count, size_t size)
{
    return g_platform_state.calloc(count, size);
}
void *platform_realloc(void *mem, size_t size)
{
    return g_platform_state.realloc(mem, size);
}

void platform_dealloc(void *mem)
{
    g_platform_state.dealloc(mem);
}