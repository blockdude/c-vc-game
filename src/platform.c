#include <vcp/vcp.h>
#include <SDL3/SDL.h>

struct
{
    u32 flags;
} g_platform_state = { 0 };

int platform_init(u32 flags)
{
    g_platform_state.flags = flags;

    log_info("Platform: %s", SDL_GetPlatform());
    log_info("SDL Version: %d.%d.%d",
        SDL_VERSIONNUM_MAJOR(SDL_GetVersion()),
        SDL_VERSIONNUM_MINOR(SDL_GetVersion()),
        SDL_VERSIONNUM_MICRO(SDL_GetVersion()));

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