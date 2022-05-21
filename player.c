#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "entity.h"
#include "util.h"
#include "sprite.h"

char *name = "player";
int flags = 0;
int id;

float player_speed = 4.0f;
float player_radius = 4.0f;

float player_load_radius = 10.0f;

sprite *player_sprite[ 4 ];

int can_unload_player( void *dst, void *src )
{
    return 0;
}

void static_constructor()
{
    entity *player = create_entity( id, 0, 0 );
    load_entity( player, NULL, &can_unload_player );

    player_sprite[ 0 ] = load_sprite( renderer, "data/textures/shrimp-north.bmp", 250, 250, 3, 100 );
    player_sprite[ 1 ] = load_sprite( renderer, "data/textures/shrimp-south.bmp", 250, 250, 3, 100 );
    player_sprite[ 2 ] = load_sprite( renderer, "data/textures/shrimp-east.bmp", 250, 250, 2, 100 );
    player_sprite[ 3 ] = load_sprite( renderer, "data/textures/shrimp-east.bmp", 250, 250, 2, 100 );
    set_sprite_flip( player_sprite[ 3 ], SDL_FLIP_HORIZONTAL );
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

    /*
     * do player movement
     */

    {
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

        // do collision resolution
        float new_x = ent->x + data->vx * delta_t * player_speed;
        float new_y = ent->y + data->vy * delta_t * player_speed;

        int l;
        object **object_query = query_objects_radius( ent->x, ent->y, player_radius + 2.0f, &l );

        for ( int i = 0; i < l; i++ )
        {
            float object_x = object_query[ i ]->x;
            float object_y = object_query[ i ]->y;

            float near_x = clamp( new_x, object_x, object_x + 1.0f );
            float near_y = clamp( new_y, object_y, object_y + 1.0f );

            float raynear_x = near_x - new_x;
            float raynear_y = near_y - new_y;

            float overlap = player_radius - magnitude( raynear_x, raynear_y );

            // check for NAN
            if ( overlap != overlap ) overlap = 0;

            if ( overlap > 0 )
            {
                normalize( raynear_x, raynear_y, &raynear_x, &raynear_y );
                new_x = new_x - raynear_x * overlap;
                new_y = new_y - raynear_y * overlap;
            }
        }

        free_object_query( object_query );

        entity_set_pos( ent, new_x, new_y );
        camera_x = new_x;
        camera_y = new_y;
    }

    /*
     * do block placment
     */

    {
        int mx, my;
        int ms = get_mouse_tile( &mx, &my );

        if ( ( ms & SDL_BUTTON_LMASK ) != 0 )
        {
            create_object( 0, mx, my );
        }

        if ( ( ms & SDL_BUTTON_RMASK ) != 0 )
        {
            object *res = find_object( mx, my );
            delete_object( res );
        }
    }

    /*
     * print info
     */

    {
        float x, y;
        world_to_screen_f( ent->x, ent->y, &x, &y );

        printf( "---------------------------\n" );
        printf( "player_scrn_pos:   %7.2f, %7.2f\n", x, y );
        printf( "player_wrld_pos:   %7.2f, %7.2f\n", ent->x, ent->y );
    }
}

static int get_direction( float vx, float vy )
{
    static int direction = 0;
    if ( vx == 0 && vy == 0 ) return direction;

    if ( abs( vx ) >= abs( vy ) )
        if ( vx > 0 )
            direction = 2;
        else
            direction = 3;
    else
        if ( vy > 0 )
            direction = 1;
        else
            direction = 0;
    return direction;
}

void on_render( entity *ent )
{
    entity_data *data = ent->data;

    SDL_Rect rect = { ent->x, ent->y, player_radius * 2 * scale_x, player_radius * 2 * scale_y };
    world_to_screen( ent->x - player_radius, ent->y - player_radius, &rect.x, &rect.y );

    if ( data->vx == 0 && data->vy == 0 )
    {
        render_sprite_last_frame( renderer, player_sprite[ get_direction( data->vx, data->vy ) ], &rect );
    }
    else
    {
        render_sprite( renderer, player_sprite[ get_direction( data->vx, data->vy ) ], &rect );
    }

    set_render_color( 255, 0, 0, 255 );
    draw_circle_world( ent->x, ent->y, player_radius );
    set_render_color( 0, 0, 255, 255 );
    draw_circle_world( ent->x, ent->y, player_radius + 2.0f );
}

void on_interact( entity *ent )
{
}
