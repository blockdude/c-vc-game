#include "gfx/window.h"
#include "game/game.h"

int main( void )
{
    window_init( &game_init, &game_close, &game_update, &game_tick, &game_render );
    window_start();
    window_close();

    return 0;
}
