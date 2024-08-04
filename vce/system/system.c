#include "system.h"
#include "input.h"
#include "../util/log.h"
#include <SDL3/SDL.h>

int system_init( void )
{

    log_debug( "Initializing SDL subsystems" );

    SDL_InitFlags flags =
        SDL_INIT_TIMER |
        SDL_INIT_AUDIO |
        SDL_INIT_VIDEO |
        SDL_INIT_JOYSTICK |
        SDL_INIT_HAPTIC |
        SDL_INIT_GAMEPAD |
        SDL_INIT_EVENTS |
        SDL_INIT_SENSOR |
        SDL_INIT_CAMERA;

    if ( SDL_Init( flags ) != 0 )
    {
        log_error( "Unable to initialize SDL: %s", SDL_GetError() );
        return SYSTEM_ERROR;
    }

    log_debug( "Initializing input" );

    input_init();

    return SYSTEM_SUCCESS;
}

int system_free( void )
{
    log_debug( "Shutting down SDL subsystems" );
    input_free();
    SDL_Quit();
    return SYSTEM_SUCCESS;
}
