#ifndef GAME_ENTITY
#define GAME_ENTITY

#include "core.h"

extern char *name;
extern int flags;
extern int id;

typedef struct entity_data entity_data;
struct entity_data
{
    int health;
    int armor;

    // vector
    float vx;
    float vy;
};

void static_constructor     ();
void static_destructor      ();

void *constructor           ();
void destructor             ( void *data );

void on_creation            ( entity *ent );
void on_deletion            ( entity *ent );

void on_update              ( entity *ent );
void on_render              ( entity *ent );
void on_interact            ( entity *ent );

#endif
