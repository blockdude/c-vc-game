#include <stdlib.h>
#include "linkedlist.h"

linkedlist *new_linkedlist()
{
    linkedlist *ll = ( linkedlist * )malloc( sizeof( linkedlist ) );
    ll->head = NULL;
    ll->tail = NULL;
    ll->length = 0;

    return ll;
}

node *new_node( void *item )
{
    node *n = ( node * )malloc( sizeof( node ) );
    n->item = item;
    n->next = NULL;

    return n;
}

int insert_node( linkedlist *ll, void *item )
{
    if ( ll == NULL )
        return -1;

    if ( ll->head == NULL )
    {
        ll->head = new_node( item );
        ll->tail = ll->head;
    }
    else
    {
        ll->tail->next = new_node( item );
        ll->tail = ll->tail->next;
    }

    ll->length++;

    return 1;
}

