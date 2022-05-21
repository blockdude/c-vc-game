#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "core.h"

extern char *name;
extern int flags;
extern int id;

typedef struct object_data object_data;
struct object_data
{
    int health;
    int armor;

    float vx;
    float vy;
};

void static_constructor     ();
void static_destructor      ();

void *constructor           ();
void destructor             ( void *data );

void on_creation            ( object *obj );
void on_deletion            ( object *obj );

void on_update              ( object *obj );
void on_render              ( object *obj );
void on_interact            ( object *obj );

#endif
