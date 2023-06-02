#include "collision-state.h"
#include "state.h"
#include "../gfx/window.h"
#include "../gfx/render.h"
#include "../util/util.h"
#include "../input/input.h"
#include "../data/collision-graph.h"

struct collision_graph graph;

int collision_state_init( void )
{
    log_info( "collision state initializing" );
    collision_graph_init( &graph );

    log_info( "inserting graph nodes" );
    collision_graph_node_insert( &graph, 1, 1 );
    collision_graph_node_insert( &graph, -1, 1 );
    collision_graph_node_insert( &graph, 1, -1 );
    collision_graph_node_insert( &graph, -1, -1 );
    log_info( "graph node count: %zu", graph.node_count );

    return 0;
}

int collision_state_free( void )
{
    collision_graph_free( &graph );
    return 0;
}

int collision_state_tick( void )
{
    return 0;
}

int collision_state_update( void )
{
    return 0;
}

int collision_state_render( void )
{
    render_set_color( 255, 255, 255, 255 );
    render_clear();

    render_set_color( 0, 0, 0, 255 );
    for ( size_t i = 0; i < graph.node_count; i++ )
    {
        struct collision_node *node = &graph.node_pool[ i ];
        int offset = 250;
        struct line line = {
            .x0 = offset,
            .y0 = offset,
            .x1 = node->x * 100 + offset,
            .y1 = node->y * 100 + offset
        };

        render_line( line );

        int size = 25;
        struct rectangle rec = {
            .x = node->x * 100 + offset - ( size / 2 ),
            .y = node->y * 100 + offset - ( size / 2 ),
            .w = size,
            .h = size
        };
        render_filled_rectangle( rec );
    }

    render_present();

    char buff[ 256 ];
    sprintf( buff, "frame : %5lu | fps : %u | tick : %5lu | tps : %u", window.frame.count, window.frame.rate, window.frame.count, window.tick.rate );
    window_set_title( buff );

    return 0;
}
