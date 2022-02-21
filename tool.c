#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "primitives.h"
#include "linkedlist.h"
#include "kd-tree.h"
#include "sdl-draw.h"
#include "sdl-game.h"

#define CAMERA_SPEED    300
#define ZOOM_SPEED      10

typedef struct object object;

enum object_type
{
    PLAYER,
    WALL,
    DOOR,
    ENEMY,
    TRAP,
    WEAPON,
    ITEM
};

struct object
{
    // note: these are grid coords
    int x;
    int y;
    float angle;

    int id;
    char *name;

    int hp;
    int armor;
};


kd_tree *objects;
float scale_x;
float scale_y;
float camera_x;
float camera_y;


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

object *new_object( int x, int y, float angle, int id, char *name, int hp, int armor )
{
    object *obj = ( object * ) malloc( sizeof( object ) );
    obj->id = id;
    obj->name = name;
    obj->hp = hp;
    obj->armor = armor;

    obj->x = x;
    obj->y = y;
    obj->angle = angle;

    return obj;
}

int handle()
{
    switch ( event.type )
    {
        case SDL_MOUSEWHEEL:

            /*
             * zooming
             */

            const float zs = 1.3f;

            float bzx, bzy;
            float azx, azy;

            screen_to_world( 350, 350, &bzx, &bzy );

            if ( event.wheel.y > 0 ) // scroll up (zoom in)
            {
                scale_x = ceil( scale_x * zs );
                scale_y = ceil( scale_y * zs );
            }
            else if ( event.wheel.y < 0 ) // scroll down (zoom out)
            {
                if ( scale_x != 1 )
                    scale_x = floor( scale_x / zs );

                if ( scale_y != 1 )
                    scale_y = floor( scale_y / zs );
            }

            screen_to_world( 350, 350, &azx, &azy );

            camera_x += bzx - azx;
            camera_y += bzy - azy;

            break;
    }

    return 0;
}

int draw_objects( kd_node *n )
{
    if ( n == NULL )
        return 1;

    object *obj = ( object * ) n->item;
    SDL_Rect temp;
    temp.x = ( obj->x - camera_x ) * scale_x;
    temp.y = ( obj->y - camera_y ) * scale_y;
    temp.w = scale_x;
    temp.h = scale_y;

    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_RenderFillRect( renderer, &temp );

    int r = draw_objects( n->r );
    int l = draw_objects( n->l );
    return r + l;
}

int draw_query()
{
    float x, y;
    screen_to_world( mouse_x, mouse_y, &x, &y );
    x = floor( x );
    y = floor( y );
    int point[] = { x, y };
    void **query = kd_query( objects, point, 350 );

    int i = 0;
    while ( query[ i ] )
    {
        object *obj = ( object * ) query[ i ];
        SDL_Rect temp;
        temp.x = ( obj->x - camera_x ) * scale_x;
        temp.y = ( obj->y - camera_y ) * scale_y;
        temp.w = scale_x;
        temp.h = scale_y;

        SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
        SDL_RenderFillRect( renderer, &temp );
        
        i++;
    }

    free( query );

    return i;
}

int update()
{
    SDL_RenderClear( renderer );

    static int prev_mouse_x = 0;
    static int prev_mouse_y = 0;

    /*
     * panning
     */

    if ( ( mouse_state & SDL_BUTTON_MMASK ) != 0)
    {
        camera_x += ( prev_mouse_x - mouse_x ) / scale_x;
        camera_y += ( prev_mouse_y - mouse_y ) / scale_y;
    }

    prev_mouse_x = mouse_x;
    prev_mouse_y = mouse_y;

    /*
     * place / remove objects
     */

    if ( ( mouse_state & SDL_BUTTON_LMASK ) != 0 )
    {
        float x, y;
        screen_to_world( mouse_x, mouse_y, &x, &y );
        x = floor( x );
        y = floor( y );
        object *obj = new_object( x, y, 0, WALL, NULL, 100, 0 );
        int point[] = { x, y };
        kd_insert( objects, point, ( void * ) obj );
    }

    if ( ( mouse_state & SDL_BUTTON_RMASK ) != 0 )
    {
        float x, y;
        screen_to_world( mouse_x, mouse_y, &x, &y );
        x = floor( x );
        y = floor( y );
        int point[] = { x, y };
        kd_remove( objects, point );
    }

    /*
     * draw objects
     */

    //int ro = draw_objects( objects->root );
    int ro = draw_query();
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderPresent( renderer );

    /*
     * info
     */

    float world_x, world_y;
    screen_to_world( mouse_x, mouse_y, &world_x, &world_y );
    world_x = floor( world_x );
    world_y = floor( world_y );

    printf( "---------------------------\n" );
    printf( "fps                :%3.4f\n", fps );
    printf( "fps_avg            :%3.4f\n", fps_avg );
    printf( "objects            :%3d\n", objects->size );
    printf( "objects_rendered   :%3d\n", ro );
    printf( "mouse_screen_pos   :%3d, %3d\n", mouse_x, mouse_y );
    printf( "mouse_world_pos    :%3.0f, %3.0f\n", world_x, world_y );
    printf( "camera_pos         :%3.0f, %3.0f\n", camera_x, camera_y );
    printf( "scaling            :%3.0f, %3.0f\n", scale_x, scale_y );

    return 0;
}

int main()
{
    init_game( 700, 700, "world creation tool" );

    objects = new_kd_tree( 2, NULL );
    scale_x = 100;
    scale_y = 100;
    camera_x = 0;
    camera_y = 0;

    fps_cap = 60;

    //for ( int i = 0; i < 1000000; i++ )
    //{
    //    int point[] = { rand() % 1000 - 500, rand() % 1000 - 500 };
    //    object *obj = new_object( point[ 0 ], point[ 1 ], 0, WALL, NULL, 100, 0 );
    //    kd_insert( objects, point, obj );
    //}

    start_game();
    close_game();

    kd_free( objects );

    return 0;
}
