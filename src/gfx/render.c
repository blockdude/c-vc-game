#include "render.h"
#include "window.h"

// global renderer
struct render render;

int render_init( void )
{
	if ( window.handle == NULL )
	{
		log_error( "Unable to create SDL renderer: window not initialized" );
		return RENDER_ERROR;
	}

	log_info( "Creating SDL renderer" );

    render.handle = SDL_CreateRenderer( window.handle, NULL );
    if ( render.handle == NULL )
	{
		log_error( "Unable to create SDL renderer: %s", SDL_GetError() );
        return RENDER_ERROR;
	}

    SDL_SetRenderDrawBlendMode( render.handle, SDL_BLENDMODE_BLEND );
	return RENDER_SUCCESS;
}

int render_free( void )
{
	log_info( "Closing SDL renderer" );
	SDL_DestroyRenderer( render.handle );
	return RENDER_SUCCESS;
}

int render_set_color( uint8_t r, uint8_t g, uint8_t b, uint8_t a )
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

int render_line( struct line line )
{
	return SDL_RenderLine( render.handle, line.x0, line.y0, line.x1, line.y1 );
}

int render_rectangle( struct rectangle rectangle )
{
	SDL_FRect r = {
		.x = rectangle.x,
		.y = rectangle.y,
		.w = rectangle.w,
		.h = rectangle.h
	};

	return SDL_RenderRect( render.handle, &r );
}

int render_filled_rectangle( struct rectangle rectangle )
{
	SDL_FRect r = {
		.x = rectangle.x,
		.y = rectangle.y,
		.w = rectangle.w,
		.h = rectangle.h
	};

	return SDL_RenderFillRect( render.handle, &r );
}
