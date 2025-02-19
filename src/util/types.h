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

#define size size_i32

struct size_i32
{
	int32_t w, h;
};

struct size_i64
{
	int64_t w, h;
};

struct size_f32
{
	float w, h;
};

struct size_f64
{
	double w, h;
};

/*
 * =============================
 * -----------------------------
 * SIMPLE PRIMITIVES
 * -----------------------------
 */

// default
#define point point_f32
#define line line_f32
#define rectangle rectangle_f32
#define circle circle_f32
#define triangle triangle_f32

// i32

struct point_i32
{
	int32_t x, y;
};

struct line_i32
{
	int32_t x0, y0;
	int32_t x1, y1;
};

struct rectangle_i32
{
	int32_t x;
	int32_t y;
	int32_t w;
	int32_t h;
};

struct circle_i32
{
	int32_t x;
	int32_t y;
	int32_t r;
};

struct triangle_i32
{
	int32_t x0, y0;
	int32_t x1, y1;
	int32_t x2, y2;
};

// i64

struct point_i64
{
	int64_t x, y;
};

struct line_i64
{
	int64_t x0, y0;
	int64_t x1, y1;
};

struct rectangle_i64
{
	int64_t x;
	int64_t y;
	int64_t w;
	int64_t h;
};

struct circle_i64
{
	int64_t x;
	int64_t y;
	int64_t r;
};

struct triangle_i64
{
	int64_t x0, y0;
	int64_t x1, y1;
	int64_t x2, y2;
};

// f32

struct point_f32
{
	float x, y;
};

struct line_f32
{
	float x0, y0;
	float x1, y1;
};

struct rectangle_f32
{
	float x;
	float y;
	float w;
	float h;
};

struct circle_f32
{
	float x;
	float y;
	float r;
};

struct triangle_f32
{
	float x0, y0;
	float x1, y1;
	float x2, y2;
};

// f64

struct point_f64
{
	double x, y;
};

struct line_f64
{
	double x0, y0;
	double x1, y1;
};

struct rectangle_f64
{
	double x;
	double y;
	double w;
	double h;
};

struct circle_f64
{
	double x;
	double y;
	double r;
};

struct triangle_f64
{
	double x0, y0;
	double x1, y1;
	double x2, y2;
};

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * COLOR
 * -----------------------------
 */

#define color color_u8

struct color_u8
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

struct color_u16
{
	uint16_t r;
	uint16_t g;
	uint16_t b;
	uint16_t a;
};

struct color_f32
{
    float r;
    float g;
    float b;
    float a;
};

struct color_f64
{
	double r;
	double g;
	double b;
	double a;
};

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

// default types

#define vec2 vec2_f32
#define vec3 vec3_f32
#define vec4 vec4_f32
#define quat quat_f32
#define mat4 mat4_f32

#define vec2i vec2_i32
#define vec3i vec3_i32
#define vec4i vec4_i32
#define quati quat_i32
#define mat4i mat4_i32

// i32

struct vec2_i32
{
	int32_t x;
	int32_t y;
};

struct vec3_i32
{
	int32_t x;
	int32_t y;
	int32_t z;
};

struct vec4_i32
{
	int32_t x;
	int32_t y;
	int32_t z;
	int32_t w;
};

struct quat_i32
{
	int32_t x;
	int32_t y;
	int32_t z;
	int32_t w;
};

struct mat4_i32
{
	int32_t m00, m01, m02, m03;
	int32_t m10, m11, m12, m13;
	int32_t m20, m21, m22, m23;
	int32_t m30, m31, m32, m33;
};

struct mat4_i32_flat
{
	int32_t m[ 16 ];
};

// i64

struct vec2_i64
{
	int64_t x;
	int64_t y;
};

struct vec3_i64
{
	int64_t x;
	int64_t y;
	int64_t z;
};

struct vec4_i64
{
	int64_t x;
	int64_t y;
	int64_t z;
	int64_t w;
};

struct quat_i64
{
	int64_t x;
	int64_t y;
	int64_t z;
	int64_t w;
};

struct mat4_i64
{
	int64_t m00, m01, m02, m03;
	int64_t m10, m11, m12, m13;
	int64_t m20, m21, m22, m23;
	int64_t m30, m31, m32, m33;
};

struct mat4_i64_flat
{
	int64_t m[ 16 ];
};

// f32

struct vec2_f32
{
	float x;
	float y;
};

struct vec3_f32
{
	float x;
	float y;
	float z;
};

struct vec4_f32
{
	float x;
	float y;
	float z;
	float w;
};

struct quat_f32
{
	float x;
	float y;
	float z;
	float w;
};

struct mat4_f32
{
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;
};

struct mat4_f32_flat
{
	float m[ 16 ];
};

// f64

struct vec2_f64
{
	double x;
	double y;
};

struct vec3_f64
{
	double x;
	double y;
	double z;
};

struct vec4_f64
{
	double x;
	double y;
	double z;
	double w;
};

struct quat_f64
{
	double x;
	double y;
	double z;
	double w;
};

struct mat4_f64
{
	double m00, m01, m02, m03;
	double m10, m11, m12, m13;
	double m20, m21, m22, m23;
	double m30, m31, m32, m33;
};

struct mat4_f64_flat
{
	double m[ 16 ];
};

/*
 * =============================
 */

#endif
