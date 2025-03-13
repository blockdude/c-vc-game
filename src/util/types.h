#ifndef VCP_TYPES_H
#define VCP_TYPES_H

/*
 * =============================
 * -----------------------------
 * STANDARD TYPES
 * -----------------------------
 */

#include "../common.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * SIZE
 * -----------------------------
 */

#define _EXTENT_TEMPLATE(T) { T w, h; }
struct extent     _EXTENT_TEMPLATE(int);
struct extentf    _EXTENT_TEMPLATE(float);
struct extent_i32 _EXTENT_TEMPLATE(i32);
struct extent_i64 _EXTENT_TEMPLATE(i64);
struct extent_f32 _EXTENT_TEMPLATE(f32);
struct extent_f64 _EXTENT_TEMPLATE(f64);

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * SIMPLE PRIMITIVES
 * -----------------------------
 */

#define _LINE_TEMPLATE(T) { T x0, y0; T x1, y1; }
#define _POINT_TEMPLATE(T) { T x, y; }
#define _CIRCLE_TEMPLATE(T) { T x, y; T r; }
#define _TRIANGLE_TEMPLATE(T) { T x0, y0; T x1, y1; T x2, y2; }
#define _RECTANGLE_TEMPLATE(T) { T x, y; T w, h; }

struct line          _LINE_TEMPLATE(float);
struct point         _POINT_TEMPLATE(float);
struct circle        _CIRCLE_TEMPLATE(float);
struct triangle      _TRIANGLE_TEMPLATE(float);
struct rectangle     _RECTANGLE_TEMPLATE(float);

struct line_i32      _LINE_TEMPLATE(i32);
struct point_i32     _POINT_TEMPLATE(i32);
struct circle_i32    _CIRCLE_TEMPLATE(i32);
struct triangle_i32  _TRIANGLE_TEMPLATE(i32);
struct rectangle_i32 _RECTANGLE_TEMPLATE(i32);

struct line_i64      _LINE_TEMPLATE(i64);
struct point_i64     _POINT_TEMPLATE(i64);
struct circle_i64    _CIRCLE_TEMPLATE(i64);
struct triangle_i64  _TRIANGLE_TEMPLATE(i64);
struct rectangle_i64 _RECTANGLE_TEMPLATE(i64);

struct line_f32      _LINE_TEMPLATE(f32);
struct point_f32     _POINT_TEMPLATE(f32);
struct circle_f32    _CIRCLE_TEMPLATE(f32);
struct triangle_f32  _TRIANGLE_TEMPLATE(f32);
struct rectangle_f32 _RECTANGLE_TEMPLATE(f32);

struct line_f64      _LINE_TEMPLATE(f64);
struct point_f64     _POINT_TEMPLATE(f64);
struct circle_f64    _CIRCLE_TEMPLATE(f64);
struct triangle_f64  _TRIANGLE_TEMPLATE(f64);
struct rectangle_f64 _RECTANGLE_TEMPLATE(f64);

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * COLOR
 * -----------------------------
 */

#define _COLOR_TEMPLATE(T) { T r, g, b, a; }
struct color     _COLOR_TEMPLATE(u8);
struct colorf    _COLOR_TEMPLATE(float);
struct color_u8  _COLOR_TEMPLATE(u8);
struct color_u16 _COLOR_TEMPLATE(u16);
struct color_f32 _COLOR_TEMPLATE(f32);
struct color_f64 _COLOR_TEMPLATE(f64);

