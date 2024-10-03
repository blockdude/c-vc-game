#include "Object.h"
#include "Renderer.h"
#include <common.h>

Object::Object( void )
{
	this->pos = { 0 };
	this->dir = 0.0f;
	this->v   = { 0 };
	this->w   = 0.0f;
	this->m   = 1.0f;
	this->r   = 0.0f;
}

void Object::Tick( void )
{
	// update position and angle
	pos = vec2_add( pos, v );
	dir = fmodf( dir + w, PI * 2.0f );

	// update velocity by drag
	//velocity = vec2_sub( velocity, vec2_scale( velocity, drag ) );
	//angularVelocity -= angularVelocity * drag;
}

void Object::Draw( void )
{
}
