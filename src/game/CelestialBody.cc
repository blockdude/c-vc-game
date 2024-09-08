#include "CelestialBody.h"
#include <cstring>
#include <lib.h>

static float mesh[] = {
	 1.0f,  1.0f, 1.0f,   1.0f, 1.0f, 1.0f,
	 1.0f, -1.0f, 1.0f,   1.0f, 1.0f, 1.0f,
	-1.0f,  1.0f, 1.0f,   1.0f, 1.0f, 1.0f,

	-1.0f, -1.0f, 1.0f,   1.0f, 1.0f, 1.0f,
	 1.0f, -1.0f, 1.0f,   1.0f, 1.0f, 1.0f,
	-1.0f,  1.0f, 1.0f,   1.0f, 1.0f, 1.0f,
};

CelestialBody::CelestialBody( void )
{
	this->position			= { 0 };
	this->angle				= 0.0f;
	this->velocity			= { 0 };
	this->angularVelocity	= 0.0f;
	this->mass				= 0.0f;
	this->body				= {};
}

void CelestialBody::Init( void )
{
	this->body.Get( 0, 0 ) = GRASS;
}

void CelestialBody::Draw( void )
{
}
