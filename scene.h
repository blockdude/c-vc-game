#ifndef VC_WORLD_UTIL
#define VC_WORLD_UTIL

#include "defs.h"

struct scene;
struct object;
struct result;

typedef struct scene scene;
typedef struct object object;
typedef struct result result;

/*
 * world
 */

scene *load_scene        ( char *infile );
int save_scene           ( scene *s, char *outfile );
int get_object_count     ( scene *s );

/*
 * query
 */

result *query_point      ( scene *s, int x, int y );
result *query_range      ( scene *s, int x, int y, int r );
result *query_dim        ( scene *s, int x, int y, int w, int h );
result *query_all        ( scene *s );
object *poll_result      ( result *res );
object *back_result      ( result *res );
int reset_result         ( result *res );

/*
 * object
 */

object *new_object       ( float x, float y, enum def d );
void get_object_pos      ( object *obj, float *x, float *y );
int set_object_pos       ( object *obj, float x, float y );
int add_object_pos       ( object *obj, float x, float y );
int get_object_comp      ( object *obj, enum comp c );
int set_object_comp      ( object *obj, enum comp c, int value );
int add_object_comp      ( object *obj, enum comp c, int value );

/*
 * object insertion
 */

int insert_object_nc     ( scene *s, object *obj );  // inserts object to w. does not allow mutiple objects on same x,y.
int insert_object        ( scene *s, object *obj );  // inserts object to w. allows mutiple objects on same x,y.
int remove_object        ( scene *s, object *obj );  // removes object from w without freeing memory.
int delete_object        ( scene *s, int x, int y ); // removes/frees the first object at x,y.
int delete_objects       ( scene *s, int x, int y ); // removes/frees all objects at x,y.

/*
 * util
 */

int get_def_comp         ( enum def d, enum comp c );

/*
 * memory
 */

void free_scene          ( scene *s );
void free_result         ( result *res );
void free_object         ( object *obj );

#endif
