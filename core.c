#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "kdtree.h"
#include "linkedlist.h"

#ifdef __linux__
#define _GNU_SOURCE
#include <dirent.h>
#include <dlfcn.h>
#include <sys/types.h>
#endif

#include "core.h"

/*
 * structs
 */

typedef struct function_data function_data;
struct function_data
{
    void *handle;
    char *name;
    int type;

    void ( *static_constructor )();
    void ( *static_destructor )();

    void *( *constructor )();
    void ( *destructor )( void * );

    void ( *on_creation )( void * );
    void ( *on_deletion )( void * );

    void ( *update )( void * );
    void ( *render )( void * );
    void ( *interact )( void * );
};

typedef struct private_data private_data;
struct private_data
{
    // load and unload stuff
    char is_loaded;
    linkedlist *node;
    object *src;
    int ( *can_unload )( object *, object * );
};

/*
 * sdl window variables
 */

void *window;
void *renderer;

int window_w = 700;
int window_h = 700;

float delta_t = 0;
float fps_cur = 0;
float fps_avg = 0;
float fps_cap = 0;

int frame = 0;

char quit = 0;
char pause = 0;

/*
 * mouse state variables
 */

const unsigned char *keystate;

/*
 * world state variables
 */

float scale_x = 100;
float scale_y = 100;
float camera_x = 0;
float camera_y = 0;

/*
 * world items
 */

kdtree *object_tree = NULL;
linkedlist *loaded_objs = NULL;

int object_count = 0;
function_data object_handle[ 256 ];

/*
 * init functions
 */

static void load_function_data_from_dir( char *path )
{
#ifdef __linux__
    DIR *dirp;
    struct dirent *entry;

    dirp = opendir( path );

    if ( dirp == NULL )
        return;

    static int id = 0;
    char buffer[ 256 ];
    while ( ( entry = readdir( dirp ) ) != NULL )
    {
        char *file_ex;
        file_ex = strrchr( entry->d_name, '.' );

        // check if it is a linux shared object file
        if ( strcmp( file_ex, ".so" ) == 0 )
        {
            strcpy( buffer, path );
            strcat( buffer, "/" );
            strcat( buffer, entry->d_name );

            void *handle = dlopen( buffer, RTLD_LAZY );

            if ( handle == NULL )
            {
                printf( "%s\n", dlerror() );
                exit( 1 );
            }

            object_handle[ id ].handle = handle;
            object_handle[ id ].name = dlsym( handle, "name" );
            object_handle[ id ].type = *( int * )dlsym( handle, "type" );

            object_handle[ id ].static_constructor = dlsym( handle, "static_constructor" );
            object_handle[ id ].static_destructor = dlsym( handle, "static_destructor" );

            object_handle[ id ].constructor = dlsym( handle, "constructor" );
            object_handle[ id ].destructor = dlsym( handle, "destructor" );

            object_handle[ id ].on_creation = dlsym( handle, "on_creation" );
            object_handle[ id ].on_deletion = dlsym( handle, "on_deletion" );

            object_handle[ id ].update = dlsym( handle, "on_update" );
            object_handle[ id ].render = dlsym( handle, "on_render" );
            object_handle[ id ].interact = dlsym( handle, "on_interact" );

            *( int * )dlsym( handle, "id" ) = id;

            object_count++;
            id++;
        }
    }

    closedir( dirp );
#endif
}

static void call_static_constructors( function_data *fdata, int c )
{
    for ( int i = 0; i < c; i++ )
        fdata[ i ].static_constructor();
}

void init_core()
{
    object_tree = new_kdtree( 2, NULL );
    load_function_data_from_dir( "./data/objects" );
    load_function_data_from_dir( "./data/entities" );
    call_static_constructors( object_handle, object_count );
}

void free_core()
{
    free_kdtree( object_tree );
    free_linkedlist( loaded_objs, NULL );

    /*
     * still need to free memory for:
     *
     * * function data
     * * all objects
     * * all entities
     */
}


/*
 * query functions
 */

object **query_objects( float x, float y, float w, float h, int *l )
{
    float point[] = { x, y };
    float dim[] = { w, h };
    object **res = ( object ** ) kdt_query_dim( object_tree, point, dim, l );
    return res;
}

object **query_objects_radius( float x, float y, float r, int *l )
{
    float point[] = { x, y };
    object **res = ( object ** ) kdt_query_range( object_tree, point, r, l );
    return res;
}

