#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "entity.h"
#include "util.h"

char *name = "player";
int id = 0;

float player_speed = 4.0f;

int can_unload( void *dst, void *src )
{
    return 0;
}

void static_constructor()
{
    entity *player = create_entity( 0, 0, 0 );
    load_entity( player, NULL, &can_unload );
}

void static_destructor()
{
}

void *constructor()
{
    entity_data *data = ( entity_data * ) malloc( sizeof( entity_data ) );

    data->health = 100;
    data->armor = 0;
    data->vx = 0;
    data->vy = 0;

    return data;
}

void destructor( void *data )
{
    free( data );
}

void on_creation( entity *ent )
{
}

void on_deletion( entity *ent )
{
}

void on_update( entity *ent )
{
    entity_data *data = ent->data;
    data->vx = 0;
    data->vy = 0;

    if ( keystate[ SDL_SCANCODE_W ] )
    {
        data->vy -= 1.0f;
    }

    if ( keystate[ SDL_SCANCODE_S ] )
    {
        data->vy += 1.0f;
    }

    if ( keystate[ SDL_SCANCODE_A ] )
    {
        data->vx -= 1.0f;
    }

    if ( keystate[ SDL_SCANCODE_D ] )
    {
        data->vx += 1.0f;
    }

    normalize( data->vx, data->vy, &data->vx, &data->vy );

    float dx = data->vx * delta_t * player_speed;
    float dy = data->vy * delta_t * player_speed;
    entity_add_pos( ent, dx, dy );
}

void on_render( entity *obj )
{
    set_render_color( 255, 0, 0, 255 );
    draw_circle_world( obj->x, obj->y, 0.5f );
}

void on_interact( entity *obj )
{
}
