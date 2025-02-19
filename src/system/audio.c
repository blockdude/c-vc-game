#include "audio.h"
#include "../internal.h"
#include "../util/log.h"

#include <SDL3/SDL.h>

/*
 * =============================
 * -----------------------------
 * INIT
 * -----------------------------
 */

int audio_init( void )
{
    if ( SDL_Init( SDL_INIT_AUDIO ) != 0 )
    {
        log_warn( "Unable to initialize SDL audio system: %s", SDL_GetError() );
        return -1;
    }

    core.audio.initialized = true;
    return 0;
}

void audio_deinit( void )
{
    if ( core.audio.initialized == false )
        return;

    SDL_QuitSubSystem( SDL_INIT_AUDIO );
    core.timer.initialized = false;
}

/*
 * =============================
 */