#ifndef TYPES_H
#define TYPES_H

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
 * GEOMETRY
 * -----------------------------
 */

struct point
{
	float x, y;
};

struct line
{
	float x0, y0;
	float x1, y1;
};

struct rectangle
{
	float x;
	float y;
	float w;
	float h;
};

struct circle
{
	float x;
	float y;
	float r;
};

struct triangle
{
	float x0, y0;
	float x1, y1;
	float x2, y2;
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

struct color
{
    float r;
    float g;
    float b;
    float a;
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

struct vec2
{
	float x;
	float y;
};

struct vec3
{
	float x;
	float y;
	float z;
};

struct vec4
{
	float x;
	float y;
	float z;
	float w;
};

struct quat
{
	float x;
	float y;
	float z;
	float w;
};

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
struct mat4
{
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;
};

struct f16v
{
	float v[ 16 ];
};

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * TYPE DEFINITIONS
 * -----------------------------
 */

typedef struct color color_t;
typedef struct line line_t;
typedef struct point point_t;
typedef struct triangle triangle_t;
typedef struct rectangle rectangle_t;
typedef struct circle circle_t;

typedef struct vec2 vec2_t;
typedef struct vec3 vec3_t;
typedef struct vec4 vec4_t;
typedef struct quat quat_t;
typedef struct mat4 mat4_t;

typedef struct f16v f16v_t;

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * INTERNAL
 * -----------------------------
 * Use this for internal functions instead of the typedefs.
 */

#define _COLOR		struct color
#define _LINE		struct line
#define _POINT		struct point
#define _TRIANGLE	struct triangle
#define _RECTANGLE	struct rectangle
#define _CIRCLE		struct circle

#define _VEC2		struct vec2
#define _VEC3 		struct vec3
#define _VEC4 		struct vec4
#define _QUAT 		struct quat
#define _MAT4 		struct mat4

#define _F16V		struct f16v

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * COLOR DEFINITIONS
 * -----------------------------
 */

static _COLOR BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };
static _COLOR WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };

/*
 * =============================
 */

#endif
