#ifndef VCP_LIB_H
#define VCP_LIB_H

#include <cstdio>
#include <cstddef>
#include <cstdint>

#include <cmath>

#define VCP_MAX_STRING_LEN 128

// =============================
// -----------------------------
// VERSION (git-derived, generated at build time)
// -----------------------------

extern const int VCP_VERSION_MAJOR;
extern const int VCP_VERSION_MINOR;
extern const int VCP_VERSION_PATCH;
extern const int VCP_VERSION_BUILD;
extern const int VCP_VERSION_BUILD_ABSOLUTE;
extern const bool VCP_VERSION_DIRTY;
extern const char *const VCP_VERSION_COMMIT;
extern const char *const VCP_VERSION_COMMIT_FULL;
extern const char *const VCP_VERSION_BRANCH;
extern const char *const VCP_VERSION_TAG;
extern const char *const VCP_VERSION_TIMESTAMP;
extern const char *const VCP_VERSION_STRING;
extern const long long VCP_VERSION_EPOCH;

// =============================
// -----------------------------
// TYPES
// -----------------------------

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

#define _EXTENT_TEMPLATE(T) { T w, h; }
#define _LINE_TEMPLATE(T) { T x0, y0; T x1, y1; }
#define _POINT_TEMPLATE(T) { T x, y; }
#define _CIRCLE_TEMPLATE(T) { T x, y; T r; }
#define _TRIANGLE_TEMPLATE(T) { T x0, y0; T x1, y1; T x2, y2; }
#define _RECTANGLE_TEMPLATE(T) { T x, y; T w, h; }
#define _COLOR_TEMPLATE(T) { T r, g, b, a; }
#define _VEC2_TEMPLATE(T)  { T x, y; }
#define _VEC3_TEMPLATE(T)  { T x, y, z; }
#define _VEC4_TEMPLATE(T)  { T x, y, z, w; }
#define _QUAT_TEMPLATE(T)  { T x, y, z, w; }
#define _FMAT4_TEMPLATE(T) { T m[16];}
#define _MAT4_TEMPLATE(T)  { T m00, m01, m02, m03; \
                             T m10, m11, m12, m13; \
                             T m20, m21, m22, m23; \
                             T m30, m31, m32, m33; }

/*
 * Memory layout of matrix is row major.
 *     ex: row[ 0 ] = { m00, m01, m02, m03 }
 *
 * Samantical layout is column major.
 *     ex: row[ 0 ] = { m00, m10, m20, m30 }
 *
 * When we convert it to an array it will look like:
 *	   { m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33 }
 */

struct Vec2 _VEC2_TEMPLATE(float);
struct Vec2I _VEC2_TEMPLATE(int);
struct Vec2I32 _VEC2_TEMPLATE(i32);
struct Vec2I64 _VEC2_TEMPLATE(i64);
struct Vec2F32 _VEC2_TEMPLATE(f32);
struct Vec2F64 _VEC2_TEMPLATE(f64);

struct Vec3 _VEC3_TEMPLATE(float);
struct Vec3I _VEC3_TEMPLATE(int);
struct Vec3I32 _VEC3_TEMPLATE(i32);
struct Vec3I64 _VEC3_TEMPLATE(i64);
struct Vec3F32 _VEC3_TEMPLATE(f32);
struct Vec3F64 _VEC3_TEMPLATE(f64);

struct Vec4 _VEC4_TEMPLATE(float);
struct Vec4I _VEC4_TEMPLATE(int);
struct Vec4I32 _VEC4_TEMPLATE(i32);
struct Vec4I64 _VEC4_TEMPLATE(i64);
struct Vec4F32 _VEC4_TEMPLATE(f32);
struct Vec4F64 _VEC4_TEMPLATE(f64);

struct Quat _QUAT_TEMPLATE(float);
struct QuatI _QUAT_TEMPLATE(int);
struct QuatI32 _QUAT_TEMPLATE(i32);
struct QuatI64 _QUAT_TEMPLATE(i64);
struct QuatF32 _QUAT_TEMPLATE(f32);
struct QuatF64 _QUAT_TEMPLATE(f64);

