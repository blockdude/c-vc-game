#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct node
{
    void *data;

    int next;
    int prev;
};

struct linkedlist
{
    int head;
    int tail;

    struct node *pool;
};

#ifdef __cplusplus
extern "C" {
#endif

int linkedlist_init( struct linkedlist *self );
int linkedlist_insert( struct linkedlist *self, void *data );
int linkedlist_push( struct linkedlist *self, void *data );

#ifdef __cplusplus
}
#endif

#endif
