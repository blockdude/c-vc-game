#ifndef ENTITY_H
#define ENTITY_H

#include "../util/util.h"

struct Entity
{
    int32 health;
    int32 stamina;
    int32 mana;
    int32 armor;

    f32 x;
    f32 y;
};

#endif
