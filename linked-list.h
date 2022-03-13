#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct node node;
typedef struct linkedlist linkedlist;

struct node
{
    void *item;
    node *next;
};

struct linkedlist
{
    node *head;
    node *tail;
    int length;

    void ( *free_item )( void *item );
};

linkedlist *new_linkedlist( void ( *free_item )( void *item ) );
int insert_node( linkedlist *list, void *item );
void list_free( linkedlist *list );

#endif
