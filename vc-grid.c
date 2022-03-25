#include "vc-grid.h"
#include "vc-util.h"

void screen_to_world( int screen_x, int screen_y, float *world_x, float *world_y )
{
    *world_x = ( float ) ( screen_x / scale_x + camera_x );
    *world_y = ( float ) ( screen_y / scale_y + camera_y );
}

void screen_to_world_f( float screen_x, float screen_y, float *world_x, float *world_y )
{
    *world_x = ( float ) ( screen_x / scale_x + camera_x );
    *world_y = ( float ) ( screen_y / scale_y + camera_y );
}

void world_to_screen( float world_x, float world_y, int *screen_x, int *screen_y )
{
    *screen_x = ( int ) ( ( world_x - camera_x ) * scale_x );
    *screen_y = ( int ) ( ( world_y - camera_y ) * scale_y );
}

void world_to_screen_f( float world_x, float world_y, float *screen_x, float *screen_y )
{
    *screen_x = ( float ) ( ( world_x - camera_x ) * scale_x );
    *screen_y = ( float ) ( ( world_y - camera_y ) * scale_y );
}

void draw_object( SDL_Renderer *renderer, vc_object *object )
{
    SDL_FRect rect_obj;
    vc_get_object_pos( object, &rect_obj.x, &rect_obj.y );
    world_to_screen_f( rect_obj.x, rect_obj.y, &rect_obj.x, &rect_obj.y );
    rect_obj.w = scale_x;
    rect_obj.h = scale_y;

    char r, g, b, a;
    int color = vc_get_object_comp( object, VC_COMP_COLOR );
    split_color( color, &r, &g, &b, &a );

    SDL_SetRenderDrawColor( renderer, r, g, b, a );
    SDL_RenderDrawRectF( renderer, &rect_obj );
}

void draw_entity( SDL_Renderer *renderer, vc_object *object )
{
    float x, y;
    vc_get_object_pos( object, &x, &y );
    world_to_screen_f( x, y, &x, &y );

    char r, g, b, a;
    int color = vc_get_object_comp( object, VC_COMP_COLOR );
    split_color( color, &r, &g, &b, &a );

    SDL_SetRenderDrawColor( renderer, r, g, b, a );
    draw_circle_f( renderer, x, y, scale_x / 2 );
}

void draw_circle_f( SDL_Renderer *renderer, float x0, float y0, float radius )
{
    float diameter = radius * 2;
    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - diameter;

    while (x >= y)
    {
        SDL_RenderDrawPoint( renderer, x0 + x, y0 + y );
        SDL_RenderDrawPoint( renderer, x0 + y, y0 + x );
        SDL_RenderDrawPoint( renderer, x0 - y, y0 + x );
        SDL_RenderDrawPoint( renderer, x0 - x, y0 + y );
        SDL_RenderDrawPoint( renderer, x0 - x, y0 - y );
        SDL_RenderDrawPoint( renderer, x0 - y, y0 - x );
        SDL_RenderDrawPoint( renderer, x0 + y, y0 - x );
        SDL_RenderDrawPoint( renderer, x0 + x, y0 - y );

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - diameter;
        }
    }
}

