#ifndef CORE_GAME_UTILS
#define CORE_GAME_UTILS

/*
 * sdl window stuff
 */

extern void *window;
extern void *renderer;

extern int window_w;
extern int window_h;

extern float delta_t;
extern float fps_cur;
extern float fps_avg;
extern float fps_cap;

extern int frame;

extern char quit;
extern char pause;

extern int mouse_state;
extern const unsigned char *keystate;

/*
 * object stuff
 */

typedef struct object object;

struct object
{
    float x;
    float y;
    float w;
    float h;

    int id;

    void *data;
    void *priv;
};

enum OBJECT_FLAGS
{
    OBJECT = 1,
    ENTITY = 3
};

/*
 * world state variables
 */

extern float scale_x;
extern float scale_y;
extern float camera_x;
extern float camera_y;

/*
 * init functions
 */

void init_core                  ();
void free_core                  ();

/*
 * world query functions
 */

object **query_objects          ( float x, float y, float w, float h, int *l );
object **query_objects_radius   ( float x, float y, float r, int *l );
object *find_object             ( float x, float y );
void query_objects_func         ( float x, float y, float w, float h, void ( *func )( object * ) );
void free_object_query          ( object **query );

/*
 * object & object functions
 */

void update_object              ( object *obj );
void render_object              ( object *obj );
void interact_object            ( object *obj );

object *create_object           ( int id, float x, float y );
void delete_object              ( object *obj );

int object_add_pos              ( object *obj, float dx, float dy );
int object_set_pos              ( object *obj, float x, float y );

void load_object                ( object *obj, object *src, int ( *can_unload )( object *, object * ) );
void unload_object              ( object *obj );

void update_loaded_objects      ();

/*
 * game state
 */

//void pause_game                 ();
//void quit_game                  ();

/*
 * world
 */

void load_world                 ( char *path );
void save_world                 ( char *path );

/*
 * getters and setters
 */

void set_scale                  ( float scl );

int get_mouse_sreen             ( int *x, int *y );
int get_mouse_tile              ( int *x, int *y );
int get_mouse_world             ( float *x, float *y );

/*
 * drawing utils
 */

void screen_to_world            ( int screen_x, int screen_y, float *world_x, float *world_y );
void world_to_screen            ( float world_x, float world_y, int *screen_x, int *screen_y );
void screen_to_world_f          ( float screen_x, float screen_y, float *world_x, float *world_y );
void world_to_screen_f          ( float world_x, float world_y, float *screen_x, float *screen_y );

void set_render_color           ( char r, char g, char b, char a );

void draw_circle_screen         ( float x, float y, float r );
void draw_circle_world          ( float x, float y, float r );

void draw_rect_screen           ( float x, float y, float w, float h );
void fill_rect_screen           ( float x, float y, float w, float h );

void draw_rect_world            ( float x, float y, float w, float h );
void fill_rect_world            ( float x, float y, float w, float h );

#endif
