#ifndef VCP_LIB_H
#define VCP_LIB_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <glad/gl.h>

#define VCP_MAX_STRING_LEN 128
#define VCP_VERSION_MAJOR 0
#define VCP_VERSION_MINOR 0
#define VCP_VERSION_PATCH 0
#define VCP_VERSION_PACKAGE 0
#define VCP_VERSION "0.0.0.0"

#ifdef __cplusplus
extern "C" {
#endif

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

struct Extent       _EXTENT_TEMPLATE(int);
struct ExtentF      _EXTENT_TEMPLATE(float);
struct ExtentI32    _EXTENT_TEMPLATE(i32);
struct ExtentI64    _EXTENT_TEMPLATE(i64);
struct ExtentF32    _EXTENT_TEMPLATE(f32);
struct ExtentF64    _EXTENT_TEMPLATE(f64);

struct Line         _LINE_TEMPLATE(float);
struct LineI32      _LINE_TEMPLATE(i32);
struct LineI64      _LINE_TEMPLATE(i64);
struct LineF32      _LINE_TEMPLATE(f32);
struct LineF64      _LINE_TEMPLATE(f64);

struct Point        _POINT_TEMPLATE(float);
struct PointI32     _POINT_TEMPLATE(i32);
struct PointI64     _POINT_TEMPLATE(i64);
struct PointF32     _POINT_TEMPLATE(f32);
struct PointF64     _POINT_TEMPLATE(f64);

struct Circle       _CIRCLE_TEMPLATE(float);
struct CircleI32    _CIRCLE_TEMPLATE(i32);
struct CircleI64    _CIRCLE_TEMPLATE(i64);
struct CircleF32    _CIRCLE_TEMPLATE(f32);
struct CircleF64    _CIRCLE_TEMPLATE(f64);

struct Triangle     _TRIANGLE_TEMPLATE(float);
struct TriangleI32  _TRIANGLE_TEMPLATE(i32);
struct TriangleI64  _TRIANGLE_TEMPLATE(i64);
struct TriangleF32  _TRIANGLE_TEMPLATE(f32);
struct TriangleF64  _TRIANGLE_TEMPLATE(f64);

struct Rectangle    _RECTANGLE_TEMPLATE(float);
struct RectangleI32 _RECTANGLE_TEMPLATE(i32);
struct RectangleI64 _RECTANGLE_TEMPLATE(i64);
struct RectangleF32 _RECTANGLE_TEMPLATE(f32);
struct RectangleF64 _RECTANGLE_TEMPLATE(f64);

struct Color     _COLOR_TEMPLATE(u8);
struct ColorF    _COLOR_TEMPLATE(float);
struct ColorU8   _COLOR_TEMPLATE(u8);
struct ColorU16  _COLOR_TEMPLATE(u16);
struct ColorF32  _COLOR_TEMPLATE(f32);
struct ColorF64  _COLOR_TEMPLATE(f64);

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
struct Vec3 _VEC3_TEMPLATE(float);
struct Vec4 _VEC4_TEMPLATE(float);
struct Quat _QUAT_TEMPLATE(float);
struct Mat4 _MAT4_TEMPLATE(float);
struct FMat4 _FMAT4_TEMPLATE(float);

struct Vec2I _VEC2_TEMPLATE(int);
struct Vec3I _VEC3_TEMPLATE(int);
struct Vec4I _VEC4_TEMPLATE(int);
struct QuatI _QUAT_TEMPLATE(int);
struct Mat4I _MAT4_TEMPLATE(int);
struct FMat4I _FMAT4_TEMPLATE(int);

struct Vec2I32 _VEC2_TEMPLATE(i32);
struct Vec3I32 _VEC3_TEMPLATE(i32);
struct Vec4I32 _VEC4_TEMPLATE(i32);
struct QuatI32 _QUAT_TEMPLATE(i32);
struct Mat4I32 _MAT4_TEMPLATE(i32);
struct FMat4I32 _FMAT4_TEMPLATE(i32);

struct Vec2I64 _VEC2_TEMPLATE(i64);
struct Vec3I64 _VEC3_TEMPLATE(i64);
struct Vec4I64 _VEC4_TEMPLATE(i64);
struct QuatI64 _QUAT_TEMPLATE(i64);
struct Mat4I64 _MAT4_TEMPLATE(i64);
struct FMat4I64 _FMAT4_TEMPLATE(i64);

struct Vec2F32 _VEC2_TEMPLATE(f32);
struct Vec3F32 _VEC3_TEMPLATE(f32);
struct Vec4F32 _VEC4_TEMPLATE(f32);
struct QuatF32 _QUAT_TEMPLATE(f32);
struct Mat4F32 _MAT4_TEMPLATE(f32);
struct FMat4F32 _FMAT4_TEMPLATE(f32);

struct Vec2F64 _VEC2_TEMPLATE(f64);
struct Vec3F64 _VEC3_TEMPLATE(f64);
struct Vec4F64 _VEC4_TEMPLATE(f64);
struct QuatF64 _QUAT_TEMPLATE(f64);
struct Mat4F64 _MAT4_TEMPLATE(f64);
struct FMat4F64 _FMAT4_TEMPLATE(f64);

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
// COLORS
// -----------------------------

static const struct Color COLOR_LIGHTGRAY = { 200, 200, 200, 255 };
static const struct Color COLOR_GRAY = { 130, 130, 130, 255 };
static const struct Color COLOR_DARKGRAY = { 80, 80, 80, 255 };
static const struct Color COLOR_YELLOW = { 253, 249, 0, 255 };
static const struct Color COLOR_GOLD = { 255, 203, 0, 255 };
static const struct Color COLOR_ORANGE = { 255, 161, 0, 255 };
static const struct Color COLOR_PINK = { 255, 109, 194, 255 };
static const struct Color COLOR_RED = { 230, 41, 55, 255 };
static const struct Color COLOR_MAROON = { 190, 33, 55, 255 };
static const struct Color COLOR_GREEN = { 0, 228, 48, 255 };
static const struct Color COLOR_LIME = { 0, 158, 47, 255 };
static const struct Color COLOR_DARKGREEN = { 0, 117, 44, 255 };
static const struct Color COLOR_SKYBLUE = { 102, 191, 255, 255 };
static const struct Color COLOR_BLUE = { 0, 121, 241, 255 };
static const struct Color COLOR_DARKBLUE = { 0, 82, 172, 255 };
static const struct Color COLOR_PURPLE = { 200, 122, 255, 255 };
static const struct Color COLOR_VIOLET = { 135, 60, 190, 255 };
static const struct Color COLOR_DARKPURPLE = { 112, 31, 126, 255 };
static const struct Color COLOR_BEIGE = { 211, 176, 131, 255 };
static const struct Color COLOR_BROWN = { 127, 106, 79, 255 };
static const struct Color COLOR_DARKBROWN = { 76, 63, 47, 255 };
static const struct Color COLOR_WHITE = { 255, 255, 255, 255 };
static const struct Color COLOR_BLACK = { 0, 0, 0, 255 };
static const struct Color COLOR_BLANK = { 0, 0, 0, 0 };
static const struct Color COLOR_MAGENTA = { 255, 0, 255, 255 };

// =============================



// =============================
// -----------------------------
// MATH
// -----------------------------

#include "_internal/linear_algebra.h"

#ifdef WIN32

#undef MIN
#undef MAX
#undef min
#undef max

#endif

#define BITFLAG(v) (1 << (v))
#define HASFLAG(f, v) (((f) & (v)) == (v))
#define ANYFLAG(f, v) (((f) & (v)) >  (0))
//#define BIT_SET(v, b) ((value) |=  (1L << (bit)))
//#define BIT_CLR(v, b) ((value) &= ~(1L << (bit)))
//#define BIT_CHK(b, reg) ((reg >> (bit)) & 1)
//#define BIT_LSB(reg) ((reg)&1)

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

#define _MATH_FUNC_TEMPLATE_INT_DIVRND(T, _name) \
static inline T _name##_divrnd(T n, T d) { return ((n < 0) == (d < 0)) ? ((n + d / 2) / d) : ((n - d / 2) / d); }

_MATH_FUNC_TEMPLATE_INT_DIVRND(int, int)
_MATH_FUNC_TEMPLATE_INT_DIVRND(i32, int32)
_MATH_FUNC_TEMPLATE_INT_DIVRND(i64, int64)

#define _MATH_FUNC_TEMPLATE_INT_DIVFLR(T, _name) \
static inline T _name##_divflr(T n, T d) { return (n / d) - (n < 0); }

_MATH_FUNC_TEMPLATE_INT_DIVFLR(int, int)
_MATH_FUNC_TEMPLATE_INT_DIVFLR(i32, int32)
_MATH_FUNC_TEMPLATE_INT_DIVFLR(i64, int64)

#define _MATH_FUNC_TEMPLATE_FLOAT_EQUALS(T, _name, _abs_fn, _max_fn) \
static inline int _name##_equals(T a, T b, T epsilon) { return (_abs_fn(a - b)) <= (epsilon * _max_fn(1.0f, _max_fn(_abs_fn(a), _abs_fn(b)))); }

_MATH_FUNC_TEMPLATE_FLOAT_EQUALS(float, float, fabsf, fmaxf)
_MATH_FUNC_TEMPLATE_FLOAT_EQUALS(f32, float32, fabsf, fmaxf)
_MATH_FUNC_TEMPLATE_FLOAT_EQUALS(f64, float64, fabs, fmax)

static inline u32 rgba8888_to_uint32(u8 r, u8 g, u8 b, u8 a)
{
    u32 result = 0;
    result = (result | r) << 24;
    result = (result | g) << 16;
    result = (result | b) << 8;
    result = (result | a) << 0;
    return result;
}

static inline struct ColorF colorf_mix(struct ColorF a, struct ColorF b, float ratio)
{
    struct ColorF result;
    result.r = a.r * ratio + b.r * (1.0f - ratio);
    result.g = a.g * ratio + b.g * (1.0f - ratio);
    result.b = a.b * ratio + b.b * (1.0f - ratio);
    result.a = a.a * ratio + b.a * (1.0f - ratio);
    return result;
}

static inline struct ColorF colorf_blend(struct ColorF a, struct ColorF b)
{
    struct ColorF result;
    result.r = a.r * b.r;
    result.g = a.g * b.g;
    result.b = a.b * b.b;
    result.a = a.a * b.a;
    return result;
}

// =============================



// =============================
// -----------------------------
// TYPE CASTS
// -----------------------------

#define _VEC2_FUNC_TEMPLATE_CAST(T, name) \
static inline struct Vec2    name##_to_vec2   (T a) { const struct Vec2    b = { (float)a.x, (float)a.y }; return b; } \
static inline struct Vec2I   name##_to_vec2i  (T a) { const struct Vec2I   b = {   (int)a.x,   (int)a.y }; return b; } \
static inline struct Vec2I32 name##_to_vec2i32(T a) { const struct Vec2I32 b = {   (i32)a.x,   (i32)a.y }; return b; } \
static inline struct Vec2I64 name##_to_vec2i64(T a) { const struct Vec2I64 b = {   (i64)a.x,   (i64)a.y }; return b; } \
static inline struct Vec2F32 name##_to_vec2f32(T a) { const struct Vec2F32 b = {   (f32)a.x,   (f32)a.y }; return b; } \
static inline struct Vec2F64 name##_to_vec2f64(T a) { const struct Vec2F64 b = {   (f64)a.x,   (f64)a.y }; return b; }

_VEC2_FUNC_TEMPLATE_CAST(struct Vec2,    vec2)
_VEC2_FUNC_TEMPLATE_CAST(struct Vec2I,   vec2i)
_VEC2_FUNC_TEMPLATE_CAST(struct Vec2I32, vec2i32)
_VEC2_FUNC_TEMPLATE_CAST(struct Vec2I64, vec2i64)
_VEC2_FUNC_TEMPLATE_CAST(struct Vec2F32, vec2f32)
_VEC2_FUNC_TEMPLATE_CAST(struct Vec2F64, vec2f64)

#define _VEC3_FUNC_TEMPLATE_CAST(T, name) \
static inline struct Vec3    name##_to_vec3   (T a) { const struct Vec3    b = { (float)a.x, (float)a.y, (float)a.z }; return b; } \
static inline struct Vec3I   name##_to_vec3i  (T a) { const struct Vec3I   b = {   (int)a.x,   (int)a.y,   (int)a.z }; return b; } \
static inline struct Vec3I32 name##_to_vec3i32(T a) { const struct Vec3I32 b = {   (i32)a.x,   (i32)a.y,   (i32)a.z }; return b; } \
static inline struct Vec3I64 name##_to_vec3i64(T a) { const struct Vec3I64 b = {   (i64)a.x,   (i64)a.y,   (i64)a.z }; return b; } \
static inline struct Vec3F32 name##_to_vec3f32(T a) { const struct Vec3F32 b = {   (f32)a.x,   (f32)a.y,   (f32)a.z }; return b; } \
static inline struct Vec3F64 name##_to_vec3f64(T a) { const struct Vec3F64 b = {   (f64)a.x,   (f64)a.y,   (f64)a.z }; return b; }

_VEC3_FUNC_TEMPLATE_CAST(struct Vec3,    vec3)
_VEC3_FUNC_TEMPLATE_CAST(struct Vec3I,   vec3i)
_VEC3_FUNC_TEMPLATE_CAST(struct Vec3I32, vec3i32)
_VEC3_FUNC_TEMPLATE_CAST(struct Vec3I64, vec3i64)
_VEC3_FUNC_TEMPLATE_CAST(struct Vec3F32, vec3f32)
_VEC3_FUNC_TEMPLATE_CAST(struct Vec3F64, vec3f64)

#define _VEC4_FUNC_TEMPLATE_CAST(T, name) \
static inline struct Vec4    name##_to_vec4   (T a) { const struct Vec4    b = { (float)a.x, (float)a.y, (float)a.z, (float)a.w }; return b; } \
static inline struct Vec4I   name##_to_vec4i  (T a) { const struct Vec4I   b = {   (int)a.x,   (int)a.y,   (int)a.z,   (int)a.w }; return b; } \
static inline struct Vec4I32 name##_to_vec4i32(T a) { const struct Vec4I32 b = {   (i32)a.x,   (i32)a.y,   (i32)a.z,   (i32)a.w }; return b; } \
static inline struct Vec4I64 name##_to_vec4i64(T a) { const struct Vec4I64 b = {   (i64)a.x,   (i64)a.y,   (i64)a.z,   (i64)a.w }; return b; } \
static inline struct Vec4F32 name##_to_vec4f32(T a) { const struct Vec4F32 b = {   (f32)a.x,   (f32)a.y,   (f32)a.z,   (f32)a.w }; return b; } \
static inline struct Vec4F64 name##_to_vec4f64(T a) { const struct Vec4F64 b = {   (f64)a.x,   (f64)a.y,   (f64)a.z,   (f64)a.w }; return b; }

_VEC4_FUNC_TEMPLATE_CAST(struct Vec4,    vec4)
_VEC4_FUNC_TEMPLATE_CAST(struct Vec4I,   vec4i)
_VEC4_FUNC_TEMPLATE_CAST(struct Vec4I32, vec4i32)
_VEC4_FUNC_TEMPLATE_CAST(struct Vec4I64, vec4i64)
_VEC4_FUNC_TEMPLATE_CAST(struct Vec4F32, vec4f32)
_VEC4_FUNC_TEMPLATE_CAST(struct Vec4F64, vec4f64)

#define _QUAT_FUNC_TEMPLATE_CAST(T, name) \
static inline struct Quat    name##_to_quat   (T a) { const struct Quat    b = { (float)a.x, (float)a.y, (float)a.z, (float)a.w }; return b; } \
static inline struct QuatI   name##_to_quati  (T a) { const struct QuatI   b = {   (int)a.x,   (int)a.y,   (int)a.z,   (int)a.w }; return b; } \
static inline struct QuatI32 name##_to_quati32(T a) { const struct QuatI32 b = {   (i32)a.x,   (i32)a.y,   (i32)a.z,   (i32)a.w }; return b; } \
static inline struct QuatI64 name##_to_quati64(T a) { const struct QuatI64 b = {   (i64)a.x,   (i64)a.y,   (i64)a.z,   (i64)a.w }; return b; } \
static inline struct QuatF32 name##_to_quatf32(T a) { const struct QuatF32 b = {   (f32)a.x,   (f32)a.y,   (f32)a.z,   (f32)a.w }; return b; } \
static inline struct QuatF64 name##_to_quatf64(T a) { const struct QuatF64 b = {   (f64)a.x,   (f64)a.y,   (f64)a.z,   (f64)a.w }; return b; }

_QUAT_FUNC_TEMPLATE_CAST(struct Quat,    quat)
_QUAT_FUNC_TEMPLATE_CAST(struct QuatI,   quati)
_QUAT_FUNC_TEMPLATE_CAST(struct QuatI32, quati32)
_QUAT_FUNC_TEMPLATE_CAST(struct QuatI64, quati64)
_QUAT_FUNC_TEMPLATE_CAST(struct QuatF32, quatf32)
_QUAT_FUNC_TEMPLATE_CAST(struct QuatF64, quatf64)

#define _MAT4_FUNC_TEMPLATE_CAST(T, name) \
static inline struct Mat4    name##_to_mat4   (T a) { const struct Mat4    b = { (float)a.m00, (float)a.m01, (float)a.m02, (float)a.m03, (float)a.m10, (float)a.m11, (float)a.m12, (float)a.m13, (float)a.m20, (float)a.m21, (float)a.m22, (float)a.m23, (float)a.m30, (float)a.m31, (float)a.m32, (float)a.m33 }; return b; } \
static inline struct Mat4I   name##_to_mat4i  (T a) { const struct Mat4I   b = {   (int)a.m00,   (int)a.m01,   (int)a.m02,   (int)a.m03,   (int)a.m10,   (int)a.m11,   (int)a.m12,   (int)a.m13,   (int)a.m20,   (int)a.m21,   (int)a.m22,   (int)a.m23,   (int)a.m30,   (int)a.m31,   (int)a.m32,   (int)a.m33 }; return b; } \
static inline struct Mat4I32 name##_to_mat4i32(T a) { const struct Mat4I32 b = {   (i32)a.m00,   (i32)a.m01,   (i32)a.m02,   (i32)a.m03,   (i32)a.m10,   (i32)a.m11,   (i32)a.m12,   (i32)a.m13,   (i32)a.m20,   (i32)a.m21,   (i32)a.m22,   (i32)a.m23,   (i32)a.m30,   (i32)a.m31,   (i32)a.m32,   (i32)a.m33 }; return b; } \
static inline struct Mat4I64 name##_to_mat4i64(T a) { const struct Mat4I64 b = {   (i64)a.m00,   (i64)a.m01,   (i64)a.m02,   (i64)a.m03,   (i64)a.m10,   (i64)a.m11,   (i64)a.m12,   (i64)a.m13,   (i64)a.m20,   (i64)a.m21,   (i64)a.m22,   (i64)a.m23,   (i64)a.m30,   (i64)a.m31,   (i64)a.m32,   (i64)a.m33 }; return b; } \
static inline struct Mat4F32 name##_to_mat4f32(T a) { const struct Mat4F32 b = {   (f32)a.m00,   (f32)a.m01,   (f32)a.m02,   (f32)a.m03,   (f32)a.m10,   (f32)a.m11,   (f32)a.m12,   (f32)a.m13,   (f32)a.m20,   (f32)a.m21,   (f32)a.m22,   (f32)a.m23,   (f32)a.m30,   (f32)a.m31,   (f32)a.m32,   (f32)a.m33 }; return b; } \
static inline struct Mat4F64 name##_to_mat4f64(T a) { const struct Mat4F64 b = {   (f64)a.m00,   (f64)a.m01,   (f64)a.m02,   (f64)a.m03,   (f64)a.m10,   (f64)a.m11,   (f64)a.m12,   (f64)a.m13,   (f64)a.m20,   (f64)a.m21,   (f64)a.m22,   (f64)a.m23,   (f64)a.m30,   (f64)a.m31,   (f64)a.m32,   (f64)a.m33 }; return b; }

_MAT4_FUNC_TEMPLATE_CAST(struct Mat4,    mat4)
_MAT4_FUNC_TEMPLATE_CAST(struct Mat4I,   mat4i)
_MAT4_FUNC_TEMPLATE_CAST(struct Mat4I32, mat4i32)
_MAT4_FUNC_TEMPLATE_CAST(struct Mat4I64, mat4i64)
_MAT4_FUNC_TEMPLATE_CAST(struct Mat4F32, mat4f32)
_MAT4_FUNC_TEMPLATE_CAST(struct Mat4F64, mat4f64)

#define _FMAT4_FUNC_TEMPLATE_CAST(T, name) \
static inline struct FMat4    name##_to_fmat4   (T a) { const struct FMat4    b = {{ (float)a.m[0], (float)a.m[1], (float)a.m[2], (float)a.m[3], (float)a.m[4], (float)a.m[5], (float)a.m[6], (float)a.m[7], (float)a.m[8], (float)a.m[9], (float)a.m[10], (float)a.m[11], (float)a.m[12], (float)a.m[13], (float)a.m[14], (float)a.m[15] }}; return b; } \
static inline struct FMat4I   name##_to_fmat4i  (T a) { const struct FMat4I   b = {{   (int)a.m[0],   (int)a.m[1],   (int)a.m[2],   (int)a.m[3],   (int)a.m[4],   (int)a.m[5],   (int)a.m[6],   (int)a.m[7],   (int)a.m[8],   (int)a.m[9],   (int)a.m[10],   (int)a.m[11],   (int)a.m[12],   (int)a.m[13],   (int)a.m[14],   (int)a.m[15] }}; return b; } \
static inline struct FMat4I32 name##_to_fmat4i32(T a) { const struct FMat4I32 b = {{   (i32)a.m[0],   (i32)a.m[1],   (i32)a.m[2],   (i32)a.m[3],   (i32)a.m[4],   (i32)a.m[5],   (i32)a.m[6],   (i32)a.m[7],   (i32)a.m[8],   (i32)a.m[9],   (i32)a.m[10],   (i32)a.m[11],   (i32)a.m[12],   (i32)a.m[13],   (i32)a.m[14],   (i32)a.m[15] }}; return b; } \
static inline struct FMat4I64 name##_to_fmat4i64(T a) { const struct FMat4I64 b = {{   (i64)a.m[0],   (i64)a.m[1],   (i64)a.m[2],   (i64)a.m[3],   (i64)a.m[4],   (i64)a.m[5],   (i64)a.m[6],   (i64)a.m[7],   (i64)a.m[8],   (i64)a.m[9],   (i64)a.m[10],   (i64)a.m[11],   (i64)a.m[12],   (i64)a.m[13],   (i64)a.m[14],   (i64)a.m[15] }}; return b; } \
static inline struct FMat4F32 name##_to_fmat4f32(T a) { const struct FMat4F32 b = {{   (f32)a.m[0],   (f32)a.m[1],   (f32)a.m[2],   (f32)a.m[3],   (f32)a.m[4],   (f32)a.m[5],   (f32)a.m[6],   (f32)a.m[7],   (f32)a.m[8],   (f32)a.m[9],   (f32)a.m[10],   (f32)a.m[11],   (f32)a.m[12],   (f32)a.m[13],   (f32)a.m[14],   (f32)a.m[15] }}; return b; } \
static inline struct FMat4F64 name##_to_fmat4f64(T a) { const struct FMat4F64 b = {{   (f64)a.m[0],   (f64)a.m[1],   (f64)a.m[2],   (f64)a.m[3],   (f64)a.m[4],   (f64)a.m[5],   (f64)a.m[6],   (f64)a.m[7],   (f64)a.m[8],   (f64)a.m[9],   (f64)a.m[10],   (f64)a.m[11],   (f64)a.m[12],   (f64)a.m[13],   (f64)a.m[14],   (f64)a.m[15] }}; return b; }

_FMAT4_FUNC_TEMPLATE_CAST(struct FMat4,    fmat4)
_FMAT4_FUNC_TEMPLATE_CAST(struct FMat4I,   fmat4i)
_FMAT4_FUNC_TEMPLATE_CAST(struct FMat4I32, fmat4i32)
_FMAT4_FUNC_TEMPLATE_CAST(struct FMat4I64, fmat4i64)
_FMAT4_FUNC_TEMPLATE_CAST(struct FMat4F32, fmat4f32)
_FMAT4_FUNC_TEMPLATE_CAST(struct FMat4F64, fmat4f64)

#undef _VEC2_FUNC_TEMPLATE_CAST
#undef _VEC3_FUNC_TEMPLATE_CAST
#undef _VEC4_FUNC_TEMPLATE_CAST
#undef _QUAT_FUNC_TEMPLATE_CAST
#undef _MAT4_FUNC_TEMPLATE_CAST
#undef _FMAT4_FUNC_TEMPLATE_CAST

// =============================



// =============================
// -----------------------------
// TIMESTEP
// -----------------------------

struct Timestep
{
    f64 rate;      // current rate this frame
    f64 ravg_rate; // running average of rate
    f64 mavg_rate; // moving average of rate
    u64 ps_rate;   // rate that updates once a second
    f64 delta;
    f64 target_delta;
    f64 target_rate;
    u64 count;
    f64 elapsed;

    struct
    {
        u64 ps_count;
        f64 timer;
        u64 count;
        f64 elapsed;
        f64 current_time;
        f64 previous_time;
        bool looping;
    } _private;
};

extern struct Timestep timestep_create(f64 rate);
extern void timestep_set_rate(struct Timestep *timestep, f64 rate);
extern bool timestep_tick(struct Timestep *timestep);
extern bool fixedstep_tick(struct Timestep *timestep, f64 delta_time);

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

typedef void (*LogLogFn)(struct LogEvent *ev);
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

extern const char *log_level_string(int level);
extern void log_set_lock(LogLockFn fn, void *udata);
extern void log_set_level(int level);
extern void log_set_quiet(bool enable);
extern int log_add_callback(LogLogFn fn, void *udata, int level);
extern int log_add_fp(FILE *fp, int level);
extern void log_log(int level, const char *file, int line, const char *fmt, ...);

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

extern int platform_init(u32 flags);
extern void platform_deinit(void);

// =============================



// =============================
// -----------------------------
// TIMER
// -----------------------------

#define TIME_TICKS_PER_S  1000000000
#define TIME_TICKS_PER_MS 1000000
#define TIME_TICKS_PER_US 1000
#define TIME_TICKS_PER_NS 1

extern int time_init(void);
extern void time_deinit(void);

extern u64 time_now(void);
extern f64 time_now_s(void);
extern f64 time_now_ms(void);
extern f64 time_now_us(void);
extern f64 time_now_ns(void);

extern void time_wait(u64 ticks);
extern void time_wait_s(f64 s);
extern void time_wait_ms(f64 ms);
extern void time_wait_us(f64 us);
extern void time_wait_ns(f64 ns);

extern u64 time_stot(f64 s);
extern u64 time_mstot(f64 ms);
extern u64 time_ustot(f64 us);
extern u64 time_nstot(f64 ns);

extern f64 time_ttos(u64 ticks);
extern f64 time_ttoms(u64 ticks);
extern f64 time_ttous(u64 ticks);
extern f64 time_ttons(u64 ticks);

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

extern int window_init(void);
extern void window_deinit(void);
extern void window_swap_buffer(void);
extern bool window_keep_open(void);
extern void window_request_close(void);
extern struct Extent window_size(void);
extern int window_width(void);
extern int window_height(void);
extern float window_aspect(void);
extern const char *window_title(void);
extern u32 window_flags(void);
extern bool window_flag_state(u32 flag);
extern u32 window_id(void);
extern void *window_handle(void);
extern void window_set_size(int w, int h);
extern void window_set_title(const char *title);
extern void window_set_flags(u32 flags, bool state);
extern void window_toggle_flags(u32 flags);
extern void window_enable_flags(u32 flags);
extern void window_disable_flags(u32 flags);

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

    B_LEFT = 0,
    B_RIGHT = 1,
    B_MIDDLE = 2,
    B_FORWARD = 3,
    B_BACK = 4,

    B_COUNT,
    B_LAST = B_COUNT - 1
};

