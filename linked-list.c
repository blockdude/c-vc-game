#include <stdlib.h>
#include "linked-list.h"

linkedlist *new_linkedlist( void ( *free_item )( void *item ) )
{
    linkedlist *list = ( linkedlist * )malloc( sizeof( linkedlist ) );
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->free_item = free_item;

    return list;
}

node *new_node( void *item )
{
    node *n = ( node * )malloc( sizeof( node ) );
    n->item = item;
    n->next = NULL;

    return n;
}

int insert_node( linkedlist *list, void *item )
{
    if ( list == NULL )
        return -1;

    if ( list->head == NULL )
    {
        list->head = new_node( item );
        list->tail = list->head;
    }
    else
    {
        list->tail->next = new_node( item );
        list->tail = list->tail->next;
    }

    list->length++;

    return 1;
}

void list_free( linkedlist *list )
{
    node *temp;
    while ( list->head != NULL )
    {
        temp = list->head;
        list->head = list->head->next;

        list->free_item( temp->item );
        free( temp );
    }

    free( list );
}

