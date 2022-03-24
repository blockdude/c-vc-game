#ifndef VC_OBJECT_DEFS
#define VC_OBJECT_DEFS

enum vc_def_type
{
    VC_DEF_FIRST = 0,
    VC_DEF_PLAYER = 0,
    VC_DEF_WALL,
    VC_DEF_DOOR,
    VC_DEF_EXIT,
    VC_DEF_LAST,
};

enum vc_comp
{
    VC_COMP_FIRST = 0,
    VC_COMP_DEF = 0,                VC_COMP_COLOR,                  VC_COMP_HEALTH,         VC_COMP_ARMOR,      VC_COMP_DPS, VC_COMP_LAST
};

static const int defs[][ 6 ] =
{
    { VC_DEF_PLAYER,                0xff0000ff,                     100,                    0,                  0 },
    { VC_DEF_WALL,                  0x00ff00ff,                     100,                    0,                  0 },
    { VC_DEF_DOOR,                  0x0000ffff,                     100,                    0,                  0 },
    { VC_DEF_EXIT,                  0x6b6b6bff,                     100,                    0,                  0 }
};

#endif
