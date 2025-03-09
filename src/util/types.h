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

#define _extent_type( T ) { T w, h; }
struct extent     _extent_type( int );
struct extentf    _extent_type( float );
struct extent_i32 _extent_type( i32 );
struct extent_i64 _extent_type( i64 );
struct extent_f32 _extent_type( f32 );
struct extent_f64 _extent_type( f64 );

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * SIMPLE PRIMITIVES
 * -----------------------------
 */

#define _line_type( T ) { T x0, y0; T x1, y1; }
#define _point_type( T ) { T x, y; }
#define _circle_type( T ) { T x, y; T r; }
#define _triangle_type( T ) { T x0, y0; T x1, y1; T x2, y2; }
#define _rectangle_type( T ) { T x, y; T w, h; }

struct line          _line_type( float );
struct point         _point_type( float );
struct circle        _circle_type( float );
struct triangle      _triangle_type( float );
struct rectangle     _rectangle_type( float );

struct line_i32      _line_type( i32 );
struct point_i32     _point_type( i32 );
struct circle_i32    _circle_type( i32 );
struct triangle_i32  _triangle_type( i32 );
struct rectangle_i32 _rectangle_type( i32 );

struct line_i64      _line_type( i64 );
struct point_i64     _point_type( i64 );
struct circle_i64    _circle_type( i64 );
struct triangle_i64  _triangle_type( i64 );
struct rectangle_i64 _rectangle_type( i64 );

struct line_f32      _line_type( f32 );
struct point_f32     _point_type( f32 );
struct circle_f32    _circle_type( f32 );
struct triangle_f32  _triangle_type( f32 );
struct rectangle_f32 _rectangle_type( f32 );

struct line_f64      _line_type( f64 );
struct point_f64     _point_type( f64 );
struct circle_f64    _circle_type( f64 );
struct triangle_f64  _triangle_type( f64 );
struct rectangle_f64 _rectangle_type( f64 );

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * COLOR
 * -----------------------------
 */

#define _color_type( T ) { T r, g, b, a; }
struct color     _color_type( u8 );
struct colorf    _color_type( float );
struct color_u8  _color_type( u8 );
struct color_u16 _color_type( u16 );
struct color_f32 _color_type( f32 );
struct color_f64 _color_type( f64 );

static const struct color COLOR_LIGHTGRAY  = { 200, 200, 200, 255 };
static const struct color COLOR_GRAY       = { 130, 130, 130, 255 };
static const struct color COLOR_DARKGRAY   = { 80,  80,  80,  255 };
static const struct color COLOR_YELLOW     = { 253, 249, 0,   255 };
static const struct color COLOR_GOLD       = { 255, 203, 0,   255 };
static const struct color COLOR_ORANGE     = { 255, 161, 0,   255 };
static const struct color COLOR_PINK       = { 255, 109, 194, 255 };
static const struct color COLOR_RED        = { 230, 41,  55,  255 };
static const struct color COLOR_MAROON     = { 190, 33,  55,  255 };
static const struct color COLOR_GREEN      = { 0,   228, 48,  255 };
static const struct color COLOR_LIME       = { 0,   158, 47,  255 };
static const struct color COLOR_DARKGREEN  = { 0,   117, 44,  255 };
static const struct color COLOR_SKYBLUE    = { 102, 191, 255, 255 };
static const struct color COLOR_BLUE       = { 0,   121, 241, 255 };
static const struct color COLOR_DARKBLUE   = { 0,   82,  172, 255 };
static const struct color COLOR_PURPLE     = { 200, 122, 255, 255 };
static const struct color COLOR_VIOLET     = { 135, 60,  190, 255 };
static const struct color COLOR_DARKPURPLE = { 112, 31,  126, 255 };
static const struct color COLOR_BEIGE      = { 211, 176, 131, 255 };
static const struct color COLOR_BROWN      = { 127, 106, 79,  255 };
static const struct color COLOR_DARKBROWN  = { 76,  63,  47,  255 };

static const struct color COLOR_WHITE      = { 255, 255, 255, 255 };
static const struct color COLOR_BLACK      = { 0,   0,   0,   255 };
static const struct color COLOR_BLANK      = { 0,   0,   0,   0   };
static const struct color COLOR_MAGENTA    = { 255, 0,   255, 255 };

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

#define _vec2_type( T )  { T x, y; }
#define _vec3_type( T )  { T x, y, z; }
#define _vec4_type( T )  { T x, y, z, w; }
#define _quat_type( T )  { T x, y, z, w; }
#define _fmat4_type( T ) { T m[ 16 ]; }
#define _mat4_type( T )  { T m00, m01, m02, m03; \
						   T m10, m11, m12, m13; \
	                       T m20, m21, m22, m23; \
	                       T m30, m31, m32, m33; }

struct vec2 _vec2_type( float );
struct vec3 _vec3_type( float );
struct vec4 _vec4_type( float );
struct quat _quat_type( float );
struct mat4 _mat4_type( float );
struct fmat4 _fmat4_type( float );

struct vec2i _vec2_type( int );
struct vec3i _vec3_type( int );
struct vec4i _vec4_type( int );
struct quati _quat_type( int );
struct mat4i _mat4_type( int );
struct fmat4i _fmat4_type( int );

struct vec2_i32 _vec2_type( i32 );
struct vec3_i32 _vec3_type( i32 );
struct vec4_i32 _vec4_type( i32 );
struct quat_i32 _quat_type( i32 );
struct mat4_i32 _mat4_type( i32 );
struct fmat4_i32 _fmat4_type( i32 );

struct vec2_i64 _vec2_type( i64 );
struct vec3_i64 _vec3_type( i64 );
struct vec4_i64 _vec4_type( i64 );
struct quat_i64 _quat_type( i64 );
struct mat4_i64 _mat4_type( i64 );
struct fmat4_i64 _fmat4_type( i64 );

struct vec2_f32 _vec2_type( f32 );
struct vec3_f32 _vec3_type( f32 );
struct vec4_f32 _vec4_type( f32 );
struct quat_f32 _quat_type( f32 );
struct mat4_f32 _mat4_type( f32 );
struct fmat4_f32 _fmat4_type( f32 );

struct vec2_f64 _vec2_type( f64 );
struct vec3_f64 _vec3_type( f64 );
struct vec4_f64 _vec4_type( f64 );
struct quat_f64 _quat_type( f64 );
struct mat4_f64 _mat4_type( f64 );
struct fmat4_f64 _fmat4_type( f64 );

/*
 * =============================
 */

#endif
