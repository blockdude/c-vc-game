#ifndef OBJECT_DEFS
#define OBJECT_DEFS

enum def
{
    DEF_FIRST = 0,
    DEF_PLAYER = 0,
    DEF_WALL,
    DEF_DOOR,
    DEF_EXIT,
    DEF_LAST,
};

enum comp
{
    COMP_FIRST = 0,
    COMP_DEF = 0,                COMP_COLOR,                  COMP_HEALTH,         COMP_ARMOR,      COMP_DPS, COMP_LAST
};

static const int defs[][ 6 ] =
{
    { DEF_PLAYER,                0xff0000ff,                     100,                    0,                  0 },
    { DEF_WALL,                  0x00ff00ff,                     100,                    0,                  0 },
    { DEF_DOOR,                  0x0000ffff,                     100,                    0,                  0 },
    { DEF_EXIT,                  0x6b6b6bff,                     100,                    0,                  0 }
};

#endif
