#include "generate.h"
#include "../world.h"
#include "../chunk.h"
#include "../tile/tile.h"

/*
 * temp world gen
 */

void generate_world( struct world *world )
{
    for ( size_t i = 0; i < world->chunks_count; i++ )
    {
        generate_chunk( &world->chunks[ i ] );
    }
}

void generate_chunk( struct chunk *chunk )
{
    for ( int i = 0; i < CHUNK_VOLUME; i++ )
    {
        int z = i / ( CHUNK_SIZE_X * CHUNK_SIZE_Y );

        // level 14 and below will be dirt
        if ( z < 15 )
        {
            chunk->tiles[ i ].id = TILE_DIRT;
        }
        // level 15 and above will be air
        if ( z > 15 )
        {
            chunk->tiles[ i ].id = TILE_AIR;
        }
        // level 15 will be grass
        if ( z == 15 )
        {
            chunk->tiles[ i ].id = TILE_GRASS;
        }
    }
}
