#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "primitives.h"
#include "linkedlist.h"
#include "sdl-draw.h"
#include "sdl-game.h"

#define CAMERA_SPEED 300


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
    int angle;

    int id;
    char *name;

    int hp;
    int armor;
};


linkedlist *objects;
float zoom;
float camera_x;
float camera_y;
int grid_w;
int grid_h;
int cell_w;
int cell_h;


int on_game_creation()
{
    objects = new_linkedlist();

    zoom = 0;
    camera_x = 0;
    camera_y = 0;
    grid_w = 10;
    grid_h = 10;
    cell_w = game.width / grid_w;
    cell_h = game.height / grid_h;

    return 0;
}

int on_game_update()
{
    SDL_RenderClear(game.renderer);
    SDL_SetRenderDrawColor( game.renderer, 0, 0, 0, 255 );

    int x, y;
    int button = SDL_GetMouseState( &x, &y );

    static int prev_mouse_x = 0;
    static int prev_mouse_y = 0;

    /*
     * controls
     */

    if ( game.keystate[ SDL_SCANCODE_W ] )
    {
        camera_y -= game.delta_t * CAMERA_SPEED;
    }

    if ( game.keystate[ SDL_SCANCODE_A ] )
    {
        camera_x -= game.delta_t * CAMERA_SPEED;
    }

    if ( game.keystate[ SDL_SCANCODE_S ] )
    {
        camera_y += game.delta_t * CAMERA_SPEED;
    }

    if ( game.keystate[ SDL_SCANCODE_D ] )
    {
        camera_x += game.delta_t * CAMERA_SPEED;
    }

    /*
     * mouse movement
     */

    if ( ( button & SDL_BUTTON_MMASK ) != 0)
    {
        camera_x += prev_mouse_x - x;
        camera_y += prev_mouse_y - y;
    }

    /*
     * place objects
     */

    if ( ( button & SDL_BUTTON_LMASK ) != 0)
    {

        object *obj = ( object * )malloc( sizeof( object ) );
        obj->id = WALL;
        obj->name = NULL;
        obj->hp = 100;
        obj->armor = 0;

        obj->x = floor( ( x + camera_x ) * grid_w / game.width );
        obj->y = floor( ( y + camera_y ) * grid_h / game.height );
        obj->angle = 0;

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
        temp.x = obj->x * cell_w - camera_x;
        temp.y = obj->y * cell_h - camera_y;
        temp.w = cell_w;
        temp.h = cell_h;

        SDL_RenderDrawRect( game.renderer, &temp );
        n = n->next;
    }

    prev_mouse_x = x;
    prev_mouse_y = y;

    SDL_SetRenderDrawColor( game.renderer, 0, 0, 0, 255 );
    SDL_RenderPresent( game.renderer );

    printf( "---------------------------\n" );
    printf( "fps:\t\t%3.4f\nobjects:\t%3d\nmou_pos:\t%3d, %3d\ncam_pos:\t%3.0f, %3.0f\ncam_zoom:\t%3.0f\n", game.fps, objects->length, x, y, camera_x, camera_y, zoom );

    return 0;
}

int main()
{
    init_game_window( 700, 700, "world creation tool" );
    start_game();
    close_game_window();

    return 0;
}
