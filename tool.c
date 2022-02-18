#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "primitives.h"
#include "linkedlist.h"
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
    BOSS,
    TRAP,
    KEY
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


linkedlist *objects;
int mouse_x;
int mouse_y;
int mouse_state;
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

            float bzx, bzy;
            float azx, azy;

            screen_to_world( mouse_x, mouse_y, &bzx, &bzy );

            if ( event.wheel.y > 0 ) // scroll up (zoom in)
            {
                scale_x += scale_x / 3;
                scale_y += scale_y / 3;
            }
            else if ( event.wheel.y < 0 ) // scroll down (zoom out)
            {
                if ( scale_x > 1 )
                {
                    scale_x -= scale_x / 4;
                    scale_y -= scale_y / 4;
                }
            }

            screen_to_world( mouse_x, mouse_y, &azx, &azy );

            camera_x += bzx - azx;
            camera_y += bzy - azy;

            break;
    }

    return 0;
}

int update()
{
    SDL_RenderClear( renderer );
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

    static int prev_mouse_x = 0;
    static int prev_mouse_y = 0;

    mouse_state = SDL_GetMouseState( &mouse_x, &mouse_y );

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
     * place objects
     */

    if ( ( mouse_state & SDL_BUTTON_LMASK ) != 0 )
    {
        float x, y;
        screen_to_world( mouse_x, mouse_y, &x, &y );
        x = floor( x );
        y = floor( y );
        object *obj = new_object( x, y, 0, WALL, NULL, 100, 0 );
        insert_node( objects, ( void * ) obj );
    }

    /*
     * draw objects
     */

    node *n = objects->head;

    while ( n )
    {
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        object *obj = ( object * ) n->item;
        SDL_Rect temp;
        temp.x = ( obj->x - camera_x ) * scale_x;
        temp.y = ( obj->y - camera_y ) * scale_y;
        temp.w = scale_x;
        temp.h = scale_y;

        SDL_RenderDrawRect( renderer, &temp );
        n = n->next;
    }

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderPresent( renderer );

    /*
     * info
     */

    float world_x, world_y;
    screen_to_world( mouse_x, mouse_y, &world_x, &world_y );

    printf( "---------------------------\n" );
    printf( "fps                :%3.4f\n", fps );
    printf( "objects            :%3d\n", objects->length );
    printf( "mouse_screen_pos   :%3d, %3d\n", mouse_x, mouse_y );
    printf( "mouse_world_pos    :%3.0f, %3.0f\n", world_x, world_y );
    printf( "camera_pos         :%3.0f, %3.0f\n", camera_x, camera_y );
    printf( "scaling            :%3.0f, %3.0f\n", scale_x, scale_y );

    return 0;
}

int main()
{
    objects = new_linkedlist();

    scale_x = 100;
    scale_y = 100;
    camera_x = 0;
    camera_y = 0;
    mouse_x = 0;
    mouse_y = 0;
    mouse_state = 0;

    init_game( 700, 700, "world creation tool" );

    max_fps = 0;

    start_game();
    close_game();

    return 0;
}
