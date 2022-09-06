#include "gfx/window.h"
#include "world/world.h"
#include "tile/tile.h"
#include "util/util.h"

struct world world;

static void init( void )
{
    tile_init();
    world_init( &world );
}

static void close( void )
{
    world_free( &world );
}

static void update( void )
{
    world_update( &world );
}

static void tick( void )
{
    world_tick( &world );
}

static void render( void )
{
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderClear( renderer );

    world_render( &world );

    SDL_RenderPresent( renderer );

    printf( "---------------------------\n" );
    printf( "frame: %ld\ttick: %ld\n", window.frame, window.tick );
    printf( "fps  : %ld\ttps : %ld\n", window.fps, window.tps );
}

int main( void )
{
    window_init( &init, &close, &update, &tick, &render );
    window_start();
    window_close();

    return 0;
}
