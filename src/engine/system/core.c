#include "core.h"
#include "core-internal.h"
#include "system.h"

struct core core = { 0 };

int core_init( unsigned int flags )
{
    core.flags = flags;

    core.window.title = "GAME";
    core.window.initialized = false;
    core.window.relative_mouse = false;
    core.window.w = 700;
    core.window.h = 700;
    core.window.aspect = 1.0f;

    if ( system_init() == SYSTEM_ERROR )
    {
        return CORE_ERROR;
    }

    core.window.initialized = true;
    return CORE_SUCCESS;
}

int core_free( void )
{
    system_free();
    core.window.initialized = false;
    return CORE_SUCCESS;
}
