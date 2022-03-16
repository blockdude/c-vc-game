#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kd-tree.h"
#include "vc-world-util.h"

typedef struct vc_list vc_list;

// complete object
struct vc_object
{
    double x;
    double y;

    vc_world *world;
    vc_object *next;
    vc_object *prev;
    vc_object *above;
    vc_object *below;
    
    int *comp;
};

// list
struct vc_list
{
    vc_object *root;
    int length;
};

// world
struct vc_world
{
    kd_tree *obj_tree;
    vc_list *obj_list;
    int obj_c;
};

struct vc_result
{
    vc_object **objects;
    vc_object *current;
    int i;
    int length;
};

static vc_list *new_vc_list()
{
    vc_list *list = ( vc_list * ) malloc( sizeof( vc_list ) );
    list->root = NULL;
    list->length = 0;
    return list;
}

vc_object *vc_new_object( double x, double y, enum vc_def_type def )
{
    vc_object *object = ( vc_object * ) malloc( sizeof( vc_object ) );
    object->x = x;
    object->y = y;
    object->world = NULL;
    object->next = NULL;
    object->prev = NULL;
    object->above = NULL;
    object->below = NULL;
    object->comp = ( int * ) malloc( sizeof( int ) * VC_COMP_LAST );
    
    // copy comp from def
    for ( int i = 0; i < VC_COMP_LAST; i++ )
        object->comp[ i ] = vc_get_def_comp( def, i );

    return object;
}

vc_world *vc_load_world( char *infile )
{
    vc_world *world = ( vc_world * ) malloc( sizeof( vc_world ) );

    if ( infile == NULL )
    {
        world->obj_tree = new_kd_tree( 2, NULL );
        world->obj_list = new_vc_list();
        world->obj_c = 0;
    }
    else
    {
        /*
         * place holder. need to create a way to save and
         * load worlds to a file
         */

        vc_free_world( world );
        world = NULL;
    }

    return world;
}

int vc_save_world( vc_world *world, char *outfile )
{
    if ( outfile == NULL || world == NULL )
        return 0;

    return 1;
}

int vc_get_object_count( vc_world *world )
{
    if ( world == NULL )
        return -1;

    return world->obj_c;
}

void vc_get_object_pos( vc_object *object, double *x, double *y )
{
    if ( object == NULL )
        return;

    if ( x ) *x = object->x;
    if ( y ) *y = object->y;
}

int vc_set_object_pos( vc_object *object, double x, double y )
{
    if ( object == NULL )
        return 0;

    if ( object->world == NULL )
    {
        object->x = x;
        object->y = y;
        return 1;
    }
    else
    {
        return 0;
    }
}

int vc_get_object_comp( vc_object *object, enum vc_comp comp )
{
    if ( object == NULL )
        return -1;

    return object->comp[ comp ];
}

int vc_set_object_comp( vc_object *object, enum vc_comp comp, int value )
{
    if (object == NULL )
        return 0;

    object->comp[ comp ] = value;
    return 1;
}

vc_result *vc_query_point( vc_world *world, int x, int y )
{
    int point[] = { x, y };

    vc_result *result = ( vc_result * ) malloc( sizeof( vc_result ) );
    result->objects = NULL;
    result->current = ( vc_object * ) kd_search( world->obj_tree, point );
    result->length = 1;
    result->i = 0;

    return result;
}

vc_result *vc_query_range( vc_world *world, int x, int y, int r )
{
    int point[] = { x, y };

    vc_result *result = ( vc_result * ) malloc( sizeof( vc_result ) );
    result->objects = ( vc_object ** ) kd_query_range( world->obj_tree, point, r, &result->length );
    result->i = 0;
    result->current = result->objects == NULL ? NULL : result->objects[ 0 ];

    return result;
}

vc_result *vc_query_rect( vc_world *world, int x, int y, int w, int h )
{
    int point[] = { x, y };
    int dim[] = { w, h };

    vc_result *result = ( vc_result * ) malloc( sizeof( vc_result ) );
    result->objects = ( vc_object ** ) kd_query_dim( world->obj_tree, point, dim, &result->length );
    result->i = 0;
    result->current = result->objects == NULL ? NULL : result->objects[ 0 ];

    return result;
}

vc_object *vc_poll_result( vc_result *result )
{
    if ( result == NULL || result->current == NULL )
        return NULL;

    if ( result->i == result->length )
        return NULL;

    vc_object *object = result->current;

    // update current
    if ( object->above != NULL )
    {
        result->current = object->above;
    }
    else
    {
        if ( result->objects != NULL )
            result->current = result->objects[ ++result->i ];
        else
            result->current = NULL;
    }

    return object;
}

int vc_result_length( vc_result *result )
{
    if ( result == NULL )
        return 0;

    return result->length;
}

