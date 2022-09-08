#include "game.h"
#include "../gfx/window.h"
#include "../util/util.h"
#include "../input/input.h"

int game_init( void )
{
    return 0;
}

int game_quit( void )
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
    printf( "frame: %lu\ttick: %lu\n", window.frame.count, window.tick.count );
    printf( "fps  : %u\ttps : %u\n", window.frame.rate, window.tick.rate );

    return 0;
}
