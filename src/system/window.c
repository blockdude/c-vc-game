#include <vcp/vcp.h>
#include <SDL3/SDL.h>

#ifdef VCP_WINDOW_OPENGL
#include <glad/gl.h>
#endif

static struct
{
    SDL_Window *handle;
    SDL_GLContext glcontext;
    bool initialized;
    u32 flags;
    char title[VCP_MAX_STRING_LEN];
    float aspect;
    int width;
    int height;
    u32 id;
    bool keep_open;
} state = { .id = 0, .title = "Application", .width = 700, .height = 700, .aspect = 1.0f };

/*
 * =============================
 * -----------------------------
 * INIT
 * -----------------------------
 */

int window_init(void)
{
    if (state.initialized == true)
    {
        log_info("Window already initialized");
        return 0;
    }

    if (SDL_InitSubSystem(SDL_INIT_VIDEO) == false)
    {
        log_warn("Unable to initialize SDL video system: %s", SDL_GetError());
        goto cleanup;
    }

    SDL_WindowFlags sdl_window_flags = 0;

#ifdef VCP_WINDOW_OPENGL
    sdl_window_flags = SDL_WINDOW_OPENGL;
#endif

    sdl_window_flags |= (state.flags & WINDOW_RESIZABLE) ? SDL_WINDOW_RESIZABLE : 0;
    sdl_window_flags |= (state.flags & WINDOW_FULLSCREEN) ? SDL_WINDOW_FULLSCREEN : 0;
    sdl_window_flags |= (state.flags & WINDOW_HIGHDPI) ? SDL_WINDOW_HIGH_PIXEL_DENSITY : 0;
    sdl_window_flags |= (state.flags & WINDOW_RELATIVE_MOUSE) ? SDL_WINDOW_MOUSE_RELATIVE_MODE : 0;

#ifdef VCP_WINDOW_OPENGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
#endif

    state.handle = SDL_CreateWindow(state.title, state.width, state.height, sdl_window_flags);
    if (state.handle == NULL)
    {
        log_warn("Failed to initialize system. Unable to create SDL window: %s", SDL_GetError());
        goto cleanup;
    }

#ifdef VCP_WINDOW_OPENGL
    state.glcontext = SDL_GL_CreateContext(state.handle);
    if (state.glcontext == NULL)
    {
        log_warn("Failed to initialize system. Unable to create OpenGL context: %s", SDL_GetError());
        goto cleanup;
    }

    if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress))
    {
        log_warn("Failed to load opengl functions");
        goto cleanup;
    }

    SDL_GL_SetSwapInterval((state.flags & WINDOW_VSYNC) ? 1 : 0);
#endif

    state.id = SDL_GetWindowID(state.handle);
    state.initialized = true;
    state.keep_open = true;

#ifdef VCP_WINDOW_OPENGL
    log_info("Vendor: %s", glGetString(GL_VENDOR));
    log_info("Renderer: %s", glGetString(GL_RENDERER));
    log_info("GL Version: %s", glGetString(GL_VERSION));
    log_info("SL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif

    return 0;

cleanup:
#ifdef VCP_WINDOW_OPENGL
    if (state.glcontext)
        SDL_GL_DestroyContext(state.glcontext);
#endif

    if (state.handle)
        SDL_DestroyWindow(state.handle);

    state.handle = NULL;
    state.glcontext = NULL;
    return -1;
}

void window_deinit(void)
{
    if (state.initialized == false)
        return;

#ifdef VCP_WINDOW_OPENGL
    if (state.glcontext)
    {
        SDL_GL_DestroyContext(state.glcontext);
        log_info("Destroyed OpenGL context");
        state.glcontext = NULL;
    }
#endif

    if (state.handle)
    {
        SDL_DestroyWindow(state.handle);
        log_info("Destroyed SDL window");
        state.handle = NULL;
    }

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    state.initialized = false;
}

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * GRAPHICS
 * -----------------------------
 */

void window_swap_buffer(void)
{
#ifdef VCP_WINDOW_OPENGL
    SDL_GL_SwapWindow(state.handle);
#endif
}

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * GETTERS
 * -----------------------------
 */

bool window_keep_open(void)
{
    return state.keep_open;
}

void window_request_close(void)
{
    state.keep_open = false;
}

struct Extent window_size(void)
{
    struct Extent result = {
        state.width,
        state.height
    };

    return result;
}

int window_width(void)
{
    return state.width;
}

int window_height(void)
{
    return state.height;
}

float window_aspect(void)
{
    return state.aspect;
}

const char *window_title(void)
{
    return state.title;
}

u32 window_flags(void)
{
    return state.flags;
}

bool window_flag_state(u32 flag)
{
    return (state.flags & flag) == flag;
}

u32 window_id(void)
{
    return state.id;
}

void *window_handle(void)
{
    return (void *)state.handle;
}

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * SETTERS
 * -----------------------------
 */

void window_set_title(const char *title)
{
    SDL_SetWindowTitle(state.handle, title);
    snprintf(state.title, VCP_MAX_STRING_LEN, "%s", title);
}

void window_set_size(int w, int h)
{
    SDL_SetWindowSize(state.handle, w, h);
    state.width = w;
    state.height = h;
    state.aspect = (float)w / h;

#ifdef VCP_WINDOW_OPENGL
    glViewport(0, 0, w, h);
#endif
}

void window_set_flags(u32 flags, bool enabled)
{
    state.flags = enabled ?
        state.flags | flags :
        state.flags & ~flags;

    if (state.initialized == false)
        return;

    if (flags & WINDOW_RESIZABLE)
    {
        SDL_SetWindowResizable(state.handle, enabled);
    }

    if (flags & WINDOW_RELATIVE_MOUSE)
    {
        SDL_SetWindowRelativeMouseMode(state.handle, enabled);
    }

    if (flags & WINDOW_VSYNC)
    {
#ifdef VCP_WINDOW_OPENGL
        SDL_GL_SetSwapInterval(enabled ? 1 : 0);
#endif
    }

    if (flags & WINDOW_FULLSCREEN)
    {
        SDL_SetWindowFullscreen(state.handle, enabled);
    }

    if (flags & WINDOW_HIGHDPI)
    {
        log_warn("Unable to toggle WINDOW_HIGHDPI: Set flag before window initialization.");
    }
}

void window_toggle_flags(u32 flags)
{
    const u32 z = window_flags();
    const u32 x = ~z & flags;
    const u32 y = z & flags;

    window_set_flags(x, true);
    window_set_flags(y, false);
}

void window_enable_flags(u32 flags)
{
    window_set_flags(flags, true);
}

void window_disable_flags(u32 flags)
{
    window_set_flags(flags, false);
}

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * INTERNAL
 * -----------------------------
 */

void window_update_view_port(int w, int h)
{
    state.width = w;
    state.height = h;
    state.aspect = (float)w / h;

#ifdef VCP_WINDOW_OPENGL
    glViewport(0, 0, w, h);
#endif
}

/*
 * =============================
 */
