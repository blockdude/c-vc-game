#include "render.h"
#include "window.h"

// some sdl flags that i made global incase i wanted to do something with them
const u32 g_render_flags = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED;

// global renderer
struct render render;

int render_init( void )
{
    render.handle = SDL_CreateRenderer( window.handle, -1, g_render_flags );

    if ( render.handle == NULL )
        return RENDER_ERROR;

    SDL_SetRenderDrawBlendMode( render.handle, SDL_BLENDMODE_BLEND );

	return RENDER_SUCCESS;
}

int render_free( void )
{
	SDL_DestroyRenderer( render.handle );

	return RENDER_SUCCESS;
}

int render_set_color( u8 r, u8 g, u8 b, u8 a )
{
	int error_code = SDL_SetRenderDrawColor( render.handle, r, g, b, a );
	return error_code == 0 ? RENDER_SUCCESS : RENDER_ERROR;
}

int render_clear( void )
{
	int error_code = SDL_RenderClear( render.handle );
	return error_code == 0 ? RENDER_SUCCESS : RENDER_ERROR;
}

int render_present( void )
{
	SDL_RenderPresent( render.handle );
	return render.handle ? RENDER_SUCCESS : RENDER_ERROR;
}
