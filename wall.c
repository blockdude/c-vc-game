#include "core.h"
#include <stdio.h>

char *name = "wall";

void *create_object()
{
    object *new_obj = ( object * ) malloc( sizeof( object ) );
    new_obj->health = 100;
    new_obj->armor = 100;
    return new_obj;
}

void free_object( void *obj )
{
    free( obj );
}

void on_update( void *obj )
{
}

void on_render( void *obj )
{
    set_render_color( 0, 255, 0, 255 );
    fill_rect_screen( 0, 0, scale.x, scale.y );
}

void on_interact( void *obj )
{
}
