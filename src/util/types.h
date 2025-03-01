#ifndef VCP_TYPES_H
#define VCP_TYPES_H

/*
 * =============================
 * -----------------------------
 * STANDARD TYPES
 * -----------------------------
 */

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
struct extent_i32 _extent_type( int32_t );
struct extent_i64 _extent_type( int64_t );
struct extent_f32 _extent_type( float );
struct extent_f64 _extent_type( double );

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

struct line_i32      _line_type( int32_t );
struct point_i32     _point_type( int32_t );
struct circle_i32    _circle_type( int32_t );
struct triangle_i32  _triangle_type( int32_t );
struct rectangle_i32 _rectangle_type( int32_t );

struct line_i64      _line_type( int64_t );
struct point_i64     _point_type( int64_t );
struct circle_i64    _circle_type( int64_t );
struct triangle_i64  _triangle_type( int64_t );
struct rectangle_i64 _rectangle_type( int64_t );

struct line_f32      _line_type( float );
struct point_f32     _point_type( float );
struct circle_f32    _circle_type( float );
struct triangle_f32  _triangle_type( float );
struct rectangle_f32 _rectangle_type( float );

struct line_f64      _line_type( double );
struct point_f64     _point_type( double );
struct circle_f64    _circle_type( double );
struct triangle_f64  _triangle_type( double );
struct rectangle_f64 _rectangle_type( double );

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
struct color     _color_type( uint8_t );
struct color_u8  _color_type( uint8_t );
struct color_u16 _color_type( uint16_t );
struct color_f32 _color_type( float );
struct color_f64 _color_type( double );

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

struct vec2_i32 _vec2_type( int32_t );
struct vec3_i32 _vec3_type( int32_t );
struct vec4_i32 _vec4_type( int32_t );
struct quat_i32 _quat_type( int32_t );
struct mat4_i32 _mat4_type( int32_t );
struct fmat4_i32 _fmat4_type( int32_t );

struct vec2_i64 _vec2_type( int64_t );
struct vec3_i64 _vec3_type( int64_t );
struct vec4_i64 _vec4_type( int64_t );
struct quat_i64 _quat_type( int64_t );
struct mat4_i64 _mat4_type( int64_t );
struct fmat4_i64 _fmat4_type( int64_t );

struct vec2_f32 _vec2_type( float );
struct vec3_f32 _vec3_type( float );
struct vec4_f32 _vec4_type( float );
struct quat_f32 _quat_type( float );
struct mat4_f32 _mat4_type( float );
struct fmat4_f32 _fmat4_type( float );

struct vec2_f64 _vec2_type( double );
struct vec3_f64 _vec3_type( double );
struct vec4_f64 _vec4_type( double );
struct quat_f64 _quat_type( double );
struct mat4_f64 _mat4_type( double );
struct fmat4_f64 _fmat4_type( double );

/*
 * =============================
 */

#endif