vc_object *vc_result_get( vc_result *result, int i )
{
    if ( result == NULL )
        return NULL;

    if ( i >= result->length || i < 0 )
        return NULL;

    return result->objects[ i ];
}

static int insert_object_util( vc_list *list, vc_object *node )
{
    if ( node == NULL )
        return 0;

    vc_object *root = list->root;

    if ( root == NULL )
    {
        root = node;
    }
    else
    {
        node->next = root;
        root->prev = node;
        root = node;
    }

    list->root = root;
    list->length++;
    return 1;
}

static int insert_object_above_util( vc_object *a, vc_object *b )
{
    if ( a == NULL || b == NULL )
        return 0;

    b->above = a->above;
    b->below = a;
    a->above = b;

    if ( b->above )
    {
        b->above->below = b;
    }

    return 1;
}

// add object with no collision
int vc_insert_object_nc( vc_world *world, vc_object *object )
{
    if ( world == NULL || object == NULL || object->world != NULL )
        return 0;

    int point[] = { floor( object->x ), floor( object->y ) };
    vc_object *res = kd_insert( world->obj_tree, point, object );

    if ( res == object )
    {
        insert_object_util( world->obj_list, object );
        world->obj_c++;
        object->world = world;
        return 1;
    }
    else
    {
        return 0;
    }
}

// add object with no collision
int vc_insert_object( vc_world *world, vc_object *object )
{
    if ( world == NULL || object == NULL )
        return 0;

    int point[] = { floor( object->x ), floor( object->y ) };
    vc_object *res = kd_insert( world->obj_tree, point, object );

    if ( res == NULL )
    {
        return 0;
    }
    else if ( res == object )
    {
        insert_object_util( world->obj_list, object );
    }
    else
    {
        insert_object_above_util( res, object );
    }

    world->obj_c++;
    object->world = world;
    return 1;
}

static int remove_object_util( vc_list *list, vc_object *node )
{
    if ( node == NULL || list->root == NULL )
        return 0;

    // if it is at very bottom
    if ( node->below == NULL )
    {
        if ( node->above == NULL )
        {
            vc_object *root = list->root;

            // node is the root
            if ( node->prev == NULL )
            {
                root = node->next;

                // set new root prev
                if ( root )
                    root->prev = NULL;
            }
            else
            {
                node->prev->next = node->next;

                if ( node->next )
                    node->next->prev = node->prev;
            }

            list->root = root;
            list->length--;
        }
        else
        {
            node->above->below = NULL;
            node->above->next = node->next;
            node->above->prev = node->prev;
        }
    }
    else
    {
        node->below->above = node->above;

        if ( node->above != NULL )
            node->above->below = node->below;
    }

    return 1;
}

int vc_remove_object( vc_world *world, vc_object *object )
{
    if ( world == NULL || object == NULL || object->world == NULL )
        return 0;

    if ( object->world != world )
        return 0;

    int point[] = { floor( object->x ), floor( object->y ) };

    if ( object->above != NULL && object->below == NULL )
    {
        kd_replace( world->obj_tree, point, object->above );
        remove_object_util( world->obj_list, object );
    }
    else if ( object->above == NULL && object->below == NULL )
    {
        kd_remove( world->obj_tree, point );
        remove_object_util( world->obj_list, object );
    }
    else if ( object->below != NULL )
    {
        remove_object_util( world->obj_list, object );
    }

    world->obj_c--;

    // reset object
    object->world = NULL;
    object->next = NULL;
    object->prev = NULL;
    object->above = NULL;
    object->below = NULL;

    return 1;
}

void vc_split_color( int color, char *r, char *g, char *b, char *a )
{
    if ( r ) *r = color >> 24 & 0xff;
    if ( g ) *g = color >> 16 & 0xff;
    if ( b ) *b = color >> 8 & 0xff;
    if ( a ) *a = color & 0xff;
}

static void free_list( vc_list *list )
{
    vc_object *x = list->root;
    while ( x )
    {
        vc_object *y = x->above;
        while ( y )
        {
            vc_object *temp = y;
            y = y->above;
            vc_free_object( temp );
        }

        vc_object *temp = x;
        x = x->next;
        vc_free_object( temp );
    }
    free( list );
}

void vc_free_world( vc_world *world )
{
    /*
     * kd_free should free the list because i passed a
     * function pointer to tell the kd_tree how to free the
     * node
     */

    if ( world == NULL )
        return;

    kd_free( world->obj_tree );
    free_list( world->obj_list );
    free( world );
}

void vc_free_result( vc_result *result )
{
    if ( result == NULL )
        return;

    free( result->objects );
    free( result );
}

void vc_free_object( vc_object *object )
{
    if ( object == NULL )
        return;

    free( object->comp );
    free( object );
}

int vc_get_def_comp( enum vc_def_type def, enum vc_comp comp )
{
    return defs[ def ][ comp ];
}
