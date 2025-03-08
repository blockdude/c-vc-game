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
 * STANDARD TYPEDEFS
 * -----------------------------
 */

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

#define _vec2_decl_cast_func( A, name ) \
static inline struct vec2     name##_to_vec2    ( const A a ) { const struct vec2     b = { ( float ) a.x, ( float ) a.y }; return b; } \
static inline struct vec2i    name##_to_vec2i   ( const A a ) { const struct vec2i    b = { ( int )   a.x, ( int )   a.y }; return b; } \
static inline struct vec2_i32 name##_to_vec2_i32( const A a ) { const struct vec2_i32 b = { ( i32 )   a.x, ( i32 )   a.y }; return b; } \
static inline struct vec2_i64 name##_to_vec2_i64( const A a ) { const struct vec2_i64 b = { ( i64 )   a.x, ( i64 )   a.y }; return b; } \
static inline struct vec2_f32 name##_to_vec2_f32( const A a ) { const struct vec2_f32 b = { ( f32 )   a.x, ( f32 )   a.y }; return b; } \
static inline struct vec2_f64 name##_to_vec2_f64( const A a ) { const struct vec2_f64 b = { ( f64 )   a.x, ( f64 )   a.y }; return b; }

_vec2_decl_cast_func( struct vec2, vec2 );
_vec2_decl_cast_func( struct vec2i, vec2i );
_vec2_decl_cast_func( struct vec2_i32, vec2_i32 );
_vec2_decl_cast_func( struct vec2_i64, vec2_i64 );
_vec2_decl_cast_func( struct vec2_f32, vec2_f32 );
_vec2_decl_cast_func( struct vec2_f64, vec2_f64 );

#define _vec3_decl_cast_func( A, name ) \
static inline struct vec3     name##_to_vec3    ( const A a ) { const struct vec3     b = { ( float ) a.x, ( float ) a.y, ( float ) a.z }; return b; } \
static inline struct vec3i    name##_to_vec3i   ( const A a ) { const struct vec3i    b = { ( int )   a.x, ( int )   a.y, ( int )   a.z }; return b; } \
static inline struct vec3_i32 name##_to_vec3_i32( const A a ) { const struct vec3_i32 b = { ( i32 )   a.x, ( i32 )   a.y, ( i32 )   a.z }; return b; } \
static inline struct vec3_i64 name##_to_vec3_i64( const A a ) { const struct vec3_i64 b = { ( i64 )   a.x, ( i64 )   a.y, ( i64 )   a.z }; return b; } \
static inline struct vec3_f32 name##_to_vec3_f32( const A a ) { const struct vec3_f32 b = { ( f32 )   a.x, ( f32 )   a.y, ( f32 )   a.z }; return b; } \
static inline struct vec3_f64 name##_to_vec3_f64( const A a ) { const struct vec3_f64 b = { ( f64 )   a.x, ( f64 )   a.y, ( f64 )   a.z }; return b; }

_vec3_decl_cast_func( struct vec3, vec3 );
_vec3_decl_cast_func( struct vec3i, vec3i );
_vec3_decl_cast_func( struct vec3_i32, vec3_i32 );
_vec3_decl_cast_func( struct vec3_i64, vec3_i64 );
_vec3_decl_cast_func( struct vec3_f32, vec3_f32 );
_vec3_decl_cast_func( struct vec3_f64, vec3_f64 );