static const struct color COLOR_LIGHTGRAY  = { 200, 200, 200, 255 };
static const struct color COLOR_GRAY       = { 130, 130, 130, 255 };
static const struct color COLOR_DARKGRAY   = {  80,  80,  80, 255 };
static const struct color COLOR_YELLOW     = { 253, 249,   0, 255 };
static const struct color COLOR_GOLD       = { 255, 203,   0, 255 };
static const struct color COLOR_ORANGE     = { 255, 161,   0, 255 };
static const struct color COLOR_PINK       = { 255, 109, 194, 255 };
static const struct color COLOR_RED        = { 230,  41,  55, 255 };
static const struct color COLOR_MAROON     = { 190,  33,  55, 255 };
static const struct color COLOR_GREEN      = {   0, 228,  48, 255 };
static const struct color COLOR_LIME       = {   0, 158,  47, 255 };
static const struct color COLOR_DARKGREEN  = {   0, 117,  44, 255 };
static const struct color COLOR_SKYBLUE    = { 102, 191, 255, 255 };
static const struct color COLOR_BLUE       = {   0, 121, 241, 255 };
static const struct color COLOR_DARKBLUE   = {   0,  82, 172, 255 };
static const struct color COLOR_PURPLE     = { 200, 122, 255, 255 };
static const struct color COLOR_VIOLET     = { 135,  60, 190, 255 };
static const struct color COLOR_DARKPURPLE = { 112,  31, 126, 255 };
static const struct color COLOR_BEIGE      = { 211, 176, 131, 255 };
static const struct color COLOR_BROWN      = { 127, 106,  79, 255 };
static const struct color COLOR_DARKBROWN  = {  76,  63,  47, 255 };
                                                                  
static const struct color COLOR_WHITE      = { 255, 255, 255, 255 };
static const struct color COLOR_BLACK      = {   0,   0,   0, 255 };
static const struct color COLOR_BLANK      = {   0,   0,   0,   0 };
static const struct color COLOR_MAGENTA    = { 255,   0, 255, 255 };

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * LINEAR ALGEBRA
 * -----------------------------
 */

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

#define _VEC2_TEMPLATE(T)  { T x, y; }
#define _VEC3_TEMPLATE(T)  { T x, y, z; }
#define _VEC4_TEMPLATE(T)  { T x, y, z, w; }
#define _QUAT_TEMPLATE(T)  { T x, y, z, w; }
#define _FMAT4_TEMPLATE(T) { T m[ 16 ];}
#define _MAT4_TEMPLATE(T)  { T m00, m01, m02, m03; \
                             T m10, m11, m12, m13; \
                             T m20, m21, m22, m23; \
                             T m30, m31, m32, m33; }

struct vec2 _VEC2_TEMPLATE(float);
struct vec3 _VEC3_TEMPLATE(float);
struct vec4 _VEC4_TEMPLATE(float);
struct quat _QUAT_TEMPLATE(float);
struct mat4 _MAT4_TEMPLATE(float);
struct fmat4 _FMAT4_TEMPLATE(float);

struct vec2i _VEC2_TEMPLATE(int);
struct vec3i _VEC3_TEMPLATE(int);
struct vec4i _VEC4_TEMPLATE(int);
struct quati _QUAT_TEMPLATE(int);
struct mat4i _MAT4_TEMPLATE(int);
struct fmat4i _FMAT4_TEMPLATE(int);

struct vec2_i32 _VEC2_TEMPLATE(i32);
struct vec3_i32 _VEC3_TEMPLATE(i32);
struct vec4_i32 _VEC4_TEMPLATE(i32);
struct quat_i32 _QUAT_TEMPLATE(i32);
struct mat4_i32 _MAT4_TEMPLATE(i32);
struct fmat4_i32 _FMAT4_TEMPLATE(i32);

struct vec2_i64 _VEC2_TEMPLATE(i64);
struct vec3_i64 _VEC3_TEMPLATE(i64);
struct vec4_i64 _VEC4_TEMPLATE(i64);
struct quat_i64 _QUAT_TEMPLATE(i64);
struct mat4_i64 _MAT4_TEMPLATE(i64);
struct fmat4_i64 _FMAT4_TEMPLATE(i64);

struct vec2_f32 _VEC2_TEMPLATE(f32);
struct vec3_f32 _VEC3_TEMPLATE(f32);
struct vec4_f32 _VEC4_TEMPLATE(f32);
struct quat_f32 _QUAT_TEMPLATE(f32);
struct mat4_f32 _MAT4_TEMPLATE(f32);
struct fmat4_f32 _FMAT4_TEMPLATE(f32);

struct vec2_f64 _VEC2_TEMPLATE(f64);
struct vec3_f64 _VEC3_TEMPLATE(f64);
struct vec4_f64 _VEC4_TEMPLATE(f64);
struct quat_f64 _QUAT_TEMPLATE(f64);
struct mat4_f64 _MAT4_TEMPLATE(f64);
struct fmat4_f64 _FMAT4_TEMPLATE(f64);

/*
 * =============================
 */

#endif