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
};

linkedlist *new_linkedlist();
int insert_node( linkedlist *ll, void *item );

#endif
