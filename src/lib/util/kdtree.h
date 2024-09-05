#ifndef KDTREE_H
#define KDTREE_H

#define KDT_DATA_TYPE int

#ifdef __cplusplus
extern "C" {
#endif

struct kdtree;

struct kdtree *kdt_new		( int k, void ( *free_item )( void * ) );
void kdt_free            	( struct kdtree *tree );

// getters
int kdt_size                ( struct kdtree *tree );
int kdt_dim                 ( struct kdtree *tree );

// build tools
void *kdt_replace           ( struct kdtree *tree, KDT_DATA_TYPE point[], void *item ); // can return item on insertion or returns existing item on replacement
void *kdt_insert            ( struct kdtree *tree, KDT_DATA_TYPE point[], void *item ); // can return item on success or returns existing item on failure
void *kdt_remove            ( struct kdtree *tree, KDT_DATA_TYPE point[] ); // returns node item if point is found otherwise returns NULL
int kdt_delete              ( struct kdtree *tree, KDT_DATA_TYPE point[] ); // returns 1 on success and 0 on failure

// query tools
void kdt_query_range_func   ( struct kdtree *tree, KDT_DATA_TYPE point[], KDT_DATA_TYPE range, void ( *func )( void * ) );
void **kdt_query_range      ( struct kdtree *tree, KDT_DATA_TYPE point[], KDT_DATA_TYPE range, int *length );

void kdt_query_dim_func     ( struct kdtree *tree, KDT_DATA_TYPE point[], KDT_DATA_TYPE dim[], void ( *func )( void * ) );
void **kdt_query_dim        ( struct kdtree *tree, KDT_DATA_TYPE point[], KDT_DATA_TYPE dim[], int *length );

// search tools
void *kdt_search            ( struct kdtree *tree, KDT_DATA_TYPE point[] );
void *kdt_nearest           ( struct kdtree *tree, KDT_DATA_TYPE point[] );

#ifdef __cplusplus
}
#endif

#endif
