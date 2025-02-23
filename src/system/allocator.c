#include "allocator.h"
#include <SDL3/SDL_stdinc.h>

static struct allocator g_allocator = { SDL_malloc, SDL_calloc, SDL_realloc, SDL_free };

void allocator_restore_original( void )
{
    g_allocator.malloc = SDL_malloc;
    g_allocator.calloc = SDL_calloc;
    g_allocator.realloc = SDL_realloc;
    g_allocator.dealloc = SDL_free;

    SDL_malloc_func sdl_malloc;
    SDL_calloc_func sdl_calloc;
    SDL_realloc_func sdl_realloc;
    SDL_free_func sdl_free;

    SDL_GetOriginalMemoryFunctions( &sdl_malloc, &sdl_calloc, &sdl_realloc, &sdl_free );
    SDL_SetMemoryFunctions( sdl_malloc, sdl_calloc, sdl_realloc, sdl_free );
}

int allocator_set( struct allocator allocator )
{
    if ( allocator.malloc == NULL )
        return -1;

    if ( allocator.calloc == NULL )
        return -1;

    if ( allocator.realloc == NULL )
        return -1;

    if ( allocator.dealloc == NULL )
        return -1;

    SDL_SetMemoryFunctions( allocator.malloc, allocator.calloc, allocator.realloc, allocator.dealloc );
    g_allocator = allocator;
    return 0;
}

int allocator_set_shallow( struct allocator allocator )
{
    if ( allocator.malloc == NULL )
        return -1;

    if ( allocator.calloc == NULL )
        return -1;

    if ( allocator.realloc == NULL )
        return -1;

    if ( allocator.dealloc == NULL )
        return -1;

    g_allocator = allocator;
    return 0;
}

struct allocator allocator_get( void )
{
    return g_allocator;
}

void *allocator_malloc( size_t size )
{
    return g_allocator.malloc( size );
}

void *allocator_calloc( size_t count, size_t size )
{
    return g_allocator.calloc( count, size );
}

void *allocator_realloc( void *mem, size_t size )
{
    return g_allocator.realloc( mem, size );
}

void allocator_dealloc( void *mem )
{
    g_allocator.dealloc( mem );
}