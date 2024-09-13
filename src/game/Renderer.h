#ifndef RENDERER_H
#define RENDERER_H

#include <util/types.h>

void RendererInit( void );
void RendererDraw( void );
void DrawRectangle( rectangle_t rect );
void DrawTriangle( triangle_t tri );

#endif
