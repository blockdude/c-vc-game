#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "kd-tree.h"
#include "scene.h"
#include "core.h"

/*
 * typedefs
 */

typedef struct sl_list sl_list;

/*
 * structs
 */

struct object
{
    float x;
    float y;
    float w;
    float h;

    scene *s;
    object *next;
    object *prev;
    object *above;
    object *below;
    
    int *comp;

    int type;
    void *obj;
};

struct sl_list
{
    object *root;
    int length;
};

struct scene
{
    kd_tree *obj_tree;
    sl_list *obj_list;
    int obj_c;
};

struct result
{
    object **obj_arr;
    object *current;
    int length;
    int i;
};

/*
 * util functions
 */

static sl_list *new_sl_list()
{
    sl_list *list = ( sl_list * ) malloc( sizeof( sl_list ) );
    list->root = NULL;
    list->length = 0;
    return list;
}

/*
 * scene
 */

scene *load_scene( char *infile )
{
    scene *s = ( scene * ) malloc( sizeof( scene ) );
    s->obj_tree = new_kd_tree( 2, NULL );
    s->obj_list = new_sl_list();
    s->obj_c = 0;

    //if ( infile != NULL )
    //{
    //    FILE *wfile = fopen( infile, "r" );

    //    if ( wfile != NULL )
    //    {
    //        /*
    //         * load s
    //         */

    //        int obj_count;
    //        fscanf( wfile, "%d", &obj_count );

    //        for ( int i = 0; i < obj_count; i++ )
    //        {
    //            // allocate obj
    //            object *obj = ( object * ) malloc( sizeof( object ) );
    //            obj->comp = ( int * ) malloc( sizeof( int ) * COMP_LAST );
    //            obj->s = NULL;
    //            obj->next = NULL;
    //            obj->prev = NULL;
    //            obj->above = NULL;
    //            obj->below = NULL;

    //            // get pos
    //            fscanf( wfile, "%f", &obj->x );
    //            fscanf( wfile, "%f", &obj->y );

    //            // get comp
    //            for ( int j = 0; j < COMP_LAST; j++ )
    //            {
    //                fscanf( wfile, "%d", &obj->comp[ j ] );
    //            }

    //            if ( !insert_object( s, obj ) )
    //            {
    //                free_object( obj );
    //            }
    //        }
    //    }

    //    if ( wfile ) fclose( wfile );
    //}
    
    return s;
}
//
//int save_scene( scene *s, char *outfile )
//{
//    if ( outfile == NULL || s == NULL )
//        return 0;
//
//    int status;
//    FILE *wfile = fopen( outfile, "w" );
//
//    if ( wfile != NULL )
//    {
//        /*
//         * save s
//         */
//        
//        fprintf( wfile, "%d\n", get_object_count( s ) );
//
//        object *x = s->obj_list->root;
//
//        while ( x )
//        {
//            object *y = x;
//
//            while ( y )
//            {
//                /*
//                 * write obj to file
//                 */
//
//                // not precise but good enough i guess
//                fprintf( wfile, "%f\n", y->x );
//                fprintf( wfile, "%f\n", y->y );
//
//                for ( int i = 0; i < COMP_LAST; i++ )
//                {
//                    fprintf( wfile, "%d\n", y->comp[ i ] );
//                }
//
//                y = y->above;
//            }
//
//            x = x->next;
//        }
//
//        status = 1;
//    }
//    else
//    {
//        status = 0;
//    }
//
//    if ( wfile ) fclose( wfile );
//    return status;
//}

/*
 * s getters and setters
 */

int get_object_count( scene *s )
{
    if ( s == NULL )
        return -1;

    return s->obj_c;
}

/*
 * query
 */

result *query_point( scene *s, int x, int y )
{
    int point[] = { x, y };

    result *res = ( result * ) malloc( sizeof( result ) );
    res->obj_arr = NULL;
    res->current = ( object * ) kd_search( s->obj_tree, point );
    res->length = 1;
    res->i = 0;

    return res;
}

result *query_range( scene *s, int x, int y, int r )
{
    int point[] = { x, y };

    result *res = ( result * ) malloc( sizeof( result ) );
    res->obj_arr = ( object ** ) kd_query_range( s->obj_tree, point, r, &res->length );
    res->i = 0;
    res->current = res->obj_arr == NULL ? NULL : res->obj_arr[ 0 ];

    return res;
}

result *query_dim( scene *s, int x, int y, int w, int h )
{
    int point[] = { x, y };
    int dim[] = { w, h };

    result *res = ( result * ) malloc( sizeof( result ) );
    res->obj_arr = ( object ** ) kd_query_dim( s->obj_tree, point, dim, &res->length );
    res->i = 0;
    res->current = res->obj_arr == NULL ? NULL : res->obj_arr[ 0 ];

    return res;
}

object *poll_result( result *res )
{
    if ( res == NULL || res->current == NULL )
        return NULL;


    object *obj = res->current;

    // update current
    if ( obj->above != NULL )
    {
        res->current = obj->above;
    }
    else
    {
        res->i++;
        if ( res->i == res->length )
            res->current = NULL;
        else if ( res->obj_arr != NULL )
            res->current = res->obj_arr[ res->i ];
        else
            res->current = NULL;
    }

    return obj;
}

/*
 * obj create, get, and set
 */

object *new_object( float x, float y, int d )
{
    object *obj = ( object * ) malloc( sizeof( object ) );
    obj->x = x;
    obj->y = y;

    obj->s = NULL;
    obj->next = NULL;
    obj->prev = NULL;
    obj->above = NULL;
    obj->below = NULL;

