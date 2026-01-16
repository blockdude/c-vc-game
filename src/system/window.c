#include <vcp/vcp.h>
#include <SDL3/SDL.h>

#ifdef VCP_WINDOW_OPENGL
#include <glad/gl.h>
#endif

static struct
{
    bool initialized;
    u32 flags;
    char title[VCP_MAX_STRING_LEN];
    float aspect;
    int width;
    int height;
    u32 id;

    bool keep_open;
} g_win_state = { .id = 0, .title = "Application", .width = 700, .height = 700, .aspect = 1.0f };

static struct
{
    SDL_Window *handle;
    SDL_GLContext glcontext;
} g_win_ctx = { 0 };

/*
 * =============================
 * -----------------------------
 * INIT
 * -----------------------------
 */

int window_init(void)
{
    if (g_win_state.initialized == true)
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

    sdl_window_flags |= (g_win_state.flags & WINDOW_RESIZABLE) ? SDL_WINDOW_RESIZABLE : 0;
    sdl_window_flags |= (g_win_state.flags & WINDOW_FULLSCREEN) ? SDL_WINDOW_FULLSCREEN : 0;
    sdl_window_flags |= (g_win_state.flags & WINDOW_HIGHDPI) ? SDL_WINDOW_HIGH_PIXEL_DENSITY : 0;
    sdl_window_flags |= (g_win_state.flags & WINDOW_RELATIVE_MOUSE) ? SDL_WINDOW_MOUSE_RELATIVE_MODE : 0;

#ifdef VCP_WINDOW_OPENGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
#endif

    g_win_ctx.handle = SDL_CreateWindow(g_win_state.title, g_win_state.width, g_win_state.height, sdl_window_flags);
    if (g_win_ctx.handle == NULL)
    {
        log_warn("Failed to initialize system. Unable to create SDL window: %s", SDL_GetError());
        goto cleanup;
    }

#ifdef VCP_WINDOW_OPENGL
    g_win_ctx.glcontext = SDL_GL_CreateContext(g_win_ctx.handle);
    if (g_win_ctx.glcontext == NULL)
    {
        log_warn("Failed to initialize system. Unable to create OpenGL context: %s", SDL_GetError());
        goto cleanup;
    }

    if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress))
    {
        log_warn("Failed to load opengl functions");
        goto cleanup;
    }

    SDL_GL_SetSwapInterval((g_win_state.flags & WINDOW_VSYNC) ? 1 : 0);
#endif

    g_win_state.id = SDL_GetWindowID(g_win_ctx.handle);
    g_win_state.initialized = true;
    g_win_state.keep_open = true;

#ifdef VCP_WINDOW_OPENGL
    log_info("Vendor: %s", glGetString(GL_VENDOR));
    log_info("Renderer: %s", glGetString(GL_RENDERER));
    log_info("GL Version: %s", glGetString(GL_VERSION));
    log_info("SL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif

    return 0;

cleanup:
#ifdef VCP_WINDOW_OPENGL
    if (g_win_ctx.glcontext)
        SDL_GL_DestroyContext(g_win_ctx.glcontext);
#endif

    if (g_win_ctx.handle)
        SDL_DestroyWindow(g_win_ctx.handle);

    g_win_ctx.handle = NULL;
    g_win_ctx.glcontext = NULL;
    return -1;
}

void window_deinit(void)
{
    if (g_win_state.initialized == false)
        return;

#ifdef VCP_WINDOW_OPENGL
    if (g_win_ctx.glcontext)
    {
        SDL_GL_DestroyContext(g_win_ctx.glcontext);
        log_info("Destroyed OpenGL context");
        g_win_ctx.glcontext = NULL;
    }
#endif

    if (g_win_ctx.handle)
    {
        SDL_DestroyWindow(g_win_ctx.handle);
        log_info("Destroyed SDL window");
        g_win_ctx.handle = NULL;
    }

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    g_win_state.initialized = false;
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
    SDL_GL_SwapWindow(g_win_ctx.handle);
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
    return g_win_state.keep_open;
}

void window_request_close(void)
{
    g_win_state.keep_open = false;
}

struct Extent window_size(void)
{
    struct Extent result = {
        g_win_state.width,
        g_win_state.height
    };

    return result;
}

int window_width(void)
{
    return g_win_state.width;
}

int window_height(void)
{
    return g_win_state.height;
}

float window_aspect(void)
{
    return g_win_state.aspect;
}

const char *window_title(void)
{
    return g_win_state.title;
}

u32 window_flags(void)
{
    return g_win_state.flags;
}

bool window_flag_state(u32 flag)
{
    return (g_win_state.flags & flag) == flag;
}

u32 window_id(void)
{
    return g_win_state.id;
}

void *window_handle(void)
{
    return (void *)g_win_ctx.handle;
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
    SDL_SetWindowTitle(g_win_ctx.handle, title);
    snprintf(g_win_state.title, VCP_MAX_STRING_LEN, "%s", title);
}

void window_set_size(int w, int h)
{
    SDL_SetWindowSize(g_win_ctx.handle, w, h);
    g_win_state.width = w;
    g_win_state.height = h;
    g_win_state.aspect = (float)w / h;

#ifdef VCP_WINDOW_OPENGL
    glViewport(0, 0, w, h);
#endif
}

void window_set_flags(u32 flags, bool state)
{
    g_win_state.flags = state ?
        g_win_state.flags | flags :
        g_win_state.flags & ~flags;

    if (g_win_state.initialized == false)
        return;

    if (flags & WINDOW_RESIZABLE)
    {
        SDL_SetWindowResizable(g_win_ctx.handle, state);
    }

    if (flags & WINDOW_RELATIVE_MOUSE)
    {
        SDL_WarpMouseInWindow(g_win_ctx.handle, g_win_state.width / 2.0f, g_win_state.height / 2.0f);
        SDL_SetWindowRelativeMouseMode(g_win_ctx.handle, state);
    }

    if (flags & WINDOW_VSYNC)
    {
#ifdef VCP_WINDOW_OPENGL
        SDL_GL_SetSwapInterval(state ? 1 : 0);
#endif
    }

    if (flags & WINDOW_FULLSCREEN)
    {
        SDL_SetWindowFullscreen(g_win_ctx.handle, state);
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
    g_win_state.width = w;
    g_win_state.height = h;
    g_win_state.aspect = (float)w / h;

#ifdef VCP_WINDOW_OPENGL
    glViewport(0, 0, w, h);
#endif
}

/*
 * =============================
 */