struct Keystate
{
    bool down : 1;
    bool pressed : 1;
    bool released : 1;
    bool repeated : 1;
};

extern int input_init(void);
extern void input_deinit(void);
extern void input_poll_events(void);
extern int input_quit_event(void);
extern int input_text(char *buffer, size_t buffer_size);
extern struct Keystate input_keystate(int key);
extern struct Keystate input_btnstate(int btn);
extern bool input_mouse_moved(void);
extern struct Vec2 input_mouse_pos(void);
extern struct Vec2 input_mouse_delta(void);
extern struct Vec2 input_mouse_scroll(void);

// =============================



// =============================
// -----------------------------
// AUDIO (todo)
// -----------------------------

extern int audio_init(void);
extern void audio_deinit(void);

// =============================



// =============================
// -----------------------------
// CAMERA
// -----------------------------

enum CameraType
{
    PERSPECTIVE,
    ORTHOGRAPHIC
};

struct Camera
{
    // projection type
    int type;

    struct Vec3 eye;	/* camera position */
    struct Vec3 target;	/* lookat position */
    struct Vec3 up;		/* camera tilt     */

    // perspective - controls the Y field of view
    float fov;

    // orthographic - controls the size of the near and far clipping planes
    float zoom;
};

extern void camera_init(struct Camera *camera, int type);
extern void camera_move(struct Camera *camera, struct Vec3 direction, float dist);
extern void camera_forward(struct Camera *camera, float dist);
extern void camera_up(struct Camera *camera, float dist);
extern void camera_right(struct Camera *camera, float dist);
extern void camera_pitch(struct Camera *camera, float angle);
extern void camera_yaw(struct Camera *camera, float angle);
extern void camera_roll(struct Camera *camera, float angle);
extern struct Mat4 camera_proj(const struct Camera *camera, float aspect, float near, float far);
extern struct Mat4 camera_view(const struct Camera *camera);