#define _vec4_decl_cast_func( A, name ) \
static inline struct vec4     name##_to_vec4    ( const A a ) { const struct vec4     b = { ( float ) a.x, ( float ) a.y, ( float ) a.z, ( float ) a.w }; return b; } \
static inline struct vec4i    name##_to_vec4i   ( const A a ) { const struct vec4i    b = { ( int )   a.x, ( int )   a.y, ( int )   a.z, ( int )   a.w }; return b; } \
static inline struct vec4_i32 name##_to_vec4_i32( const A a ) { const struct vec4_i32 b = { ( i32 )   a.x, ( i32 )   a.y, ( i32 )   a.z, ( i32 )   a.w }; return b; } \
static inline struct vec4_i64 name##_to_vec4_i64( const A a ) { const struct vec4_i64 b = { ( i64 )   a.x, ( i64 )   a.y, ( i64 )   a.z, ( i64 )   a.w }; return b; } \
static inline struct vec4_f32 name##_to_vec4_f32( const A a ) { const struct vec4_f32 b = { ( f32 )   a.x, ( f32 )   a.y, ( f32 )   a.z, ( f32 )   a.w }; return b; } \
static inline struct vec4_f64 name##_to_vec4_f64( const A a ) { const struct vec4_f64 b = { ( f64 )   a.x, ( f64 )   a.y, ( f64 )   a.z, ( f64 )   a.w }; return b; }

_vec4_decl_cast_func( struct vec4, vec4 );
_vec4_decl_cast_func( struct vec4i, vec4i );
_vec4_decl_cast_func( struct vec4_i32, vec4_i32 );
_vec4_decl_cast_func( struct vec4_i64, vec4_i64 );
_vec4_decl_cast_func( struct vec4_f32, vec4_f32 );
_vec4_decl_cast_func( struct vec4_f64, vec4_f64 );

#define _quat_decl_cast_func( A, name ) \
static inline struct quat     name##_to_quat    ( const A a ) { const struct quat     b = { ( float ) a.x, ( float ) a.y, ( float ) a.z, ( float ) a.w }; return b; } \
static inline struct quati    name##_to_quati   ( const A a ) { const struct quati    b = { ( int )   a.x, ( int )   a.y, ( int )   a.z, ( int )   a.w }; return b; } \
static inline struct quat_i32 name##_to_quat_i32( const A a ) { const struct quat_i32 b = { ( i32 )   a.x, ( i32 )   a.y, ( i32 )   a.z, ( i32 )   a.w }; return b; } \
static inline struct quat_i64 name##_to_quat_i64( const A a ) { const struct quat_i64 b = { ( i64 )   a.x, ( i64 )   a.y, ( i64 )   a.z, ( i64 )   a.w }; return b; } \
static inline struct quat_f32 name##_to_quat_f32( const A a ) { const struct quat_f32 b = { ( f32 )   a.x, ( f32 )   a.y, ( f32 )   a.z, ( f32 )   a.w }; return b; } \
static inline struct quat_f64 name##_to_quat_f64( const A a ) { const struct quat_f64 b = { ( f64 )   a.x, ( f64 )   a.y, ( f64 )   a.z, ( f64 )   a.w }; return b; }

_quat_decl_cast_func( struct quat, quat );
_quat_decl_cast_func( struct quati, quati );
_quat_decl_cast_func( struct quat_i32, quat_i32 );
_quat_decl_cast_func( struct quat_i64, quat_i64 );
_quat_decl_cast_func( struct quat_f32, quat_f32 );
_quat_decl_cast_func( struct quat_f64, quat_f64 );

