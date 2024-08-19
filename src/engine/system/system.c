#include "system.h"
#include <util/log.h>
#include <SDL3/SDL.h>

int system_init( void )
{
    SDL_InitFlags flags =
        SDL_INIT_TIMER      |
        SDL_INIT_AUDIO      |
        SDL_INIT_VIDEO      |
        SDL_INIT_JOYSTICK   |
        SDL_INIT_HAPTIC     |
        SDL_INIT_GAMEPAD    |
        SDL_INIT_EVENTS     |
        SDL_INIT_SENSOR     |
        SDL_INIT_CAMERA;

    if ( SDL_Init( flags ) != 0 )
    {
        log_error( "Unable to initialize SDL: %s", SDL_GetError() );
        return SYSTEM_ERROR;
    }

    log_info( "Successfully initialized SDL subsystems" );

    return SYSTEM_SUCCESS;
}

int system_free( void )
{
    log_info( "Shutting down SDL subsystems" );
    SDL_Quit();
    return SYSTEM_SUCCESS;
}
