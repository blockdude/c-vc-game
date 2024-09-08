#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include <util/types.h>

#define MAXBODYSIZE 15

class CelestialBody
{
	class Body
	{
	public:
		int	blocks[ MAXBODYSIZE ][ MAXBODYSIZE ];
		int& Get( int x, int y )
		{
			const int xCenter = ( MAXBODYSIZE + 1 ) / 2;
			const int yCenter = ( MAXBODYSIZE + 1 ) / 2;

			int xOut = xCenter + x;
			int yOut = yCenter + y;

			if ( xOut < 0 || xOut > MAXBODYSIZE )
				xOut = xCenter;

			if ( yOut < 0 || yOut > MAXBODYSIZE )
				yOut = yCenter;

			return blocks[ xOut ][ yOut ];
		}
	};

public:
	enum BlockType
	{
		NONE,
		GRASS,
		DIRT,
		WATER,
		LAVA,
		STONE
	};

	vec2_t	position;
	float	angle;
	vec2_t	velocity;
	float	angularVelocity;
	float	mass;
	Body	body;

			CelestialBody( void );
	void    Init( void );
	void	Free( void );
	void	Tick( void );
	void    Update( void );
	void    Draw( void );
};

#endif
