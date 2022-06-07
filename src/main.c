#include "tile/tile.h"
#include "util/util.h"

static void init()
{
    tile_init();
}

static void close()
{
}

static void update()
{
}

static void tick()
{
}

static void render()
{
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderClear( renderer );

    SDL_RenderPresent( renderer );

    printf( "---------------------------\n" );
    printf( "frame              :%3ld\n",            window.frame );
    printf( "tick               :%3ld\n",            window.tick );
    printf( "fps                :%3.4lf\n",          window.fps );
    printf( "tps                :%3.4lf\n",          window.tps );
}

int main()
{
    window_init( &init, &close, &update, &tick, &render );
    window_start();
    window_close();

    return 0;
}
