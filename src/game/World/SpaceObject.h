#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H

#include <util/types.h>
#include "Chunk.h"

class SpaceObject
{
public:
	vec2_t  com;		/* center of mass		*/
	vec2_t	pos; 		/* position             */
	float  	dir; 		/* rotation / direction */
	vec2_t 	v;   		/* velocity             */
	float  	w;   		/* angular velocity     */
	float  	m;   		/* mass                 */
	float  	r;   		/* radius               */
	Chunk * chunks;
	size_t  count;

			SpaceObject( void );
			~SpaceObject( void );
	void	Tick( void );
	void    Step( void );
	void    Draw( void );
};

#endif
