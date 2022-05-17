#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

typedef struct linkedlist linkedlist;

struct linkedlist
{
    linkedlist *next;
    linkedlist *prev;
    void *data;
};

void init_linkedlist            ( linkedlist **list );
void free_linkedlist            ( linkedlist *root, void ( *free_data )( void * ) );

linkedlist *linkedlist_insert   ( linkedlist *root, void *data );
linkedlist *linkedlist_remove   ( linkedlist *root, linkedlist *node );

#endif
