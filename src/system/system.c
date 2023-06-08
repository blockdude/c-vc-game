#include "system.h"
#include "input.h"
#include "../util/log.h"
#include <SDL2/SDL.h>

int system_init( void )
{
    log_info( "Initializing SDL" );

    if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
    {
        log_error( "Unable to initialize SDL: %s", SDL_GetError() );
        return SYSTEM_ERROR;
    }

    log_info( "Initializing input" );

    input_init();

    return SYSTEM_SUCCESS;
}

int system_free( void )
{
    log_info( "Shutting down SDL subsystems" );
    input_free();
    SDL_Quit();
    return SYSTEM_SUCCESS;
}
