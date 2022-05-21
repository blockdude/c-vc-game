#include <stdlib.h>
#include "object.h"

char *name = "block";
int flags = 0;
int id;

void static_constructor()
{
}

void static_destructor()
{
}

void *constructor()
{
    object_data *data = ( object_data * ) malloc( sizeof( object_data ) );

    data->health = 100;
    data->armor = 0;

    return data;
}

void destructor( void *data )
{
    free( data );
}

void on_creation( object *obj )
{
}

void on_deletion( object *obj )
{
}

void on_update( object *obj )
{
}

void on_render( object *obj )
{
    set_render_color( 105, 105, 105, 255 );
    fill_rect_world( obj->x, obj->y, 1, 1 );
}

void on_interact( object *obj )
{
}
