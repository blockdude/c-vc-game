#ifndef OBJECTS
#define OBJECTS

typedef struct object object;
typedef struct object_def object_def;

enum object_type
{
    PLAYER = 0,
    WALL,
    ENEMY,
    TRAP,
    DOOR,
    EXIT,
    LAST,
    FIRST = PLAYER
};

struct object_def
{
    enum object_type type;
    int color;
    int hp;
    int armor;
    int dps;
};

struct object
{
    int x;
    int y;

    object *next;
    object *prev;

    object_def *def;
};

// object storage
kd_tree *objects;
object *obj_list;
object_def *defs;
const int def_c = 6;

object *new_object( int x, int y, int id )
{
    object *obj = ( object * ) malloc( sizeof( object ) );
    obj->x = x;
    obj->y = y;
    obj->next = NULL;
    obj->prev = NULL;
    obj->def = &defs[ id ];
    return obj;
}

void load_defs( char *infile )
{
    defs = ( object_def * ) malloc( sizeof( object_def ) * def_c );

    defs[ 0 ].type = PLAYER;
    defs[ 0 ].color = 0x00ff00ff;

    defs[ 1 ].type = WALL;
    defs[ 1 ].color = 0x6b6b6bff;

    defs[ 2 ].type = ENEMY;
    defs[ 2 ].color = 0xff0000ff;

    defs[ 3 ].type = TRAP;
    defs[ 3 ].color = 0xb266ffff;

    defs[ 4 ].type = DOOR;
    defs[ 4 ].color = 0x994c00ff;

    defs[ 5 ].type = EXIT;
    defs[ 5 ].color = 0x0000ffff;
}

void load_level( char *infile )
{
}

void free_level()
{
    kd_free( objects );
}

void free_defs()
{
    free( defs );
}

void insert_to_obj_list( object *obj )
{
    if ( obj == NULL )
        return;

    if ( obj_list == NULL )
    {
        obj_list = obj;
    }
    else
    {
        obj->next = obj_list;
        obj_list->prev = obj;
        obj_list = obj;
    }
}

void delete_from_obj_list( object *obj )
{
    if ( obj == NULL )
        return;

    // obj is the head
    if ( obj->prev == NULL )
    {
        obj_list = obj->next;

        if ( obj_list )
            obj_list->prev = NULL;
    }
    else
    {
        obj->prev->next = obj->next;

        if ( obj->next )
            obj->next->prev = obj->prev;
    }

    free( obj );
}

void place_object( float x, float y, int def )
{
    int point[] = { x, y };
    object *obj = new_object( x, y, def );
    insert_to_obj_list( obj );
    kd_insert( objects, point, obj );
}

void remove_object( float x, float y)
{
    int point[] = { x, y };
    object *obj = kd_pull( objects, point );
    delete_from_obj_list( obj );
}

void split_color( int color, char *r, char *g, char *b, char *a )
{
    *r = color >> 24 & 0xff;
    *g = color >> 16 & 0xff;
    *b = color >> 8 & 0xff;
    *a = color & 0xff;
}

#endif
