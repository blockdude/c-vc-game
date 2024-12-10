#include "SpaceObject.h"
#include <common.h>

SpaceObject::SpaceObject( void )
{
	this->com    = { 0 };
	this->pos    = { 0 };
	this->dir    = 0.0f;
	this->v      = { 0 };
	this->w      = 0.0f;
	this->m      = 1.0f;
	this->r      = 0.0f;
	this->chunks = NULL;
}

void SpaceObject::Tick( void )
{
	pos = vec2_add( pos, v );
	dir = fmodf( dir + w, PI * 2.0f );
}

void SpaceObject::Draw( void )
{
}
