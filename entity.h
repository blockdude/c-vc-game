#ifndef GAME_ENTITY
#define GAME_ENTITY

#include "core.h"

extern char *name;  // assign a name
extern int id;      // id will be given

typedef struct entity_data entity_data;
struct entity_data
{
    int health;
    int armor;
};

void *constructor   ();
void destructor     ( void *data );

void on_game_load   ();
void on_game_exit   ();
void on_update      ( entity *ent );
void on_render      ( entity *ent );
void on_interact    ( entity *ent );

#endif
