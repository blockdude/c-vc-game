#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "primitives.h"
#include "sdl-draw.h"
#include "sdl-game.h"


typedef struct node node;
typedef struct linkedlist linkedlist;


struct node
{
    SDL_Rect rect;
    node *next;
};

struct linkedlist
{
    node *head;
    node *tail;
};


linkedlist *objects;


linkedlist *new_linkedlist()
{
    linkedlist *ll = ( linkedlist * )malloc( sizeof( linkedlist ) );
    ll->head = NULL;
    ll->tail = NULL;

    return ll;
}

node *new_node( SDL_Rect rect )
{
    node *n = ( node * )malloc( sizeof( node ) );
    n->rect.x = rect.x;
    n->rect.y = rect.y;
    n->rect.w = rect.w;
    n->rect.h = rect.h;
    n->next = NULL;

    return n;
}

int insert_node( linkedlist *ll, SDL_Rect rect )
{
    if ( ll == NULL )
        return -1;

    if ( ll->head == NULL )
    {
        ll->head = new_node( rect );
        ll->tail = ll->head;
    }
    else
    {
        ll->tail->next = new_node( rect );
        ll->tail = ll->tail->next;
    }

    return 1;
}

int on_game_creation()
{
    objects = new_linkedlist();
    return 0;
}

int on_game_update()
{
    if ( game.keystate[ SDL_SCANCODE_W ] )
    {
        SDL_Rect rect;
        rect.x = 0;
        rect.y = 0;
        rect.h = 0;
        rect.w = 0;

        insert_node( objects, rect );
    }

    printf( "%f\n", game.fps );

    return 0;
}

int main()
{
    init_game_window( 500, 500, "world creation tool" );
    start_game();
    close_game_window();

    return 0;
}