#define _mat4_decl_cast_func( A, name ) \
static inline struct mat4     name##_to_mat4    ( const A a ) { const struct mat4     b = { ( float ) a.m00, ( float ) a.m01, ( float ) a.m02, ( float ) a.m03, ( float ) a.m10, ( float ) a.m11, ( float ) a.m12, ( float ) a.m13, ( float ) a.m20, ( float ) a.m21, ( float ) a.m22, ( float ) a.m23, ( float ) a.m30, ( float ) a.m31, ( float ) a.m32, ( float ) a.m33 }; return b; } \
static inline struct mat4i    name##_to_mat4i   ( const A a ) { const struct mat4i    b = { ( int )   a.m00, ( int )   a.m01, ( int )   a.m02, ( int )   a.m03, ( int )   a.m10, ( int )   a.m11, ( int )   a.m12, ( int )   a.m13, ( int )   a.m20, ( int )   a.m21, ( int )   a.m22, ( int )   a.m23, ( int )   a.m30, ( int )   a.m31, ( int )   a.m32, ( int )   a.m33 }; return b; } \
static inline struct mat4_i32 name##_to_mat4_i32( const A a ) { const struct mat4_i32 b = { ( i32 )   a.m00, ( i32 )   a.m01, ( i32 )   a.m02, ( i32 )   a.m03, ( i32 )   a.m10, ( i32 )   a.m11, ( i32 )   a.m12, ( i32 )   a.m13, ( i32 )   a.m20, ( i32 )   a.m21, ( i32 )   a.m22, ( i32 )   a.m23, ( i32 )   a.m30, ( i32 )   a.m31, ( i32 )   a.m32, ( i32 )   a.m33 }; return b; } \
static inline struct mat4_i64 name##_to_mat4_i64( const A a ) { const struct mat4_i64 b = { ( i64 )   a.m00, ( i64 )   a.m01, ( i64 )   a.m02, ( i64 )   a.m03, ( i64 )   a.m10, ( i64 )   a.m11, ( i64 )   a.m12, ( i64 )   a.m13, ( i64 )   a.m20, ( i64 )   a.m21, ( i64 )   a.m22, ( i64 )   a.m23, ( i64 )   a.m30, ( i64 )   a.m31, ( i64 )   a.m32, ( i64 )   a.m33 }; return b; } \
static inline struct mat4_f32 name##_to_mat4_f32( const A a ) { const struct mat4_f32 b = { ( f32 )   a.m00, ( f32 )   a.m01, ( f32 )   a.m02, ( f32 )   a.m03, ( f32 )   a.m10, ( f32 )   a.m11, ( f32 )   a.m12, ( f32 )   a.m13, ( f32 )   a.m20, ( f32 )   a.m21, ( f32 )   a.m22, ( f32 )   a.m23, ( f32 )   a.m30, ( f32 )   a.m31, ( f32 )   a.m32, ( f32 )   a.m33 }; return b; } \
static inline struct mat4_f64 name##_to_mat4_f64( const A a ) { const struct mat4_f64 b = { ( f64 )   a.m00, ( f64 )   a.m01, ( f64 )   a.m02, ( f64 )   a.m03, ( f64 )   a.m10, ( f64 )   a.m11, ( f64 )   a.m12, ( f64 )   a.m13, ( f64 )   a.m20, ( f64 )   a.m21, ( f64 )   a.m22, ( f64 )   a.m23, ( f64 )   a.m30, ( f64 )   a.m31, ( f64 )   a.m32, ( f64 )   a.m33 }; return b; }

_mat4_decl_cast_func( struct mat4, mat4 );
_mat4_decl_cast_func( struct mat4i, mat4i );
_mat4_decl_cast_func( struct mat4_i32, mat4_i32 );
_mat4_decl_cast_func( struct mat4_i64, mat4_i64 );
_mat4_decl_cast_func( struct mat4_f32, mat4_f32 );
_mat4_decl_cast_func( struct mat4_f64, mat4_f64 );

