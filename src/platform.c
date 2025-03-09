#include "platform.h"
#include <SDL3/SDL.h>

struct
{
    u32 flags;
} g_platform_state = { 0 };

int platform_init( const u32 flags )
{
    g_platform_state.flags = flags;

    log_info( "SDL Version : %d.%d.%d",
        SDL_VERSIONNUM_MAJOR( SDL_VERSION ),
        SDL_VERSIONNUM_MINOR( SDL_VERSION ),
        SDL_VERSIONNUM_MICRO( SDL_VERSION ) );

    if ( HASFLAG( flags, TIMER ) )
    {
        time_init();
    }

    if ( HASFLAG( flags, INPUT ) )
    {
        input_init();
    }

    if ( HASFLAG( flags, AUDIO ) )
    {
        audio_init();
    }

    if ( HASFLAG( flags, WINDOW ) )
    {
        window_init();
    }

    return 0;
}

void platform_deinit( void )
{
    time_deinit();
    input_deinit();
    audio_deinit();
    window_deinit();
    SDL_Quit();
}