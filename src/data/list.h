#ifndef LIST_H
#define LIST_H

struct node
{
    void *data;

    int next;
    int prev;
};

struct list
{
    int head;
    int tail;

    struct node *pool;
};

int list_init( struct list *self );
int list_insert( struct list *self, void *data );
int list_push( struct list *self, void *data );

#endif
