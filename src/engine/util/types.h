#ifndef TYPES_H
#define TYPES_H

/*
 * Type definitions for standard types and math types
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct color_s
{
    float r;
    float g;
    float b;
    float a;
} color_t;

typedef struct vec2_s
{
	float x;
	float y;
} vec2_t;

typedef struct vec3_s
{
	float x;
	float y;
	float z;
} vec3_t;

typedef struct vec4_s
{
	float x;
	float y;
	float z;
	float w;
} vec4_t;

typedef vec4_t quat_t;

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
typedef struct mat4_s
{
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;
} mat4_t;

typedef struct float16v_s
{
	float v[ 16 ];
} float16v_t;

#endif
