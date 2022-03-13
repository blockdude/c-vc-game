#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "kd-tree.h"
#include "sdl-game.h"

typedef struct object object;
typedef struct object_def object_def;

enum object_type
{
    PLAYER = 0,
    WALL,
    ENEMY,
    TRAP,
    DOOR,
    END,
    LAST,
    FIRST = PLAYER
};

struct object_def
{
    enum object_type type;
    int color;
    int armor;
    int dps;
};

struct object
{
    int x;
    int y;

    int hp;
    object_def *def;
};


// object storage
kd_tree *objects;
object_def *defs;
const int obj_c = 6;

// game info
float scale_x;
float scale_y;
float camera_x;
float camera_y;
int sel_def;

// window info
int window_w;
int window_h;

// viewports
SDL_Rect main_view;
SDL_Rect button_view;

// settings
const float zoom_speed = 1.3f;
const int button_view_width = 150;


void screen_to_world( int screen_x, int screen_y, float *world_x, float *world_y )
{
    *world_x = ( float ) ( screen_x / scale_x + camera_x );
    *world_y = ( float ) ( screen_y / scale_y + camera_y );
}

void world_to_screen( float world_x, float world_y, int *screen_x, int *screen_y )
{
    *screen_x = ( int ) ( ( world_x - camera_x ) * scale_x );
    *screen_y = ( int ) ( ( world_y - camera_y ) * scale_y );
}

int pt_in_rect( int x, int y, SDL_Rect *port )
{
    return ( x >= port->x && x <= port->x + port->w && y >= port->y && y <= port->y + port->h );
}

object *new_object( int x, int y, int id )
{
    object *obj = ( object * ) malloc( sizeof( object ) );
    obj->x = x;
    obj->y = y;
    obj->hp = 100;
    obj->def = &defs[ id ];
    return obj;
}

object_def *load_object_types( char *infile )
{
    defs = ( object_def * ) malloc( sizeof( object_def ) * obj_c );

    defs[ 0 ].type = PLAYER;
    defs[ 0 ].color = 0x00ff00ff;
    defs[ 0 ].armor = 0;
    defs[ 0 ].dps = 0;

    defs[ 1 ].type = WALL;
    defs[ 1 ].color = 0x6b6b6bff;
    defs[ 1 ].armor = 0;
    defs[ 1 ].dps = 0;

    defs[ 2 ].type = ENEMY;
    defs[ 2 ].color = 0xff0000ff;
    defs[ 2 ].armor = 0;
    defs[ 2 ].dps = 0;

    defs[ 3 ].type = TRAP;
    defs[ 3 ].color = 0xb266ffff;
    defs[ 3 ].armor = 0;
    defs[ 3 ].dps = 0;

    defs[ 4 ].type = DOOR;
    defs[ 4 ].color = 0x994c00ff;
    defs[ 4 ].armor = 0;
    defs[ 4 ].dps = 0;

    defs[ 5 ].type = END;
    defs[ 5 ].color = 0x0000ffff;
    defs[ 5 ].armor = 0;
    defs[ 5 ].dps = 0;

    return defs;
}

void place_object()
{
    float x, y;
    screen_to_world( mouse_x, mouse_y, &x, &y );
    x = floor( x );
    y = floor( y );
    int point[] = { x, y };
    kd_insert( objects, point, new_object( x, y, sel_def ) );
}

void remove_object()
{
    float x, y;
    screen_to_world( mouse_x, mouse_y, &x, &y );
    x = floor( x );
    y = floor( y );
    int point[] = { x, y };
    kd_remove( objects, point );
}

int render()
{
    /*
     * main view
     */

    SDL_RenderSetViewport( renderer, &main_view );

    int point[] = { floor( camera_x ), floor( camera_y ) };
    int dim[] = { ceil( main_view.w / scale_x ) + 1, ceil( main_view.h / scale_y ) + 1 };

    int length;
    void **query = kd_query_dim( objects, point, dim, &length );

    for ( int i = 0; i < length; i++ )
    {
        object *obj = query[ i ];
        SDL_FRect temp;
        temp.x = ( obj->x - camera_x ) * scale_x;
        temp.y = ( obj->y - camera_y ) * scale_y;
        temp.w = scale_x;
        temp.h = scale_y;

        char r = obj->def->color >> 24 & 0xff;
        char g = obj->def->color >> 16 & 0xff;
        char b = obj->def->color >> 8 & 0xff;
        char a = obj->def->color & 0xff;

        SDL_SetRenderDrawColor( renderer, r, g, b, a );
        SDL_RenderFillRectF( renderer, &temp );
    }

    free( query );

    /*
     * button view
     */

    SDL_RenderSetViewport( renderer, &button_view );
    
    float button_height = ( float ) window_h / obj_c;
    SDL_Rect button;

    button.x = 0;
    button.y = 0;
    button.w = button_view.w;
    button.h = button_height;

    for ( int i = 0; i < obj_c; i++ )
    {
        char r = defs[ i ].color >> 24 & 0xff;
        char g = defs[ i ].color >> 16 & 0xff;
        char b = defs[ i ].color >> 8 & 0xff;
        char a = defs[ i ].color & 0xff;

        SDL_SetRenderDrawColor( renderer, r, g, b, a );
        SDL_RenderFillRect( renderer, &button );

        if ( i == sel_def )
        {
            SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
            SDL_RenderDrawRect( renderer, &button );
        }

        button.y += button_height;
    }


    return length;
}

