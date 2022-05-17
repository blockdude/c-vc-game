#include <stdlib.h>
#include "linkedlist.h"

void init_linkedlist( linkedlist **list )
{
    *list = NULL;
}

void free_linkedlist( linkedlist *root, void ( *free_data )( void * ) )
{
    linkedlist *cur = root;
    while ( cur )
    {
        if ( free_data )
            free_data( cur->data );

        linkedlist *tmp = cur;
        cur = cur->next;
        free( tmp );
    }
}

linkedlist *linkedlist_insert( linkedlist *root, void *data )
{
    linkedlist *new_root = ( linkedlist * )malloc( sizeof( linkedlist ) );
    new_root->next = root;
    new_root->prev = NULL;
    new_root->data = data;
    return new_root;
}

linkedlist *linkedlist_remove( linkedlist *root, linkedlist *node )
{
    linkedlist *new_root = root;

    // if node is root
    if ( node->prev )
        node->prev->next = node->next;
    else
        new_root = node->next;

    if ( node->next )
        node->next->prev = node->prev;


    free( node );
    return new_root;
}