object *find_object( float x, float y )
{
    float point[] = { x, y };
    return kdt_search( object_tree, point );
}

void query_objects_func( float x, float y, float w, float h, void ( *func )( object * ) )
{
    float point[] = { x, y };
    float dim[] = { w, h };
    kdt_query_dim_func( object_tree, point, dim, func );
}

void free_object_query( object **query )
{
    free( query );
}

/*
 * object & object functions
 */

char *get_object_name( object *obj )
{
    return object_handle[ obj->id ].name;
}

int get_object_type( object *obj )
{
    return object_handle[ obj->id ].type;
}

void update_object( object *obj )
{
    object_handle[ obj->id ].update( obj );
}

void render_object( object *obj )
{
    object_handle[ obj->id ].render( obj );
}

void interact_object( object *obj )
{
    object_handle[ obj->id ].interact( obj );
}

static private_data *new_private_data()
{
    private_data *pd = ( private_data * ) malloc( sizeof( private_data ) );
    pd->is_loaded = 0;
    pd->node = NULL;
    pd->src = NULL;
    pd->can_unload = NULL;

    return pd;
}

static void free_private_data( private_data *pd )
{
    free( pd );
}

object *create_object( int id, float x, float y )
{
    object *new_object = ( object * ) malloc( sizeof( object ) );
    new_object->x = x;
    new_object->y = y;
    new_object->w = 1;
    new_object->h = 1;
    new_object->id = id;
    new_object->data = object_handle[ id ].constructor();
    new_object->priv = new_private_data();

    float point[] = { x, y };
    void *res = kdt_insert( object_tree, point, new_object );

    if ( res != new_object )
    {
        object_handle[ id ].destructor( new_object->data );
        free_private_data( new_object->priv );
        free( new_object );
        return NULL;
    }

    object_handle[ id ].on_creation( new_object );
    return new_object;
}

void delete_object( object *obj )
{
    if ( !obj )
        return;

    float point[] = { obj->x, obj->y };
    void *res = kdt_remove( object_tree, point );

    if ( res == NULL )
        return;

    unload_object( obj );
    object_handle[ obj->id ].on_deletion( obj );
    object_handle[ obj->id ].destructor( obj->data );
    free_private_data( obj->priv );
    free( obj );
}

int object_add_pos( object *obj, float dx, float dy )
{
    if ( !obj )
        return -1;

    int x = obj->x + dx;
    int y = obj->y + dy;

    if ( obj->x == x && obj->y == y )
        return 1;

    float point_dst[] = { x, y };
    void *res = kdt_insert( object_tree, point_dst, obj );

    if ( res != obj )
        return 0;

    float point_src[] = { obj->x, obj->y };
    kdt_remove( object_tree, point_src );

    obj->x = x;
    obj->y = y;

    return 1;
}

int object_set_pos( object *obj, float x, float y )
{
    if ( !obj )
        return -1;

    if ( obj->x == x && obj->y == y )
        return 1;

    float point_dst[] = { x, y };
    void *res = kdt_insert( object_tree, point_dst, obj );

    if ( res != obj )
        return 0;

    float point_src[] = { obj->x, obj->y };
    kdt_remove( object_tree, point_src );

    obj->x = x;
    obj->y = y;

    return 1;
}

void load_object( object *obj, object *src, int ( *can_unload )( object *, object * ) )
{
    private_data *pd = obj->priv;

    if ( pd->is_loaded )
        return;

    loaded_objs = linkedlist_insert( loaded_objs, obj );

    pd->is_loaded = 1;
    pd->node = loaded_objs; // the node we want will be at the front of the linked list
    pd->src = src;
    pd->can_unload = can_unload;
}

void unload_object( object *obj )
{
    private_data *pd = obj->priv;

    if ( !pd->is_loaded )
        return;

    loaded_objs = linkedlist_remove( loaded_objs, pd->node );

    pd->is_loaded = 0;
    pd->node = NULL;
    pd->src = NULL;
    pd->can_unload = NULL;
}

void update_loaded_objects()
{
    linkedlist *cur = loaded_objs;
    while ( cur )
    {
        object *obj = cur->data;
        private_data *pd = obj->priv;
        cur = cur->next;

        update_object( obj );

        if ( pd->is_loaded )
        {
            if ( pd->can_unload == NULL || pd->can_unload( obj, pd->src ) )
            {
                unload_object( obj );
            }
        }
    }
}

