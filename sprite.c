#include <stdlib.h>
#include "sprite.h"

sprite *load_sprite( SDL_Renderer *renderer, const char *path, int frame_width, int frame_height, int frame_count, int frame_speed )
{
    // sanity check
    if ( renderer == NULL || path == NULL )
        return NULL;

    sprite *sp = ( sprite * ) malloc( sizeof( sprite ) );
    SDL_Surface *surface = SDL_LoadBMP( path );

    // error check
    if ( surface == NULL )
    {
        free( sp );
        return NULL;
    }

    sp->width = surface->w;
    sp->height = surface->h;

    sp->sprite_sheet = SDL_CreateTextureFromSurface( renderer, surface );
    SDL_FreeSurface( surface );
    
    // error checking
    if ( sp->sprite_sheet == NULL )
    {
        free( sp );
        return NULL;
    }

    sp->frame_width = frame_width;
    sp->frame_height = frame_height;
    sp->frame_count = frame_count;

    // keeps track of the last frame rendered and when
    sp->last_frame = 0;
    sp->ticks_since_last_frame = SDL_GetTicks();
    sp->frame_speed = frame_speed;

    return sp;
}

void free_sprite( sprite *sp )
{
    if ( sp == NULL )
        return;

    SDL_DestroyTexture( sp->sprite_sheet );
    free( sp );
}

void render_sprite( SDL_Renderer *renderer, sprite *sp, SDL_Rect *dst, SDL_RendererFlip flip )
{
    SDL_Rect src = { 0, 0, sp->frame_width, sp->frame_height };
    src.x = sp->last_frame * sp->frame_width;

    // update frame if enough time has elapsed
    unsigned int cur_tick = SDL_GetTicks();
    if ( cur_tick - sp->ticks_since_last_frame >= sp->frame_speed )
    {
        sp->ticks_since_last_frame = cur_tick;
        sp->last_frame = ( sp->last_frame + 1 ) % sp->frame_count;
    }

    SDL_RenderCopyEx( renderer, sp->sprite_sheet, &src, dst, 0, NULL, flip );
}

void render_sprite_last_frame( SDL_Renderer *renderer, sprite *sp, SDL_Rect *dst, SDL_RendererFlip flip )
{
    SDL_Rect src = { 0, 0, sp->frame_width, sp->frame_height };
    src.x = sp->last_frame * sp->frame_width;

    SDL_RenderCopyEx( renderer, sp->sprite_sheet, &src, dst, 0, NULL, flip );
}

void render_sprite_frame( SDL_Renderer *renderer, sprite *sp, SDL_Rect *dst, int frame, SDL_RendererFlip flip )
{
    SDL_Rect src = { 0, 0, sp->frame_width, sp->frame_height };
    src.x = ( frame % sp->frame_count ) * sp->frame_width;

    SDL_RenderCopyEx( renderer, sp->sprite_sheet, &src, dst, 0, NULL, flip );
}
