#ifndef RENDERER_H
#define RENDERER_H

#include <util/types.h>

void RendererInit( void );
void RendererDraw( void );
void RendererClear( void );
void RendererColor( color_t c );
void DrawRectangle( rectangle_t rect, float rot );
void DrawTriangle( triangle_t tri, float rot );

#endif
