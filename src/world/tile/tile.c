#include "tile.h"

struct tile tiles[ TILE_COUNT ];

#define TILE_DECL( name ) \
	extern void name##_init( void ); \
	name##_init();

int tile_init( void )
{
	TILE_DECL( air );
	TILE_DECL( grass );
	TILE_DECL( dirt );
	TILE_DECL( stone );
	TILE_DECL( water );

	return 0;
}

struct tile *tile_new( int id )
{
	// default tile
	struct tile default_tile = {
		.id				= id,
		.str_id			= NULL,
		.transparent	= false,
		.liquid     	= false,
		.animated   	= false,
		.solid      	= true,
		.use_color  	= false,
		.color      	= 0,
		.drag       	= 1.0f,
		.slip       	= 1.0f,
		.width      	= 1.0f,
		.height     	= 1.0f,
		.offset_x   	= 0.0f,
		.offset_y   	= 0.0f,
		.texture    	= NULL
	};

	// copy default tile to tiles array
	tiles[ id ] = default_tile;

	// return address of new tile
	return &tiles[ id ];
}

struct tile *tile_get( int id )
{
	return &tiles[ id ];
}

/*
 * i don't really know if i want to use this yet.
 * what i want to do here is to be able to create
 * tiles and give them ids dynamically. might to
 * create a trie so i can search the tiles by a
 * string though.
 */

//struct tile *tile_new( char *name )
//{
//	// track next available id
//	static int next_id = 0;
//
//	// don't create new tile type when no available ids
//	if ( next_id >= TILE_COUNT_MAX )
//		return NULL;
//
//	int id = next_id++;
//
//	// default tile
//	tiles[ id ] = {
//		.id				= id,
//		.transparent	= false,
//		.liquid     	= false,
//		.animated   	= false,
//		.solid      	= true,
//		.use_color  	= false,
//		.color      	= 0,
//		.drag       	= 1.0f,
//		.slip       	= 1.0f,
//		.width      	= 1.0f,
//		.height     	= 1.0f,
//		.offset_x   	= 0.0f,
//		.offset_y   	= 0.0f,
//		.texture    	= NULL
//	};
//
//	// return address of new tile
//	return &tiles[ id ];
//}
//
