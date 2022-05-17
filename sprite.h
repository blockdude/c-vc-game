#ifndef SPRITE
#define SPRITE

#include <SDL2/SDL.h>

typedef struct sprite sprite;

sprite *load_sprite                 ( SDL_Renderer *renderer, const char *path, int frame_width, int frame_height, int frame_count, int frame_speed );
void free_sprite                    ( sprite *sp );

void render_sprite                  ( SDL_Renderer *renderer, sprite *sp, SDL_Rect *dst, SDL_RendererFlip flip );
void render_sprite_last_frame       ( SDL_Renderer *renderer, sprite *sp, SDL_Rect *dst, SDL_RendererFlip flip );
void render_sprite_frame            ( SDL_Renderer *renderer, sprite *sp, SDL_Rect *dst, int frame, SDL_RendererFlip flip );

#endif
