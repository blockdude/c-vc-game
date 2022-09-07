#include "game.h"
#include "../gfx/window.h"
#include "../util/util.h"

int game_init( void )
{
    return 0;
}

int game_close( void )
{
    return 0;
}

int game_update( void )
{
    return 0;
}

int game_tick( void )
{
    return 0;
}

int game_render( void )
{
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderClear( renderer );

    SDL_RenderPresent( renderer );

    printf( "---------------------------\n" );
    printf( "frame: %ld\ttick: %ld\n", window.frame, window.tick );
    printf( "fps  : %ld\ttps : %ld\n", window.fps, window.tps );

    return 0;
}
