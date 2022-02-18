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
float zoom;
float camera_x;
float camera_y;
int cell_w;
int cell_h;


void screen_to_world( int screen_x, int screen_y, float *world_x, float *world_y )
{
    *world_x = ( float )( screen_x / zoom + camera_x );
    *world_y = ( float )( screen_y / zoom + camera_y );
}

void world_to_screen( float world_x, float world_y, int *screen_x, int *screen_y )
{
    *screen_x = ( int )( ( world_x - camera_x ) * zoom );
    *screen_y = ( int )( ( world_y - camera_y ) * zoom );
}

object *new_object( int x, int y, float angle, int id, char *name, int hp, int armor )
{
    object *obj = ( object * )malloc( sizeof( object ) );
    obj->id = id;
    obj->name = name;
    obj->hp = hp;
    obj->armor = armor;

    obj->x = x;
    obj->y = y;
    obj->angle = angle;

    return obj;
}

int on_game_creation()
{
    objects = new_linkedlist();

    zoom = 100;
    camera_x = 0;
    camera_y = 0;
    cell_w = 1;
    cell_h = 1;

    return 0;
}

int on_game_update()
{
    SDL_RenderClear(game.renderer);
    SDL_SetRenderDrawColor( game.renderer, 0, 0, 0, 255 );

    int mouse_x;
    int mouse_y;
    int button = SDL_GetMouseState( &mouse_x, &mouse_y );

    static int prev_mouse_x = 0;
    static int prev_mouse_y = 0;

    /*
     * zooming
     */

    float bzx, bzy;
    screen_to_world( mouse_x, mouse_y, &bzx, &bzy );

    if ( game.keystate[ SDL_SCANCODE_MINUS ] )
    {
        if ( zoom > 1 )
        {
            zoom -= zoom / 10;
        }
    }

    if ( game.keystate[ SDL_SCANCODE_EQUALS ] )
    {
        zoom += zoom / 10;
    }

    float azx, azy;
    screen_to_world( mouse_x, mouse_y, &azx, &azy );
    camera_x += bzx - azx;
    camera_y += bzy - azy;

    /*
     * panning
     */

    if ( ( button & SDL_BUTTON_MMASK ) != 0)
    {
        camera_x += ( prev_mouse_x - mouse_x ) / zoom;
        camera_y += ( prev_mouse_y - mouse_y ) / zoom;
    }

    prev_mouse_x = mouse_x;
    prev_mouse_y = mouse_y;

    /*
     * place objects
     */

    if ( ( button & SDL_BUTTON_LMASK ) != 0)
    {
        float x, y;
        screen_to_world( mouse_x, mouse_y, &x, &y );
        x = floor( x / cell_w );
        y = floor( y / cell_h );
        object *obj = new_object( x, y, 0, WALL, NULL, 100, 0 );
        insert_node( objects, ( void * )obj );
    }

    /*
     * draw objects
     */

    node *n = objects->head;

    while ( n )
    {
        SDL_SetRenderDrawColor( game.renderer, 255, 255, 255, 255 );
        object *obj = ( object * )n->item;
        SDL_Rect temp;
        temp.x = ( obj->x * cell_w - camera_x ) * zoom;
        temp.y = ( obj->y * cell_h - camera_y ) * zoom;
        temp.w = cell_w * zoom;
        temp.h = cell_h * zoom;

        SDL_RenderDrawRect( game.renderer, &temp );
        n = n->next;
    }

    SDL_SetRenderDrawColor( game.renderer, 0, 0, 0, 255 );
    SDL_RenderPresent( game.renderer );

    /*
     * info
     */

    float world_x, world_y;
    screen_to_world( mouse_x, mouse_y, &world_x, &world_y );

    printf( "---------------------------\n" );
    printf( "fps               :%3.4f\n", game.fps );
    printf( "objects           :%3d\n", objects->length );
    printf( "mouse_screen_pos  :%3d, %3d\n", mouse_x, mouse_y );
    printf( "mouse_world_pos   :%3.0f, %3.0f\n", world_x, world_y );
    printf( "camera_pos        :%3.0f, %3.0f\n", camera_x, camera_y );
    printf( "zoom              :%3.0f\n", zoom );

    return 0;
}

int main()
{
    init_game_window( 700, 700, "world creation tool" );
    start_game();
    close_game_window();

    return 0;
}
