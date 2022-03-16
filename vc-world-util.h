#ifndef VC_WORLD_UTIL
#define VC_WORLD_UTIL

#include "vc-object-defs.h"

struct vc_world;
struct vc_object;
struct vc_result;

typedef struct vc_world vc_world;
typedef struct vc_object vc_object;
typedef struct vc_result vc_result;

/*
 * world
 */

int vc_save_world           ( vc_world *world, char *outfile );
vc_world *vc_load_world     ( char *infile );
int vc_get_object_count     ( vc_world *world );

/*
 * query
 */

vc_result *vc_query_point   ( vc_world *world, int x, int y );
vc_result *vc_query_range   ( vc_world *world, int x, int y, int r );
vc_result *vc_query_rect    ( vc_world *world, int x, int y, int w, int h );
vc_object *vc_poll_result   ( vc_result *result );

/*
 * object
 */

vc_object *vc_new_object    ( double x, double y, enum vc_def_type def );
void vc_get_object_pos      ( vc_object *object, double *x, double *y );
int vc_set_object_pos       ( vc_object *object, double x, double y );
int vc_get_object_comp      ( vc_object *object, enum vc_comp comp );
int vc_set_object_comp      ( vc_object *object, enum vc_comp comp, int new_val );

/*
 * object insertion
 */

int vc_insert_object_nc     ( vc_world *world, vc_object *object );
int vc_insert_object        ( vc_world *world, vc_object *object );
int vc_remove_object        ( vc_world *world, vc_object *object );
int vc_delete_object        ( vc_world *world, int x, int y );
int vc_delete_objects       ( vc_world *world, int x, int y );

/*
 * util
 */

void vc_split_color         ( int color, char *r, char *g, char *b, char *a );
int vc_get_def_comp         ( enum vc_def_type def, enum vc_comp comp );

/*
 * memory
 */

void vc_free_world          ( vc_world *world );
void vc_free_result         ( vc_result *result );
void vc_free_object         ( vc_object *object );

#endif
