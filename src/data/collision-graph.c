#include "collision-graph.h"
#include "../util/util.h"

#define flipbits( n, b ) ( ( n ) ^ ( ( 1u << ( b ) ) - 1 ) )

static int get_quadrant( int64_t x0, int64_t y0, int64_t x1, int64_t y1 )
{
    int64_t dx = x1 - x0;
    int64_t dy = y1 - y0;

    int quad = ( ( ( dx << 63 ) & 1 ) << 1 ) | ( ( dy << 63 ) & 1 );
    return quad;
}

static int get_distance( int64_t x0, int64_t y0, int64_t x1, int64_t y1 )
{
    int64_t dx = x1 - x0;
    int64_t dy = y1 - y0; 

    dx = dx * dx;
    dy = dy * dy;

    // return square distance
    return dx + dy;
}

static struct collision_node *new_node( struct collision_graph *graph, int64_t x, int64_t y )
{
    if ( graph == NULL || graph->node_count == graph->node_count_max )
        return NULL;

    // get node from pool
    struct collision_graph *node = &graph->node_pool[ graph->node_count++ ];

    // init values
    node.x = x;
    node.y = y;
    node.quadrant[ 0 ] = NULL;
    node.quadrant[ 1 ] = NULL;
    node.quadrant[ 2 ] = NULL;
    node.quadrant[ 3 ] = NULL;

    return node;
}

int collision_graph_init( struct collision_graph *graph )
{
    if ( graph == NULL )
        return -1;

    graph->origin.x = 0;
    graph->origin.y = 0;
    graph->node_count_max = 256;
    graph->node_count = 0;

    return 0;
}

int collision_graph_free( struct collision_graph *graph )
{
    return 0;
}

int collision_graph_node_insert( struct collision_graph *graph, int64_t x, int64_t y )
{
    if ( graph == NULL )
        return -1;

    struct collision_node *new_node = new_node( graph, x, y );

    if ( node == NULL )
        return -1;

    struct collision_node *insert = &graph->origin;
    while ( insert != NULL )
    {
        // get node from quadrant
        int quad = get_quadrant( insert->x, insert->y, x, y );
        int opposite_quad = flipbits( quad, 2 );
        struct collision_node *tmp = insert->quadrand[ quad ];

        // new node can be placed in this quadrant
        if ( tmp == NULL )
        {
            insert->quadrant[ quad ] = new_node;
            new_node->quadrant[ opposite_quad ] = insert;

            // grab other three quadrant connections if we can

        }

        // check which node is closer
        int dist_a = get_distance( tmp->x, tmp->y, insert->x, insert->y );
        int dist_b = get_distance( node->x, node->y, insert->x, insert->y );

        // tmp node is closer
        if ( dist_a <= dist_b )
        {
            // tranverse and recalculate the quad section to go to
            insert = tmp;
            quad = get_quadrant( insert->x, insert->y, node->x, node->y );
            continue;
        }
        // new node is closer
        else
        {
            // insert node and repair connections

        }
    }

    graph->origin.quadrant[ quad ] = node;
    quad = flipbits( quad, 2 );

    node->quadrant[ quad ] = &graph->origin;
    
    return 0;
}

int collision_graph_node_delete( struct collision_graph *graph, struct collision_node *node )
{
    return 0;
}

int collision_graph_node_repair( struct collision_graph *graph, struct collision_node *node )
{
    return 0;
}
