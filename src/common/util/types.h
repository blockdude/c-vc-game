#ifndef TYPES_H
#define TYPES_H

/*
 * Type definitions for standard types and math types
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct point
{
	float x, y;
} point_t;

typedef struct line
{
	float x0, y0;
	float x1, y1;
} line_t;

typedef struct rectangle
{
	float x;
	float y;
	float w;
	float h;
} rectangle_t;

typedef struct circle
{
	float x;
	float y;
	float r;
} circle_t;

typedef struct triangle
{
	float x0, y0;
	float x1, y1;
	float x2, y2;
} triangle_t;

typedef struct color
{
    float r;
    float g;
    float b;
    float a;
} color_t;

typedef struct vec2
{
	float x;
	float y;
} vec2_t;

typedef struct vec3
{
	float x;
	float y;
	float z;
} vec3_t;

typedef struct vec4
{
	float x;
	float y;
	float z;
	float w;
} vec4_t;

typedef struct quat
{
	float x;
	float y;
	float z;
	float w;
} quat_t;

/*
 * Memory layout is row major.
 *     ex: row[ 0 ] = { m00, m01, m02, m03 }
 *
 * Samantical layout is column major.
 *     ex: row[ 0 ] = { m00, m10, m20, m30 }
 *
 * When we convert it to an array it will look like:
 *	   { m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33 }
 */
typedef struct mat4
{
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;
} mat4_t;

typedef struct float16v
{
	float v[ 16 ];
} float16v_t;

#endif
