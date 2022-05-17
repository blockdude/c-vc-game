#ifndef GAME_WINDOW
#define GAME_WINDOW

#include <SDL2/SDL.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Event event;

extern float delta_t;
extern float fps_cur;
extern float fps_avg;
extern float fps_cap;

extern char quit;
extern char pause;

extern int mouse_state;
extern const unsigned char *keystate;

// mouse pos
extern SDL_Point mouse_screen;
extern SDL_FPoint mouse_world;
extern SDL_Point mouse_world_floor;

extern SDL_FPoint scale;
extern SDL_FPoint camera;

// viewports
extern SDL_Rect main_view;

int init_game           (int width, int height, const char *title);
int close_game          ();
int start_game          ();

int update              ();
int handle              ();

void screen_to_world    ( int screen_x, int screen_y, float *world_x, float *world_y );
void world_to_screen    ( float world_x, float world_y, int *screen_x, int *screen_y );
void screen_to_world_f  ( float screen_x, float screen_y, float *world_x, float *world_y );
void world_to_screen_f  ( float world_x, float world_y, float *screen_x, float *screen_y );

void draw_circle_screen ( float x, float y, float r );
void draw_circle_world  ( float x, float y, float r );

void draw_rect_screen   ( float x, float y, float w, float h );
void fill_rect_screen   ( float x, float y, float w, float h );

void draw_rect_world    ( float x, float y, float w, float h );
void fill_rect_world    ( float x, float y, float w, float h );

#endif
