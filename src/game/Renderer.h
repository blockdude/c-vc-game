#ifndef RENDERER_H
#define RENDERER_H

#include "SpaceObject.h"
#include <util/types.h>

#define BUFFERSIZE 50000

void RendererInit( void );
void RendererDraw( void );
void RendererClear( void );
void RendererColor( color_t c );

void DrawMesh( const float *mesh, int c, vec2_t pos, vec2_t scale, float angle );

void DrawRectangle( rectangle_t rect, float angle );
void DrawTriangle( triangle_t tri, float angle );

void DrawSpaceObject( SpaceObject *obj );

#endif
