#ifndef GAME_WINDOW
#define GAME_WINDOW

#include <SDL2/SDL.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Event event;
extern float delta_t;
extern float fps;
extern float max_fps;
extern char quit;
extern char pause;
extern const unsigned char *keystate;

int init_game           (int width, int height, const char *title);
int close_game          ();
int start_game          ();

int update              ();
int handle              ();

#endif
