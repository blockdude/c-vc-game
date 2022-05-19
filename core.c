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
    void *src;
    int ( *can_unload )( void *, void * );
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

int mouse_state = 0;
int mouse_screen_x = 0;
int mouse_screen_y = 0;
int mouse_tile_x = 0;
int mouse_tile_y = 0;
float mouse_world_x = 0;
float mouse_world_y = 0;

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
kdtree *entity_tree = NULL;

linkedlist *loaded_objs = NULL;
linkedlist *loaded_ents = NULL;

int entity_count;
int object_count;
function_data *entity_handle;
function_data *object_handle;

/*
 * init functions
 */

static function_data *load_function_data_from_dir( char *path, int *len )
{
#ifdef __linux__
    function_data *fdata;

    int file_count = 0;

    DIR *dirp;
    struct dirent *entry;

    dirp = opendir( path );

    if ( dirp == NULL )
        return NULL;

    while ( ( entry = readdir( dirp ) ) != NULL )
    {
        char *file_ex;
        file_ex = strrchr( entry->d_name, '.' );

        // check if it is a linux shared object file
        if ( strcmp( file_ex, ".so" ) == 0 )
        {
            file_count++;
        }
    }

    // setup
    fdata = ( function_data * ) malloc( sizeof( function_data ) * file_count );
    *len = file_count;

    rewinddir( dirp );

    int id = 0;
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

            fdata[ id ].handle = handle;
            fdata[ id ].name = dlsym( handle, "name" );

            fdata[ id ].static_constructor = dlsym( handle, "static_constructor" );
            fdata[ id ].static_destructor = dlsym( handle, "static_destructor" );

            fdata[ id ].constructor = dlsym( handle, "constructor" );
            fdata[ id ].destructor = dlsym( handle, "destructor" );

            fdata[ id ].on_creation = dlsym( handle, "on_creation" );
            fdata[ id ].on_deletion = dlsym( handle, "on_deletion" );

            fdata[ id ].update = dlsym( handle, "on_update" );
            fdata[ id ].render = dlsym( handle, "on_render" );
            fdata[ id ].interact = dlsym( handle, "on_interact" );

            *( int * )dlsym( handle, "id" ) = id;

            id++;
        }
    }

    closedir( dirp );

    return fdata;
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
    entity_tree = new_kdtree( 2, NULL );
    entity_handle = load_function_data_from_dir( "./data/entities", &entity_count );
    object_handle = load_function_data_from_dir( "./data/objects", &object_count );
    call_static_constructors( entity_handle, entity_count );
    call_static_constructors( object_handle, object_count );
}

