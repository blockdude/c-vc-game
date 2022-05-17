#include <stdlib.h>
#include <SDL2/SDL.h>

#define KDT_DATA_TYPE float
#include "kdtree.h"
#include "linkedlist.h"

#include <dirent.h>
#include <dlfcn.h>

#include "core.h"

/*
 * structs
 */

typedef struct handle handle;
struct handle
{
    char *name;

    void *( *create )();
    void ( *delete )( void * );

    void ( *init )();
    void ( *exit )();
    void ( *update )( void * );
    void ( *render )( void * );
    void ( *interact )( void * );
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

handle entity_handle[ 1 ];
handle object_handle[ 1 ];

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

entity *add_entity( int id, float x, float y )
{
    entity *new_entity = ( entity * ) malloc( sizeof( entity ) );
    new_entity->x = x;
    new_entity->y = y;
    new_entity->w = 1;
    new_entity->h = 1;
    new_entity->id = id;
    new_entity->l = NULL;
    new_entity->data = entity_handle[ id ].create();

    float point[] = { x, y };
    void *res = kdt_insert( entity_tree, point, new_entity );

    if ( res != new_entity )
    {
        entity_handle[ id ].delete( new_entity->data );
        free( new_entity );
        return NULL;
    }
    
    return new_entity;
}

object *add_object( int id, float x, float y )
{
    object *new_object = ( object * ) malloc( sizeof( object ) );
    new_object->x = x;
    new_object->y = y;
    new_object->w = 1;
    new_object->h = 1;
    new_object->id = id;
    new_object->l = NULL;
    new_object->data = object_handle[ id ].create();

    float point[] = { x, y };
    void *res = kdt_insert( object_tree, point, new_object );

    if ( res != new_object )
    {
        object_handle[ id ].delete( new_object->data );
        free( new_object );
        return NULL;
    }
    