struct Mat4 _MAT4_TEMPLATE(float);
struct Mat4I _MAT4_TEMPLATE(int);
struct Mat4I32 _MAT4_TEMPLATE(i32);
struct Mat4I64 _MAT4_TEMPLATE(i64);
struct Mat4F32 _MAT4_TEMPLATE(f32);
struct Mat4F64 _MAT4_TEMPLATE(f64);

struct FMat4 _FMAT4_TEMPLATE(float);
struct FMat4I _FMAT4_TEMPLATE(int);
struct FMat4I32 _FMAT4_TEMPLATE(i32);
struct FMat4I64 _FMAT4_TEMPLATE(i64);
struct FMat4F32 _FMAT4_TEMPLATE(f32);
struct FMat4F64 _FMAT4_TEMPLATE(f64);

struct Line _LINE_TEMPLATE(float);
struct LineI32 _LINE_TEMPLATE(i32);
struct LineI64 _LINE_TEMPLATE(i64);
struct LineF32 _LINE_TEMPLATE(f32);
struct LineF64 _LINE_TEMPLATE(f64);

struct Circle _CIRCLE_TEMPLATE(float);
struct CircleI32 _CIRCLE_TEMPLATE(i32);
struct CircleI64 _CIRCLE_TEMPLATE(i64);
struct CircleF32 _CIRCLE_TEMPLATE(f32);
struct CircleF64 _CIRCLE_TEMPLATE(f64);

struct Triangle _TRIANGLE_TEMPLATE(float);
struct TriangleI32 _TRIANGLE_TEMPLATE(i32);
struct TriangleI64 _TRIANGLE_TEMPLATE(i64);
struct TriangleF32 _TRIANGLE_TEMPLATE(f32);
struct TriangleF64 _TRIANGLE_TEMPLATE(f64);

struct Rectangle _RECTANGLE_TEMPLATE(float);
struct RectangleI32 _RECTANGLE_TEMPLATE(i32);
struct RectangleI64 _RECTANGLE_TEMPLATE(i64);
struct RectangleF32 _RECTANGLE_TEMPLATE(f32);
struct RectangleF64 _RECTANGLE_TEMPLATE(f64);

struct Color _COLOR_TEMPLATE(float);
struct ColorU8 _COLOR_TEMPLATE(u8);
struct ColorU16 _COLOR_TEMPLATE(u16);
struct ColorF32 _COLOR_TEMPLATE(f32);
struct ColorF64 _COLOR_TEMPLATE(f64);

#undef _EXTENT_TEMPLATE
#undef _LINE_TEMPLATE
#undef _POINT_TEMPLATE
#undef _CIRCLE_TEMPLATE
#undef _TRIANGLE_TEMPLATE
#undef _RECTANGLE_TEMPLATE
#undef _COLOR_TEMPLATE
#undef _VEC2_TEMPLATE
#undef _VEC3_TEMPLATE
#undef _VEC4_TEMPLATE
#undef _QUAT_TEMPLATE
#undef _FMAT4_TEMPLATE
#undef _MAT4_TEMPLATE

// =============================



// =============================
// -----------------------------
// MATH
// -----------------------------

#include "_internal/linear_algebra.h"

#if defined(WIN32) || defined(_WIN32)

#undef MIN
#undef MAX
#undef min
#undef max

#endif

#define BITFLAG(v) (1 << (v))
#define HASFLAG(f, v) (((f) & (v)) == (v))
#define ANYFLAG(f, v) (((f) & (v)) >  (0))

#define EULER   2.71828182845904523536028747135266249
#define PI_2    1.57079632679489661923132169163975144
#define PI      3.14159265358979323846264338327950288
#define TAU     6.28318530717958647692528676655900576
#define EPSILON 0.0001

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define SIGN(v) (((v) > 0) - ((v) < 0))

#define CLAMP(v, mn, mx) MAX(mn, MIN(mx, v))

#define DEGTORAD(x) ((x) * (PI / 180.0))
#define RADTODEG(x) ((x) * (180.0 / PI))

#define LERP(a, b, t) ((a) + (t) * ((b) - (a)))
#define NORMALIZE(x, min, max) (((x) - (min)) / ((max) - (min)))

// =============================



// =============================
// CLOCK
// -----------------------------

struct FrameClock
{
    f64 delta;
    f64 interval;
    f64 last;
};

struct FixedClock
{
    f64 accumulator;
    f64 interval;
};

