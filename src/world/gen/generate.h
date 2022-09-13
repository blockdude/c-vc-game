#ifndef GENERATE_H
#define GENERATE_H

#include "../../util/util.h"

// forward declaration
struct world;
struct chunk;

void generate_world( struct world *world );
void generate_chunk( struct chunk *chunk );

#endif
