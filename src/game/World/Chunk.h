#ifndef CHUNK_H
#define CHUNK_H

#include <util/types.h>

struct Chunk
{
	static constexpr int	CHUNKSIZE = 8;
	vec2_t					offset;
	int *					data;
	size_t					count;

	int						GetTile( int x, int y );
	void					SetTile( int x, int y, int tile );
	void					Tick( void );
	void					Step( void );
	void					Draw( void );
};

#endif
