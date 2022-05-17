#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "entity.h"
#include "util.h"

char *name = "player";
int id = 0;

float vx = 0.0f;
float vy = 0.0f;
float player_speed = 4.0f;

void *constructor()
{
    entity_data *data = ( entity_data * ) malloc( sizeof( entity_data ) );
    data->health = 100;
    data->armor = 0;

    return data;
}

void destructor( void *data )
{
    free( data );
}

int can_unload( void *dst, void *src )
{
    return 0;
}

void on_game_load()
{
    entity *player = add_entity( id, 0, 0 );
    load_entity( player, NULL, &can_unload );
}

void on_game_exit()
{
}

void on_update( entity *ent )
{
    vx = 0;
    vy = 0;

    if ( keystate[ SDL_SCANCODE_W ] )
    {
        vy -= 1.0f;
    }

    if ( keystate[ SDL_SCANCODE_S ] )
    {
        vy += 1.0f;
    }

    if ( keystate[ SDL_SCANCODE_A ] )
    {
        vx -= 1.0f;
    }

    if ( keystate[ SDL_SCANCODE_D ] )
    {
        vx += 1.0f;
    }

    normalize( vx, vy, &vx, &vy );

    float dx = vx * delta_t * player_speed;
    float dy = vy * delta_t * player_speed;
    int res = entity_add_pos( ent, dx, dy );
}

void on_render( entity *obj )
{
    set_render_color( 255, 0, 0, 255 );
    draw_circle_world( obj->x, obj->y, 0.5f );
}

void on_interact( entity *obj )
{
}