struct ClockConfig
{
    f64 rise_alpha;
    f64 fall_alpha;
    f64 interval;
};

struct ClockStats
{
    u64 count;
    f64 rate;
    u64 raw_rate;
    f64 elapsed;
    f64 instant_rate;
    f64 running_average_rate;
    f64 moving_average_rate;
    f64 timer;
    u64 timer_count;
};

struct FrameClock frame_clock_create(f64 rate);
void frame_clock_start(struct FrameClock *fc);
void frame_clock_wait(struct FrameClock *fc);
void frame_clock_tick(struct FrameClock *fc);
void frame_clock_set_rate(struct FrameClock *fc, f64 rate);

struct FixedClock fixed_clock_create(f64 rate);
void fixed_clock_set_rate(struct FixedClock *sc, f64 rate);
void fixed_clock_accumulate(struct FixedClock *sc, f64 delta);
bool fixed_clock_consume(struct FixedClock *sc);
f64 fixed_clock_alpha(struct FixedClock *sc);

struct ClockConfig clock_config_default(void);
struct ClockConfig clock_config_create(f64 delta, f64 time_constant);
void clock_config_set_alpha(struct ClockConfig *c, f64 alpha);
void clock_config_set_interval(struct ClockConfig *c, f64 interval);
void clock_config_set_rise_alpha(struct ClockConfig *c, f64 rise_alpha);
void clock_config_set_fall_alpha(struct ClockConfig *c, f64 fall_alpha);

struct ClockStats clock_stats_create(void);
void clock_stats_reset(struct ClockStats *s);
void clock_stats_sample(struct ClockStats *s, struct ClockConfig c, f64 delta, u64 ticks);

// =============================



// =============================
// -----------------------------
// LOGGING
// -----------------------------

struct LogEvent
{
    va_list ap;
    const char *fmt;
    const char *file;
    struct tm *time;
    void *udata;
    int line;
    int level;
};

typedef void (*LogCallbackFn)(struct LogEvent *ev);
typedef void (*LogLockFn)(bool lock, void *udata);

enum LogLevel
{
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL
};

#define log_trace(...) log_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...) log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)  log_log(LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...)  log_log(LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) log_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...) log_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

const char *log_level_string(int level);
void log_set_lock(LogLockFn fn, void *udata);
void log_set_level(int level);
void log_set_quiet(bool enable);
int log_add_callback(LogCallbackFn fn, void *udata, int level);
int log_add_fp(FILE *fp, int level);
void log_log(int level, const char *file, int line, const char *fmt, ...);

// =============================



// =============================
// -----------------------------
// MAIN INTERFACE FOR INITIALIZATION
// -----------------------------

enum PlatformFlag
{
    PLATFORM_WINDOW = 0x01,
    PLATFORM_INPUT = 0x02,
    PLATFORM_AUDIO = 0x04,
    PLATFORM_TIMER = 0x08,
    PLATFORM_NETWORK = 0x10 // TODO?
};

int platform_init(u32 flags);
void platform_deinit(void);

// =============================



// =============================
// -----------------------------
// TIMER
// -----------------------------

#define TIME_TICKS_PER_S  1000000000
#define TIME_TICKS_PER_MS 1000000
#define TIME_TICKS_PER_US 1000
#define TIME_TICKS_PER_NS 1

int time_init(void);
void time_deinit(void);

u64 time_now(void);
f64 time_now_s(void);
f64 time_now_ms(void);
f64 time_now_us(void);
f64 time_now_ns(void);

void time_wait(u64 ticks);
void time_wait_s(f64 s);
void time_wait_ms(f64 ms);
void time_wait_us(f64 us);
void time_wait_ns(f64 ns);

u64 time_stot(f64 s);
u64 time_mstot(f64 ms);
u64 time_ustot(f64 us);
u64 time_nstot(f64 ns);

f64 time_ttos(u64 ticks);
f64 time_ttoms(u64 ticks);
f64 time_ttous(u64 ticks);
f64 time_ttons(u64 ticks);

// =============================



// =============================
// -----------------------------
// WINDOW
// -----------------------------

enum WindowFlag
{
    WINDOW_RELATIVE_MOUSE = 0x01,
    WINDOW_VSYNC = 0x02,
    WINDOW_FULLSCREEN = 0x04,
    WINDOW_RESIZABLE = 0x08,
    WINDOW_HIGHDPI = 0x10
};

