#ifndef SPRITE
#define SPRITE

#include <SDL2/SDL.h>

typedef struct sprite sprite;

struct sprite
{
    SDL_Texture *sprite_sheet;

    // w and h of entire sheet
    int width;
    int height;

    // w and h of single frame
    int frame_width;
    int frame_height;

    // # of frames in sheet
    int frame_count;

    // ms per frame
    unsigned int frame_speed;

    // tracker for render_sprite
    int last_frame;
    unsigned int ticks_since_last_frame;
};


sprite *load_sprite     ( SDL_Renderer *renderer, const char *path, int frame_width, int frame_height, int frame_count, int frame_speed );
void free_sprite        ( sprite *sp );

void render_sprite      ( SDL_Renderer *renderer, sprite *sp, SDL_Rect *rect, SDL_RendererFlip flip );

#endif
