#ifndef VCP_KDTREE_H
#define VCP_KDTREE_H

#define KDT_DATA_TYPE int

struct kdtree;

extern struct kdtree *kdt_new( int k, void ( *free_item )( void * ) );
extern void kdt_free( struct kdtree *tree );
extern int kdt_size( struct kdtree *tree );
extern int kdt_dim( struct kdtree *tree );
extern void *kdt_replace( struct kdtree *tree, KDT_DATA_TYPE point[], void *item ); // can return item on insertion or returns existing item on replacement
extern void *kdt_insert( struct kdtree *tree, KDT_DATA_TYPE point[], void *item ); // can return item on success or returns existing item on failure
extern void *kdt_remove( struct kdtree *tree, KDT_DATA_TYPE point[] ); // returns node item if point is found otherwise returns NULL
extern int kdt_delete( struct kdtree *tree, KDT_DATA_TYPE point[] ); // returns 1 on success and 0 on failure
extern void kdt_query_range_func( struct kdtree *tree, KDT_DATA_TYPE point[], KDT_DATA_TYPE range, void ( *func )( void * ) );
extern void **kdt_query_range( struct kdtree *tree, KDT_DATA_TYPE point[], KDT_DATA_TYPE range, int *length );
extern void kdt_query_dim_func( struct kdtree *tree, KDT_DATA_TYPE point[], KDT_DATA_TYPE dim[], void ( *func )( void * ) );
extern void **kdt_query_dim( struct kdtree *tree, KDT_DATA_TYPE point[], KDT_DATA_TYPE dim[], int *length );
extern void *kdt_search( struct kdtree *tree, KDT_DATA_TYPE point[] );
//extern void *kdt_nearest( struct kdtree *tree, KDT_DATA_TYPE point[] );

#endif
