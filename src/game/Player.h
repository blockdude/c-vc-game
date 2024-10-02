#ifndef SHIP_H
#define SHIP_H

#include "SpaceObject.h"

#include <system/input.h>
#include <math/math.h>
#include <math/vector.h>
#include <math/matrix.h>
#include <util/log.h>

class Player : public SpaceObject
{
public:
	vec2_t move;
	float rotate;
	float force = 1.0f;

	void Reset( void )
	{
		position = { 0.0f };
		velocity = { 0.0f };
		angle = 0.0f;
		angularVelocity = 0.0f;
	}

	void Tick( void )
	{
		SpaceObject::Tick();
		float acceleration = force / mass;
		float angacc = force / ( mass * radius );

		rotate = CLAMP( rotate, -1.0f, 1.0f );
		angularVelocity += rotate * angacc;

		vec2_t direction = vec2_normalize( move );
		direction = vec2_rotate( direction, angle );
		direction = vec2_scale( direction, acceleration );
		velocity = vec2_add( velocity, direction );
	}

	void Step( void )
	{
		this->move = { 0.0f, 0.0f };
		this->rotate = 0.0f;

		if ( input_keystate( K_W ).pressed )
		{
			move.y += 1.0f;
		}

		if ( input_keystate( K_S ).pressed )
		{
			move.y -= 1.0f;
		}

		if ( input_keystate( K_A ).pressed )
		{
			rotate += 1.0f;
		}

		if ( input_keystate( K_D ).pressed )
		{
			rotate -= 1.0f;
		}
	}
};

#endif
