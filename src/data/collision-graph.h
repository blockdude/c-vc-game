#ifndef COLLISION_GRAPH_H
#define COLLISION_GRAPH_H

#include <stdint.h>
#include <stdlib.h>

struct collision_node
{
    int64_t x, y;


    // -------
    // |q2|q1|
    // -------
    // |q4|q3|
    // -------
    //
    // This will store the nearest nodes in each quadrant
    struct collision_node *quadrant[ 4 ];
};

struct collision_graph
{
    struct collision_node origin;
    struct collision_node node_pool[ 256 ];

    size_t node_count_max;
    size_t node_count;
};

int collision_graph_init( struct collision_graph *graph );
int collision_graph_free( struct collision_graph *graph );
int collision_graph_node_insert( struct collision_graph *graph, int64_t x, int64_t y );
int collision_graph_node_delete( struct collision_graph *graph, struct collision_node *node );
int collision_graph_node_repair( struct collision_graph *graph, struct collision_node *node );

#endif