    obj->comp = NULL;
    obj->type = d;
    obj->obj = def_list[ d ].create_object();

    return obj;
}

void get_object_pos( object *obj, float *x, float *y )
{
    if ( obj == NULL )
        return;

    if ( x ) *x = obj->x;
    if ( y ) *y = obj->y;
}

int set_object_pos( object *obj, float x, float y )
{
    if ( obj == NULL )
        return 0;

    // currently obj_arr cannot be set if it is attached to a s
    if ( obj->s == NULL )
    {
        obj->x = x;
        obj->y = y;
        return 1;
    }
    else
    {
        return 0;
    }
}

int add_object_pos( object *obj, float x, float y )
{
    if ( obj == NULL )
        return 0;

    if ( obj->s == NULL )
    {
        obj->x += x;
        obj->y += y;
        return 1;
    }
    else
    {
        return 0;
    }
}

//int get_object_comp( object *obj, enum comp comp )
//{
//    if ( obj == NULL )
//        return -1;
//
//    return obj->comp[ comp ];
//}
//
//int set_object_comp( object *obj, enum comp comp, int value )
//{
//    if ( obj == NULL )
//        return 0;
//
//    obj->comp[ comp ] = value;
//    return 1;
//}
//
//int add_object_comp( object *obj, enum comp comp, int value )
//{
//    if ( obj == NULL )
//        return 0;
//
//    obj->comp[ comp ] = value;
//    return 1;
//}

/*
 * s obj attaching
 */

static int insert_object_util( sl_list *list, object *node )
{
    if ( node == NULL )
        return 0;

    object *root = list->root;

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

static int insert_object_above_util( sl_list *list, object *a, object *b )
{
    if ( a == NULL || b == NULL )
        return 0;

    if ( list->root == b )
        list->root = a;

    a->next = b->next;
    a->prev = b->prev;
    a->above = b;
    b->below = a;

    b->next = NULL;
    b->prev = NULL;

    if ( a->next )
        a->next->prev = a;

    if ( a->prev )
        a->prev->next = a;

    return 1;
}

// add obj with no collision
int insert_object_nc( scene *s, object *obj )
{
    if ( s == NULL || obj == NULL || obj->s != NULL )
        return 0;

    int point[] = { floor( obj->x ), floor( obj->y ) };
    object *res = kd_insert( s->obj_tree, point, obj );

    if ( res == obj )
    {
        insert_object_util( s->obj_list, obj );
        s->obj_c++;
        obj->s = s;
        return 1;
    }
    else
    {
        return 0;
    }
}

// add obj with no collision
int insert_object( scene *s, object *obj )
{
    if ( s == NULL || obj == NULL || obj->s != NULL )
        return 0;

    int point[] = { floor( obj->x ), floor( obj->y ) };
    object *res = kd_replace( s->obj_tree, point, obj );

    if ( res == NULL )
    {
        return 0;
    }
    else if ( res == obj )
    {
        insert_object_util( s->obj_list, obj );
    }
    else
    {
        insert_object_above_util( s->obj_list, obj, res );
    }

    s->obj_c++;
    obj->s = s;
    return 1;
}

static int remove_object_util( sl_list *list, object *node )
{
    if ( node == NULL || list->root == NULL )
        return 0;

    // if it is at very bottom
    if ( node->below == NULL )
    {
        // if there is no replacement node
        if ( node->above == NULL )
        {
            object *root = list->root;

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
        // if there is a replacement node
        else
        {
            node->above->below = NULL;
            node->above->next = node->next;
            node->above->prev = node->prev;

            if ( node->next != NULL )
                node->next->prev = node->above;

            // check if we are at the root of list
            if ( node->prev != NULL )
                node->prev->next = node->above;
            else
                list->root = node->above;
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

int remove_object( scene *s, object *obj )
{
    if ( s == NULL || obj == NULL || obj->s == NULL )
        return 0;

    if ( obj->s != s )
        return 0;

    int point[] = { floor( obj->x ), floor( obj->y ) };

    // if there is a replacement node
    if ( obj->above != NULL && obj->below == NULL )
    {
        kd_replace( s->obj_tree, point, obj->above );
        remove_object_util( s->obj_list, obj );
    }
    // if there is no replacement node
    else if ( obj->above == NULL && obj->below == NULL )
    {
        kd_remove( s->obj_tree, point );
        remove_object_util( s->obj_list, obj );
    }
    // if node is not in root list
    else if ( obj->below != NULL )
    {
        remove_object_util( s->obj_list, obj );
    }

    s->obj_c--;

    // reset obj
    obj->s = NULL;
    obj->next = NULL;
    obj->prev = NULL;
    obj->above = NULL;
    obj->below = NULL;

    return 1;
}

/*
 * general util function
 */

//int get_def_comp( enum def d, enum comp comp )
//{
//    return defs[ d ][ comp ];
//}

/*
 * memory management
 */

static void free_list( sl_list *list )
{
    object *x = list->root;
    while ( x )
    {
        object *y = x->above;
        while ( y )
        {
            object *temp = y;
            y = y->above;
            free_object( temp );
        }

        object *temp = x;
        x = x->next;
        free_object( temp );
    }
    free( list );
}

void free_scene( scene *s )
{
    if ( s == NULL )
        return;

    kd_free( s->obj_tree );
    free_list( s->obj_list );
    free( s );
}

void free_result( result *res )
{
    if ( res == NULL )
        return;

    free( res->obj_arr );
    free( res );
}

void free_object( object *obj )
{
    if ( obj == NULL )
        return;

    def_list[ obj->type ].free_object( obj->obj );
    free( obj->comp );
    free( obj );
}