int handle()
{
    /*
     * general handle
     */

    switch ( event.type )
    {
        case SDL_WINDOWEVENT:

            switch ( event.window.event )
            {
                case SDL_WINDOWEVENT_RESIZED:

                    SDL_GetWindowSize( window, &window_w, &window_h );

                    main_view.x = 0;
                    main_view.y = 0;
                    main_view.w = window_w - 150;
                    main_view.h = window_h;

                    button_view.x = main_view.w;
                    button_view.y = 0;
                    button_view.w = window_w - main_view.w;
                    button_view.h = window_h;

                    break;
            }

            break;
    }

    /*
     * main view handle
     */
    
    if ( pt_in_rect( mouse_x, mouse_y, &main_view ) )
    {
        switch ( event.type )
        {
            case SDL_MOUSEWHEEL:

                /*
                 * zooming
                 */

                // before and after zoom for camera offset
                float bzx, bzy;
                float azx, azy;

                screen_to_world( window_w / 2, window_h / 2, &bzx, &bzy );

                if ( event.wheel.y > 0 ) // scroll up (zoom in)
                {
                    scale_x = ceil( scale_x * zoom_speed );
                    scale_y = ceil( scale_y * zoom_speed );
                }
                else if ( event.wheel.y < 0 ) // scroll down (zoom out)
                {
                    if ( scale_x != 1 )
                        scale_x = floor( scale_x / zoom_speed );

                    if ( scale_y != 1 )
                        scale_y = floor( scale_y / zoom_speed );
                }

                screen_to_world( window_w / 2, window_h / 2, &azx, &azy );

                camera_x += bzx - azx;
                camera_y += bzy - azy;

                break;
        }
    }

    /*
     * button view handle
     */

    else if ( pt_in_rect( mouse_x, mouse_y, &button_view ) )
    {
        switch ( event.type )
        {
            case SDL_MOUSEBUTTONDOWN:

                if ( event.button.button == SDL_BUTTON_LEFT )
                {
                    float button_height = ( float ) window_h / obj_c;
                    SDL_Rect button;

                    button.x = 0;
                    button.y = 0;
                    button.w = button_view.w;
                    button.h = button_height;

                    // check if mouse is over any button from defs
                    for ( int i = 0; i < obj_c; i++ )
                    {
                        if ( pt_in_rect( mouse_x - button_view.x, mouse_y, &button ) )
                        {
                            sel_def = i;
                            break;
                        }

                        button.y += button_height;
                    }
                }

                break;
        }
    }

    return 0;
}

int update()
{
    /*
     * main view update
     */

    if ( pt_in_rect( mouse_x, mouse_y, &main_view ) )
    {
        /*
         * panning
         */

        static int prev_mouse_x = 0;
        static int prev_mouse_y = 0;

        if ( ( mouse_state & SDL_BUTTON_MMASK ) != 0)
        {
            camera_x += ( prev_mouse_x - mouse_x ) / scale_x;
            camera_y += ( prev_mouse_y - mouse_y ) / scale_y;
        }

        prev_mouse_x = mouse_x;
        prev_mouse_y = mouse_y;

        /*
         * place / remove objects
         */

        if ( ( mouse_state & SDL_BUTTON_LMASK ) != 0 )
        {
            place_object();
        }

        if ( ( mouse_state & SDL_BUTTON_RMASK ) != 0 )
        {
            remove_object();
        }
    }

    /*
     * button view update
     */

    else if ( pt_in_rect( mouse_x, mouse_y, &button_view ) )
    {
    }

    /*
     * draw objects
     */

    SDL_RenderClear( renderer );
    int i = render();
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderPresent( renderer );

    /*
     * info
     */

    float world_x, world_y;
    screen_to_world( mouse_x, mouse_y, &world_x, &world_y );
    world_x = floor( world_x );
    world_y = floor( world_y );

    printf( "---------------------------\n" );
    printf( "fps                :%3.4f\n", fps );
    printf( "fps_avg            :%3.4f\n", fps_avg );
    printf( "objects            :%3d\n", kd_size( objects ) );
    printf( "objects_rendered   :%3d\n", i );
    printf( "mouse_screen_pos   :%3d, %3d\n", mouse_x, mouse_y );
    printf( "mouse_world_pos    :%3.0f, %3.0f\n", world_x, world_y );
    printf( "camera_pos         :%3.0f, %3.0f\n", camera_x, camera_y );
    printf( "scaling            :%3.0f, %3.0f\n", scale_x, scale_y );
    printf( "selected def       :%2d\n", sel_def );

    return 0;
}

void test_random_points()
{
    for ( int i = 0; i < 1000000; i++ )
    {
        int point[] = { rand() % 5000 - 2500, rand() % 5000 - 2500 };
        kd_insert( objects, point, new_object( point[ 0 ], point[ 1 ], 1 ) );
    }
}

int main()
{
    /*
     * pre window
     */

    window_w = 850;
    window_h = 700;

    main_view.x = 0;
    main_view.y = 0;
    main_view.w = window_w - button_view_width;
    main_view.h = window_h;

    button_view.x = main_view.w;
    button_view.y = 0;
    button_view.w = window_w - main_view.w;
    button_view.h = window_h;

    init_game( window_w, window_h, "world creation tool" );

    /*
     * post window
     */

    load_object_types( NULL );

    sel_def = 0;
    objects = new_kd_tree( 2, NULL );
    scale_x = 100;
    scale_y = 100;
    camera_x = 0;
    camera_y = 0;

    fps_cap = 60;

    SDL_SetWindowResizable( window, SDL_TRUE );

    /*
     * game
     */

    start_game();

    /*
     * clean up
     */

    close_game();
    kd_free( objects );
    free( defs );

    return 0;
}
