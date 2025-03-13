#include "audio.h"
#include "../util/log.h"

#include <SDL3/SDL.h>

static struct
{
    bool initialized;
} g_audio_state = { 0 };

/*
 * =============================
 * -----------------------------
 * INIT
 * -----------------------------
 */

int audio_init(void)
{
    if (SDL_Init(SDL_INIT_AUDIO) == false)
    {
        log_warn("Unable to initialize SDL audio system: %s", SDL_GetError());
        return -1;
    }

    g_audio_state.initialized = true;
    return 0;
}

void audio_deinit(void)
{
    if (g_audio_state.initialized == false)
        return;

    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    g_audio_state.initialized = false;
}

/*
 * =============================
 */