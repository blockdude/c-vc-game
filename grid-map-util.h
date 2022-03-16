#ifndef GRID_MAP_UTIL
#define GRID_MAP_UTIL

extern float scale_x;
extern float scale_y;
extern float camera_x;
extern float camera_y;

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

void screen_to_world_f( float screen_x, float screen_y, float *world_x, float *world_y )
{
    *world_x = ( float ) ( screen_x / scale_x + camera_x );
    *world_y = ( float ) ( screen_y / scale_y + camera_y );
}

void world_to_screen_f( float world_x, float world_y, float *screen_x, float *screen_y )
{
    *screen_x = ( float ) ( ( world_x - camera_x ) * scale_x );
    *screen_y = ( float ) ( ( world_y - camera_y ) * scale_y );
}

#endif
