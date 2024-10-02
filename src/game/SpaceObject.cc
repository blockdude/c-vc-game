#include "SpaceObject.h"
#include "Renderer.h"
#include <common.h>

SpaceObject::SpaceObject( void )
{
	this->position			= { 0 };
	this->angle				= 0.0f;
	this->velocity			= { 0 };
	this->angularVelocity	= 0.0f;
	this->mass				= 1.0f;
	this->body				= {};
}

void SpaceObject::Init( void )
{
	for ( int x = 0; x < MAXBODYSIZE; x++ )
	{
		for ( int y = 0; y < MAXBODYSIZE; y++ )
		{
			int xCenter = x - ( MAXBODYSIZE / 2 );
			int yCenter = y - ( MAXBODYSIZE / 2 );

			vec2_t center = { ( float ) xCenter, ( float ) yCenter };
			vec2_t origin = { 0.0f, 0.0f };

			float dist = vec2_dist( center, origin );

			if ( dist <= 10 )
			{
				body.blocks[ x ][ y ] = GRASS;
				mass += 1.0f;
				radius = dist > radius ? dist : radius;
			}
		}
	}
	
	log_debug( "Object Mass  : %.2f", mass );
	log_debug( "Object Radius: %.2f", radius );
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
	float *mesh = new float[ BUFFERSIZE ];
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
	delete[] mesh;
}