int window_init(void);
void window_deinit(void);
void window_swap_buffer(void);
bool window_keep_open(void);
void window_request_close(void);
struct Vec2I window_size(void);
int window_width(void);
int window_height(void);
float window_aspect(void);
const char *window_title(void);
u32 window_flags(void);
bool window_flag_state(u32 flag);
u32 window_id(void);
void *window_handle(void);
void window_set_size(int w, int h);
void window_set_title(const char *title);
void window_set_flags(u32 flags, bool state);
void window_toggle_flags(u32 flags);
void window_enable_flags(u32 flags);
void window_disable_flags(u32 flags);

// =============================



// =============================
// -----------------------------
// INPUT
// -----------------------------

enum InputKey
{
    K_FIRST = 0,

    K_NONE = 0,

    K_A = 4,
    K_B = 5,
    K_C = 6,
    K_D = 7,
    K_E = 8,
    K_F = 9,
    K_G = 10,
    K_H = 11,
    K_I = 12,
    K_J = 13,
    K_K = 14,
    K_L = 15,
    K_M = 16,
    K_N = 17,
    K_O = 18,
    K_P = 19,
    K_Q = 20,
    K_R = 21,
    K_S = 22,
    K_T = 23,
    K_U = 24,
    K_V = 25,
    K_W = 26,
    K_X = 27,
    K_Y = 28,
    K_Z = 29,

    K_0 = 30,
    K_1 = 31,
    K_2 = 32,
    K_3 = 33,
    K_4 = 34,
    K_5 = 35,
    K_6 = 36,
    K_7 = 37,
    K_8 = 38,
    K_9 = 39,

    K_RETURN = 40,
    K_ESCAPE = 41,
    K_BACKSPACE = 42,
    K_TAB = 43,
    K_SPACE = 44,

    K_MINUS = 45,
    K_EQUAL = 46,
    K_LBRACKET = 47,
    K_RBRACKET = 48,
    K_BACKSLASH = 49,

    K_RIGHT = 79,
    K_LEFT = 80,
    K_DOWN = 81,
    K_UP = 82,

    K_LCTRL = 224,
    K_LSHIFT = 225,
    K_LALT = 226,
    K_LMETA = 227,

    K_RCTRL = 228,
    K_RSHIFT = 229,
    K_RALT = 230,
    K_RMETA = 231,

    K_COUNT,
    K_LAST = K_RMETA
};

enum InputButton
{
    B_FIRST = 0,

    B_NONE = 0,

    B_LEFT = 1,
    B_RIGHT = 2,
    B_MIDDLE = 3,
    B_FORWARD = 4,
    B_BACK = 5,

    B_COUNT,
    B_LAST = B_COUNT - 1
};

struct InputState
{
    bool down : 1;
    bool pressed : 1;
    bool released : 1;
    bool repeated : 1;
};

int input_init(void);
void input_deinit(void);
void input_poll_events(bool capture_text);
bool input_quit_event(void);
int input_text_history_size(void);
char input_text_history(int i);
int input_text_history_buffer(char *buffer, size_t buffer_size);
int input_key_history_size(void);
int input_button_history_size(void);
enum InputKey input_key_history(int i);
enum InputButton input_button_history(int i);
#define input_last_key_pressed() input_key_history(input_key_history_size() - 1)
#define input_last_button_pressed() input_button_history(input_button_history_size() - 1)
int input_key_history_buffer(enum InputKey *buffer, size_t buffer_size);
int input_button_history_buffer(enum InputButton *buffer, size_t buffer_size);
struct InputState input_key_state(enum InputKey key);
struct InputState input_button_state(enum InputButton btn);
void input_warp_mouse(float x, float y); // moves mouse to position in window
void input_warp_mouse_global(float x, float y);
bool input_mouse_moved(void);
struct Vec2 input_mouse_position(void);
struct Vec2 input_mouse_global_position(void);
struct Vec2 input_mouse_motion_position(void); // position from last mouse motion
struct Vec2 input_mouse_delta(void);
struct Vec2 input_mouse_scroll(void);

// =============================



// =============================
// -----------------------------
// AUDIO (todo)
// -----------------------------

int audio_init(void);
void audio_deinit(void);

// =============================

#endif /* VCP_LIB_H */