// =============================



// =============================
// -----------------------------
// OPENGL STUFF
// -----------------------------

struct VBO
{
    GLuint handle;
    GLint type;
    bool dyn;
};

struct VAO
{
    GLuint handle;
};

struct Shader
{
    GLuint handle;
    int status;
};

enum ShaderStatus
{
    SHADER_SUCCESS = 0,
    SHADER_VS_COMPILE_ERROR = 1,
    SHADER_FS_COMPILE_ERROR = 2,
    SHADER_PROGRAM_LINKING_ERROR = 3,
    SHADER_INVALID_FILE_PATH = 4,
};

extern struct VBO vbo_create(GLint type, bool dyn);
extern void vbo_free(struct VBO self);
extern void vbo_bind(struct VBO self);
extern void vbo_buff(struct VBO self, const void *data, size_t n);
//void vbo_sub_buff(void *data, size_t offset, size_t n);
extern struct VAO vao_create(void);
extern void vao_free(struct VAO self);
extern void vao_bind(struct VAO self);
extern void vao_attr(struct VAO self, struct VBO vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);
extern struct Shader shader_loadf(const char *vspath, const char *fspath);
extern struct Shader shader_load(const char *vstext, const char *fstext);
extern void shader_free(struct Shader self);
extern void shader_bind(struct Shader self);
extern void shader_uniform_mat4(struct Shader self, const char *name, struct Mat4 m);
extern void shader_uniform_float(struct Shader self, const char *name, float f);
extern void shader_uniform_vec2(struct Shader self, const char *name, struct Vec2 v);
extern void shader_uniform_vec3(struct Shader self, const char *name, struct Vec3 v);
extern void shader_uniform_vec4(struct Shader self, const char *name, struct Vec4 v);
extern void shader_uniform_int(struct Shader self, const char *name, int v);
extern void shader_uniform_uint(struct Shader self, const char *name, unsigned int v);

// =============================

#ifdef __cplusplus
}
#endif

#endif /* VCP_LIB_H */