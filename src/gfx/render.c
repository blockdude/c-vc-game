#include "render.h"
#include "window.h"

const u32 g_render_flags = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED;

struct render render;

int render_init( struct world *world )
{
	render.world = world;
    render.handle = SDL_CreateRenderer( window.handle, -1, g_render_flags );

    if ( render.handle == NULL )
        return 1;

    SDL_SetRenderDrawBlendMode( render.handle, SDL_BLENDMODE_BLEND );

	return 0;
}

int render_free( void )
{
    if ( render.handle == NULL )
		return 1;

	SDL_DestroyRenderer( render.handle );
	render.world = NULL;

	return 0;
}

int render_set_color( u8 r, u8 g, u8 b, u8 a )
{
	int error_code = SDL_SetRenderDrawColor( render.handle, r, g, b, a );
	return error_code;
}

int render_clear( void )
{
	int error_code = SDL_RenderClear( render.handle );
	return error_code;
}

int render_present( void )
{
	SDL_RenderPresent( render.handle );
	return 0;
}