    return new_object;
}

void del_entity( entity *ent )
{
    if ( !ent )
        return;

    float point[] = { ent->x, ent->y };
    void *res = kdt_remove( entity_tree, point );

    if ( res == NULL )
        return;

    unload_entity( ent );
    entity_handle[ ent->id ].delete( ent->data );
    free( ent );
}

void del_object( object *obj )
{
    if ( !obj )
        return;

    float point[] = { obj->x, obj->y };
    void *res = kdt_remove( object_tree, point );

    if ( res == NULL )
        return;

    unload_object( obj );
    object_handle[ obj->id ].delete( obj->data );
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
    if ( ent->l != NULL )
        return;

    ent->l = ( unload * ) malloc( sizeof( unload ) );
    ent->l->src = src;
    ent->l->can_unload = can_unload;

    loaded_ents = linkedlist_insert( loaded_ents, ent );
}

void load_object( object *obj, void *src, int ( *can_unload )( void *, void * ) )
{
    if ( obj->l != NULL )
        return;
        
    obj->l = ( unload * ) malloc( sizeof( unload ) );
    obj->l->src = src;
    obj->l->can_unload = can_unload;

    loaded_objs = linkedlist_insert( loaded_objs, obj );
}

void unload_entity( entity *ent )
{
    if ( ent->l == NULL )
        return;

    free( ent->l );
    ent->l = NULL;
}

void unload_object( object *obj )
{
    if ( obj->l == NULL )
        return;

    free( obj->l );
    obj->l = NULL;
}

void update_loaded_entities()
{
    linkedlist *cur = loaded_ents;
    while ( cur )
    {
        entity *ent = cur->data;
        update_entity( ent );

        if ( ent->l != NULL )
        {
            int res = ent->l->can_unload( ent, ent->l->src );
            if ( res )
            {
                unload_entity( ent );
            }
        }

        linkedlist *tmp = cur;
        cur = cur->next;
        if ( ent->l == NULL )
        {
            loaded_ents = linkedlist_remove( loaded_ents, tmp );
        }
    }
}

void update_loaded_objects()
{
    linkedlist *cur = loaded_objs;
    while ( cur )
    {
        object *obj = cur->data;
        update_object( obj );

        if ( obj->l != NULL )
        {
            int res = obj->l->can_unload( obj, obj->l->src );
            if ( res )
            {
                unload_object( obj );
            }
        }

        linkedlist *tmp = cur;
        cur = cur->next;
        if ( obj->l == NULL )
        {
            loaded_objs = linkedlist_remove( loaded_objs, cur );
        }
    }
}

/*
 * init functions
 */

static void load_entity_handles_from_dir()
{
    void *handle = dlopen( "./data/entities/player.so", RTLD_LAZY );

    if ( handle == NULL )
    {
        printf( "%s", dlerror() );
        exit( 1 );
    }

    entity_handle[ 0 ].name = dlsym( handle, "name" );

    if ( entity_handle[ 0 ].name == NULL )
    {
        printf( "%s", dlerror() );
        exit( 1 );
    }

    entity_handle[ 0 ].create = dlsym( handle, "constructor" );

    if ( entity_handle[ 0 ].create == NULL )
    {
        printf( "%s", dlerror() );
        exit( 1 );
    }

    entity_handle[ 0 ].delete = dlsym( handle, "destructor" );

    if ( entity_handle[ 0 ].delete == NULL )
    {
        printf( "%s", dlerror() );
        exit( 1 );
    }

    entity_handle[ 0 ].init = dlsym( handle, "on_game_load" );

    if ( entity_handle[ 0 ].init == NULL )
    {
        printf( "%s", dlerror() );
        exit( 1 );
    }

    entity_handle[ 0 ].exit = dlsym( handle, "on_game_exit" );

    if ( entity_handle[ 0 ].exit == NULL )
    {
        printf( "%s", dlerror() );
        exit( 1 );
    }

    entity_handle[ 0 ].update = dlsym( handle, "on_update" );

    if ( entity_handle[ 0 ].update == NULL )
    {
        printf( "%s", dlerror() );
        exit( 1 );
    }

    entity_handle[ 0 ].render = dlsym( handle, "on_render" );

    if ( entity_handle[ 0 ].render == NULL )
    {
        printf( "%s", dlerror() );
        exit( 1 );
    }

    entity_handle[ 0 ].interact = dlsym( handle, "on_interact" );

    if ( entity_handle[ 0 ].interact == NULL )
    {
        printf( "%s", dlerror() );
        exit( 1 );
    }

    entity_handle[ 0 ].init();
}

void init_core()
{
    object_tree = new_kdtree( 2, NULL );
    entity_tree = new_kdtree( 2, NULL );
    load_entity_handles_from_dir();
}

void free_core()
{
    free_kdtree( object_tree );
    free_kdtree( entity_tree );
    free_linkedlist( loaded_objs, NULL );
    free_linkedlist( loaded_ents, NULL );
}

/*
 * mouse getter functions
 */

/*
 * drawing util functions
 */

void screen_to_world( int screen_x, int screen_y, float *world_x, float *world_y )
{
    *world_x = ( float ) ( screen_x / scale_x + camera_x );
    *world_y = ( float ) ( screen_y / scale_y + camera_y );
}

void world_to_screen( float world_x, float world_y, int *screen_x, int *screen_y )
{
    *screen_x = ( int ) ( ( world_x - camera_x ) * scale_x );
    *screen_y = ( int ) ( ( world_y - camera_y ) * scale_y );
}

void screen_to_world_f( float screen_x, float screen_y, float *world_x, float *world_y )
{
    *world_x = ( float ) ( screen_x / scale_x + camera_x );
    *world_y = ( float ) ( screen_y / scale_y + camera_y );
}

void world_to_screen_f( float world_x, float world_y, float *screen_x, float *screen_y )
{
    *screen_x = ( float ) ( ( world_x - camera_x ) * scale_x );
    *screen_y = ( float ) ( ( world_y - camera_y ) * scale_y );
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
