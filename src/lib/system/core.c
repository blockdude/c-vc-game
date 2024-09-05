#include "core.h"
#include "internal/core.h"
#include "internal/sys.h"

struct core core = {
    .window.initialized = false,
    .window.flags = 0,
    .window.title = "",
    .window.w = 700,
    .window.h = 700,
    .window.aspect = 1.0f,
};

int core_init( unsigned int flags )
{
    core.flags = flags;

    sys_init();

    if ( ( flags & TIMER ) > 0 )
    {
        sys_init_timer();
    }

    if ( ( flags & INPUT ) > 0 )
    {
        sys_init_input();
    }

    if ( ( flags & AUDIO ) > 0 )
    {
        sys_init_audio();
    }

    if ( ( flags & WINDOW ) > 0 )
    {
        sys_init_window();
    }

    return CORE_SUCCESS;
}

int core_free( void )
{
    sys_free();
    core.window.initialized = false;
    return CORE_SUCCESS;
}
