#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H

#include <util/types.h>

enum TileType
{
	NONE,
	GRASS,
	DIRT,
	WATER,
	LAVA,
	STONE
};

struct Chunk
{
	static constexpr int	CHUNKSIZE = 8;
	vec2_t					offset;
	unsigned int *			data;
	size_t					count;

	int			GetTile( int x, int y );
	void		SetTile( int x, int y, int tile );
	void		Tick( void );
	void		Step( void );
	void		Draw( void );
};

class Object
{
public:
	vec2_t  com;		/* center of mass		 */
	vec2_t	pos; 		/* position             */
	float  	dir; 		/* rotation / direction */
	vec2_t 	v;   		/* velocity             */
	float  	w;   		/* angular velocity     */
	float  	m;   		/* mass                 */
	float  	r;   		/* radius               */
	Chunk	**chunks;

			Object( void );
			~Object( void );
	void	Tick( void );
	void    Step( void );
	void    Draw( void );
};

#endif