/*
 * mouse getter functions
 */

/*
 * drawing util functions
 */

int get_mouse_screen( int *x, int *y )
{
    return SDL_GetMouseState( x, y );
}

int get_mouse_tile( int *x, int *y )
{
    int ms = SDL_GetMouseState( x, y );

    float tmp_x = *x;
    float tmp_y = *y;

    screen_to_world_f( tmp_x, tmp_y, &tmp_x, &tmp_y );
    *x = floor( tmp_x );
    *y = floor( tmp_y );

    return ms;
}

int get_mouse_world( float *x, float *y )
{
    int tmp_x;
    int tmp_y;
    int ms = SDL_GetMouseState( &tmp_x, &tmp_y );
    screen_to_world( tmp_x, tmp_y, x, y );
    return ms;
}

void screen_to_world( int screen_x, int screen_y, float *world_x, float *world_y )
{
    float offset_x = window_w / 2.0f;
    float offset_y = window_h / 2.0f;

    *world_x = ( float ) ( ( screen_x - offset_x ) / scale_x + camera_x );
    *world_y = ( float ) ( ( screen_y - offset_y ) / scale_y + camera_y );
}

void world_to_screen( float world_x, float world_y, int *screen_x, int *screen_y )
{
    float offset_x = window_w / 2.0f;
    float offset_y = window_h / 2.0f;

    *screen_x = ( int ) ( ( world_x - camera_x ) * scale_x + offset_x );
    *screen_y = ( int ) ( ( world_y - camera_y ) * scale_y + offset_y );
}

void screen_to_world_f( float screen_x, float screen_y, float *world_x, float *world_y )
{
    float offset_x = window_w / 2.0f;
    float offset_y = window_h / 2.0f;

    *world_x = ( float ) ( ( screen_x - offset_x ) / scale_x + camera_x );
    *world_y = ( float ) ( ( screen_y - offset_y ) / scale_y + camera_y );
}

void world_to_screen_f( float world_x, float world_y, float *screen_x, float *screen_y )
{
    float offset_x = window_w / 2.0f;
    float offset_y = window_h / 2.0f;

    *screen_x = ( float ) ( ( world_x - camera_x ) * scale_x + offset_x );
    *screen_y = ( float ) ( ( world_y - camera_y ) * scale_y + offset_y );
}

void set_render_color( char r, char g, char b, char a )
{
    SDL_SetRenderDrawColor( renderer, r, g, b, a );
}

void draw_circle_screen( float x0, float y0, float r )
{
    float diameter = r + r;
    int x = r - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - diameter;

    while (x >= y)
    {
        SDL_RenderDrawPoint( renderer, x0 + x, y0 + y );
        SDL_RenderDrawPoint( renderer, x0 + y, y0 + x );
        SDL_RenderDrawPoint( renderer, x0 - y, y0 + x );
        SDL_RenderDrawPoint( renderer, x0 - x, y0 + y );
        SDL_RenderDrawPoint( renderer, x0 - x, y0 - y );
        SDL_RenderDrawPoint( renderer, x0 - y, y0 - x );
        SDL_RenderDrawPoint( renderer, x0 + y, y0 - x );
        SDL_RenderDrawPoint( renderer, x0 + x, y0 - y );

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - diameter;
        }
    }
}

void draw_circle_world( float x, float y, float r )
{
    world_to_screen_f( x, y, &x, &y );
    r = r * scale_x;

    draw_circle_screen( x, y, r );
}

void draw_rect_screen( float x, float y, float w, float h )
{
    SDL_FRect rect = { x, y, w, h };
    SDL_RenderDrawRectF( renderer, &rect );
}

void fill_rect_screen( float x, float y, float w, float h )
{
    SDL_FRect rect = { x, y, w, h };
    SDL_RenderFillRectF( renderer, &rect );
}

void draw_rect_world( float x, float y, float w, float h )
{
    world_to_screen_f( x, y, &x, &y );
    w = w * scale_x;
    h = h * scale_y;

    SDL_FRect rect = { x, y, w, h };
    SDL_RenderDrawRectF( renderer, &rect );
}

void fill_rect_world( float x, float y, float w, float h )
{
    world_to_screen_f( x, y, &x, &y );
    w = w * scale_x;
    h = h * scale_y;

    SDL_FRect rect = { x, y, w, h };
    SDL_RenderFillRectF( renderer, &rect );
}
