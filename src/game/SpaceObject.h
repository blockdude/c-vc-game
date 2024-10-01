#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H

#include <util/types.h>

#define MAXBODYSIZE 99

class SpaceObject
{
public:
	static constexpr float drag = 0.0000001f;

	enum BlockType
	{
		NONE,
		GRASS,
		DIRT,
		WATER,
		LAVA,
		STONE
	};

	class Body
	{
	public:
		int	blocks[ MAXBODYSIZE ][ MAXBODYSIZE ];
		int& Get( int x, int y )
		{
			const int xCenter = ( MAXBODYSIZE ) / 2;
			const int yCenter = ( MAXBODYSIZE ) / 2;

			int xOut = xCenter + x;
			int yOut = yCenter + y;

			if ( xOut < 0 || xOut > MAXBODYSIZE )
				xOut = xCenter;

			if ( yOut < 0 || yOut > MAXBODYSIZE )
				yOut = yCenter;

			return blocks[ xOut ][ yOut ];
		}
	};

	vec2_t	position;
	float	angle;
	vec2_t	velocity;
	float	angularVelocity;
	float	mass;
	Body	body;

			SpaceObject( void );
	void    Init( void );
	void	Free( void );
	void	Tick( void );
	void    Step( void );
	void    Draw( void );
};

#endif
