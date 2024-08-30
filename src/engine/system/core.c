#include "core.h"
#include "core-internal.h"
#include "system.h"

struct core core = { 0 };

int core_init( void )
{
    if ( system_init() == SYSTEM_ERROR )
    {
        return CORE_ERROR;
    }

    return CORE_SUCCESS;
}

int core_free( void )
{
    system_free();
    core.window.initialized = false;
    return CORE_SUCCESS;
}