#define _fmat4_decl_cast_func( A, name ) \
static inline struct fmat4     name##_to_fmat4( const A a )     { const struct fmat4     b = { ( float ) a.m[ 0 ], ( float ) a.m[ 1 ], ( float ) a.m[ 2 ], ( float ) a.m[ 3 ], ( float ) a.m[ 4 ], ( float ) a.m[ 5 ], ( float ) a.m[ 6 ], ( float ) a.m[ 7 ], ( float ) a.m[ 8 ], ( float ) a.m[ 9 ], ( float ) a.m[ 10 ], ( float ) a.m[ 11 ], ( float ) a.m[ 12 ], ( float ) a.m[ 13 ], ( float ) a.m[ 14 ], ( float ) a.m[ 15 ] }; return b; } \
static inline struct fmat4i    name##_to_fmat4i( const A a )    { const struct fmat4i    b = { ( int )   a.m[ 0 ], ( int )   a.m[ 1 ], ( int )   a.m[ 2 ], ( int )   a.m[ 3 ], ( int )   a.m[ 4 ], ( int )   a.m[ 5 ], ( int )   a.m[ 6 ], ( int )   a.m[ 7 ], ( int )   a.m[ 8 ], ( int )   a.m[ 9 ], ( int )   a.m[ 10 ], ( int )   a.m[ 11 ], ( int )   a.m[ 12 ], ( int )   a.m[ 13 ], ( int )   a.m[ 14 ], ( int )   a.m[ 15 ] }; return b; } \
static inline struct fmat4_i32 name##_to_fmat4_i32( const A a ) { const struct fmat4_i32 b = { ( i32 )   a.m[ 0 ], ( i32 )   a.m[ 1 ], ( i32 )   a.m[ 2 ], ( i32 )   a.m[ 3 ], ( i32 )   a.m[ 4 ], ( i32 )   a.m[ 5 ], ( i32 )   a.m[ 6 ], ( i32 )   a.m[ 7 ], ( i32 )   a.m[ 8 ], ( i32 )   a.m[ 9 ], ( i32 )   a.m[ 10 ], ( i32 )   a.m[ 11 ], ( i32 )   a.m[ 12 ], ( i32 )   a.m[ 13 ], ( i32 )   a.m[ 14 ], ( i32 )   a.m[ 15 ] }; return b; } \
static inline struct fmat4_i64 name##_to_fmat4_i64( const A a ) { const struct fmat4_i64 b = { ( i64 )   a.m[ 0 ], ( i64 )   a.m[ 1 ], ( i64 )   a.m[ 2 ], ( i64 )   a.m[ 3 ], ( i64 )   a.m[ 4 ], ( i64 )   a.m[ 5 ], ( i64 )   a.m[ 6 ], ( i64 )   a.m[ 7 ], ( i64 )   a.m[ 8 ], ( i64 )   a.m[ 9 ], ( i64 )   a.m[ 10 ], ( i64 )   a.m[ 11 ], ( i64 )   a.m[ 12 ], ( i64 )   a.m[ 13 ], ( i64 )   a.m[ 14 ], ( i64 )   a.m[ 15 ] }; return b; } \
static inline struct fmat4_f32 name##_to_fmat4_f32( const A a ) { const struct fmat4_f32 b = { ( f32 )   a.m[ 0 ], ( f32 )   a.m[ 1 ], ( f32 )   a.m[ 2 ], ( f32 )   a.m[ 3 ], ( f32 )   a.m[ 4 ], ( f32 )   a.m[ 5 ], ( f32 )   a.m[ 6 ], ( f32 )   a.m[ 7 ], ( f32 )   a.m[ 8 ], ( f32 )   a.m[ 9 ], ( f32 )   a.m[ 10 ], ( f32 )   a.m[ 11 ], ( f32 )   a.m[ 12 ], ( f32 )   a.m[ 13 ], ( f32 )   a.m[ 14 ], ( f32 )   a.m[ 15 ] }; return b; } \
static inline struct fmat4_f64 name##_to_fmat4_f64( const A a ) { const struct fmat4_f64 b = { ( f64 )   a.m[ 0 ], ( f64 )   a.m[ 1 ], ( f64 )   a.m[ 2 ], ( f64 )   a.m[ 3 ], ( f64 )   a.m[ 4 ], ( f64 )   a.m[ 5 ], ( f64 )   a.m[ 6 ], ( f64 )   a.m[ 7 ], ( f64 )   a.m[ 8 ], ( f64 )   a.m[ 9 ], ( f64 )   a.m[ 10 ], ( f64 )   a.m[ 11 ], ( f64 )   a.m[ 12 ], ( f64 )   a.m[ 13 ], ( f64 )   a.m[ 14 ], ( f64 )   a.m[ 15 ] }; return b; }

_fmat4_decl_cast_func( struct fmat4, fmat4 );
_fmat4_decl_cast_func( struct fmat4i, fmat4i );
_fmat4_decl_cast_func( struct fmat4_i32, fmat4_i32 );
_fmat4_decl_cast_func( struct fmat4_i64, fmat4_i64 );
_fmat4_decl_cast_func( struct fmat4_f32, fmat4_f32 );
_fmat4_decl_cast_func( struct fmat4_f64, fmat4_f64 );

/*
 * =============================
 */

#endif
