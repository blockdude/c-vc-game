#include "SpaceObject.h"
#include "Renderer.h"
#include <common.h>

SpaceObject::SpaceObject( void )
{
	this->position			= { 0 };
	this->angle				= 0.0f;
	this->velocity			= { 0 };
	this->angularVelocity	= 0.0f;
	this->mass				= 0.0f;
	this->body				= {};
}

void SpaceObject::Init( void )
{
	this->body.Get(  0,  0 ) = GRASS;
	this->body.Get(  0,  1 ) = GRASS;
	this->body.Get(  1,  0 ) = GRASS;
	this->body.Get( -1,  0 ) = GRASS;
	this->body.Get( -1, -1 ) = GRASS;
	this->body.Get(  1, -1 ) = GRASS;
}

void SpaceObject::Tick( void )
{
	// update position and angle
	position = vec2_add( position, velocity );
	angle = fmodf( angle + angularVelocity, PI * 2.0f );

	// update velocity by drag
	velocity = vec2_sub( velocity, vec2_scale( velocity, drag ) );
	angularVelocity -= angularVelocity * drag;
}

void SpaceObject::Draw( void )
{
	float mesh[ 2048 ] = { 0 };
	int vertexCount = 0;

	for ( int x = 0; x < MAXBODYSIZE; x++ )
	{
		for ( int y = 0; y < MAXBODYSIZE; y++ )
		{
			if ( body.blocks[ x ][ y ] )
			{
				int xCenter = x - ( MAXBODYSIZE / 2 );
				int yCenter = y - ( MAXBODYSIZE / 2 );

				mesh[ vertexCount++ ] = -0.5f + xCenter;
				mesh[ vertexCount++ ] =  0.5f + yCenter;
				mesh[ vertexCount++ ] =  0.0f;

				mesh[ vertexCount++ ] =  0.0f;
				mesh[ vertexCount++ ] =  1.0f;
				mesh[ vertexCount++ ] =  0.0f;

				mesh[ vertexCount++ ] =  0.5f + xCenter;
				mesh[ vertexCount++ ] =  0.5f + yCenter;
				mesh[ vertexCount++ ] =  0.0f;

				mesh[ vertexCount++ ] =  0.0f;
				mesh[ vertexCount++ ] =  1.0f;
				mesh[ vertexCount++ ] =  0.0f;

				mesh[ vertexCount++ ] = -0.5f + xCenter;
				mesh[ vertexCount++ ] = -0.5f + yCenter;
				mesh[ vertexCount++ ] =  0.0f;

				mesh[ vertexCount++ ] =  0.0f;
				mesh[ vertexCount++ ] =  1.0f;
				mesh[ vertexCount++ ] =  0.0f;



				mesh[ vertexCount++ ] =  0.5f + xCenter;
				mesh[ vertexCount++ ] =  0.5f + yCenter;
				mesh[ vertexCount++ ] =  0.0f;

				mesh[ vertexCount++ ] =  0.0f;
				mesh[ vertexCount++ ] =  1.0f;
				mesh[ vertexCount++ ] =  0.0f;

				mesh[ vertexCount++ ] =  0.5f + xCenter;
				mesh[ vertexCount++ ] = -0.5f + yCenter;
				mesh[ vertexCount++ ] =  0.0f;

				mesh[ vertexCount++ ] =  0.0f;
				mesh[ vertexCount++ ] =  1.0f;
				mesh[ vertexCount++ ] =  0.0f;

				mesh[ vertexCount++ ] = -0.5f + xCenter;
				mesh[ vertexCount++ ] = -0.5f + yCenter;
				mesh[ vertexCount++ ] =  0.0f;

				mesh[ vertexCount++ ] =  0.0f;
				mesh[ vertexCount++ ] =  1.0f;
				mesh[ vertexCount++ ] =  0.0f;
			}
		}
	}

	DrawMesh( mesh, vertexCount, this->position, { 1.0f, 1.0f }, this->angle );
}