void free_core()
{
    free_kdtree( object_tree );
    free_kdtree( entity_tree );
    free_linkedlist( loaded_objs, NULL );
    free_linkedlist( loaded_ents, NULL );

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

entity **query_entities( float x, float y, float w, float h, int *l )
{
    float point[] = { x, y };
    float dim[] = { w, h };
    entity **res = ( entity ** ) kdt_query_dim( entity_tree, point, dim, l );
    return res;
}

void query_objects_func( float x, float y, float w, float h, void ( *func )( void * ) )
{
    float point[] = { x, y };
    float dim[] = { w, h };
    kdt_query_dim_func( object_tree, point, dim, func );
}

void query_entities_func( float x, float y, float w, float h, void ( *func )( void * ) )
{
    float point[] = { x, y };
    float dim[] = { w, h };
    kdt_query_dim_func( entity_tree, point, dim, func );
}

void query_entities_range_func( float x, float y, float r, void ( *func )( void * ) )
{
    float point[] = { x, y };
    kdt_query_range_func( entity_tree, point, r, func );
}

void free_object_query( object **query )
{
    free( query );
}

void free_entity_query( entity **query )
{
    free( query );
}

/*
 * object & entity functions
 */

void update_entity( entity *ent )
{
    entity_handle[ ent->id ].update( ent );
}

void render_entity( entity *ent )
{
    entity_handle[ ent->id ].render( ent );
}

void interact_entity( entity *ent )
{
    entity_handle[ ent->id ].interact( ent );
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

entity *create_entity( int id, float x, float y )
{
    entity *new_entity = ( entity * ) malloc( sizeof( entity ) );
    new_entity->x = x;
    new_entity->y = y;
    new_entity->w = 1;
    new_entity->h = 1;
    new_entity->id = id;
    new_entity->data = entity_handle[ id ].constructor();
    new_entity->priv = new_private_data();

    float point[] = { x, y };
    void *res = kdt_insert( entity_tree, point, new_entity );

    if ( res != new_entity )
    {
        entity_handle[ id ].destructor( new_entity->data );
        free_private_data( new_entity->priv );
        free( new_entity );
        return NULL;
    }

    entity_handle[ id ].on_creation( new_entity );
    return new_entity;
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

void delete_entity( entity *ent )
{
    if ( !ent )
        return;

    float point[] = { ent->x, ent->y };
    void *res = kdt_remove( entity_tree, point );

    if ( res == NULL )
        return;

    unload_entity( ent );
    entity_handle[ ent->id ].on_deletion( ent );
    entity_handle[ ent->id ].destructor( ent->data );
    free_private_data( ent->priv );
    free( ent );
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

int entity_add_pos( entity *ent, float dx, float dy )
{
    if ( !ent )
        return -1;

    void *res;

    float point_src[] = { ent->x, ent->y };
    res = kdt_remove( entity_tree, point_src );

    if ( res == NULL )
        return -1;

    ent->x += dx;
    ent->y += dy;

    float point_dst[] = { ent->x, ent->y };
    res = kdt_insert( entity_tree, point_dst, ent );

    if ( res != ent )
    {
        kdt_insert( entity_tree, point_src, ent );
        return 0;
    }

    return 1;
}

int entity_set_pos( entity *ent, float x, float y )
{
    if ( !ent )
        return -1;

    void *res;

    float point_src[] = { ent->x, ent->y };
    res = kdt_remove( entity_tree, point_src );

    if ( res == NULL )
        return -1;

    ent->x = x;
    ent->y = y;

    float point_dst[] = { ent->x, ent->y };
    res = kdt_insert( entity_tree, point_dst, ent );

    if ( res != ent )
    {
        kdt_insert( entity_tree, point_src, ent );
        return 0;
    }

    return 1;
}

void load_entity( entity *ent, void *src, int ( *can_unload )( void *, void * ) )
{
    private_data *pd = ent->priv;

    if ( pd->is_loaded )
        return;

    loaded_ents = linkedlist_insert( loaded_ents, ent );

    pd->is_loaded = 1;
    pd->node = loaded_ents; // the node we want will be at the front of the linked list
    pd->src = src;
    pd->can_unload = can_unload;
}

void load_object( object *obj, void *src, int ( *can_unload )( void *, void * ) )
{
    private_data *pd = obj->priv;

    if ( pd->is_loaded )
        return;

    loaded_objs = linkedlist_insert( loaded_objs, obj );

    pd->is_loaded = 1;
    pd->node = loaded_ents; // the node we want will be at the front of the linked list
    pd->src = src;
    pd->can_unload = can_unload;
}

void unload_entity( entity *ent )
{
    private_data *pd = ent->priv;

    if ( !pd->is_loaded )
        return;

    loaded_ents = linkedlist_remove( loaded_ents, pd->node );

    pd->is_loaded = 0;
    pd->node = NULL;
    pd->src = NULL;
    pd->can_unload = NULL;
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

void update_loaded_entities()
{
    linkedlist *cur = loaded_ents;
    while ( cur )
    {
        entity *ent = cur->data;
        private_data *pd = ent->priv;
        cur = cur->next;

        update_entity( ent );

        if ( pd->is_loaded )
        {
            if ( pd->can_unload == NULL || pd->can_unload( ent, pd->src ) )
            {
                unload_entity( ent );
            }
        }
    }
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
