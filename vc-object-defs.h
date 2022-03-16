#ifndef VC_OBJECT_DEFS
#define VC_OBJECT_DEFS

enum vc_def_type
{
    VC_DEF_PLAYER,
    VC_DEF_WALL,
    VC_DEF_DOOR,
    VC_DEF_EXIT,
    VC_DEF_LAST,
    VC_DEF_FIRST = VC_DEF_PLAYER
};

enum vc_comp
{
    VC_COMP_COLOR,                  VC_COMP_HEALTH,         VC_COMP_ARMOR,      VC_COMP_DPS, VC_COMP_LAST, VC_COMP_FIRST = VC_COMP_COLOR
};

static const int defs[][ 4 ] =
{
    { 0xff0000ff,                   100,                    0,                  0 },
    { 0x00ff00ff,                   100,                    0,                  0 },
    { 0x0000ffff,                   100,                    0,                  0 },
    { 0x6b6b6bff,                   100,                    0,                  0 }
};

#endif
