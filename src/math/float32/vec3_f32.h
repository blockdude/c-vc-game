#ifndef VEC3_F32_H
#define VEC3_F32_H

#include "../../util/types.h"
#include <math.h>

// Vector with components value 0.0f
static inline struct vec3_f32 vec3_f32_zero( void )
{
    struct vec3_f32 result = { 0.0f, 0.0f, 0.0f };
    return result;
}

// Vector with components value 1.0f
static inline struct vec3_f32 vec3_f32_one( void )
{
    struct vec3_f32 result = { 1.0f, 1.0f, 1.0f };
    return result;
}

// Add two vectors
static inline struct vec3_f32 vec3_f32_add( struct vec3_f32 a, struct vec3_f32 b )
{
    struct vec3_f32 result = { a.x + b.x, a.y + b.y, a.z + b.z };
    return result;
}

// Add vector and float value
static inline struct vec3_f32 vec3_f32_add_val( struct vec3_f32 v, float val )
{
    struct vec3_f32 result = { v.x + val, v.y + val, v.z + val };
    return result;
}

// Subtract two vectors
static inline struct vec3_f32 vec3_f32_sub( struct vec3_f32 a, struct vec3_f32 b )
{
    struct vec3_f32 result = { a.x - b.x, a.y - b.y, a.z - b.z };
    return result;
}

// Subtract vector by float value
static inline struct vec3_f32 vec3_f32_sub_val( struct vec3_f32 v, float val )
{
    struct vec3_f32 result = { v.x - val, v.y - val, v.z - val };
    return result;
}

// Multiply vector by scalar
static inline struct vec3_f32 vec3_f32_scale( struct vec3_f32 v, float scale )
{
    struct vec3_f32 result = { v.x * scale, v.y * scale, v.z * scale };
    return result;
}

// Multiply vector by vector
static inline struct vec3_f32 vec3_f32_mul( struct vec3_f32 a, struct vec3_f32 b )
{
    struct vec3_f32 result = { a.x * b.x, a.y * b.y, a.z * b.z };
    return result;
}

// Calculate two vectors cross product
static inline struct vec3_f32 vec3_f32_cross( struct vec3_f32 a, struct vec3_f32 b )
{
    struct vec3_f32 result = { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
    return result;
}

// Calculate one vector perpendicular vector
static inline struct vec3_f32 vec3_f32_perpendicular( struct vec3_f32 v )
{
    struct vec3_f32 result = { 0 };

    float min = fabsf( v.x );
    struct vec3_f32 cardinal_axis = { 1.0f, 0.0f, 0.0f };

    if ( fabsf( v.y ) < min )
    {
        min = fabsf( v.y );
        struct vec3_f32 tmp = { 0.0f, 1.0f, 0.0f };
        cardinal_axis = tmp;
    }

    if ( fabsf( v.z ) < min )
    {
        struct vec3_f32 tmp = { 0.0f, 0.0f, 1.0f };
        cardinal_axis = tmp;
    }

    // Cross product between vectors
    result.x = v.y * cardinal_axis.z - v.z * cardinal_axis.y;
    result.y = v.z * cardinal_axis.x - v.x * cardinal_axis.z;
    result.z = v.x * cardinal_axis.y - v.y * cardinal_axis.x;

    return result;
}

// Calcuate the center point of two vectors
static inline struct vec3_f32 vec3_f32_center( struct vec3_f32 a, struct vec3_f32 b )
{
    struct vec3_f32 result = { 0.0f };

    result.x = ( a.x + b.x ) / 2.0f;
    result.y = ( a.y + b.y ) / 2.0f;
    result.z = ( a.z + b.z ) / 2.0f;

    return result;
}

// Calculate vector length
static inline float vec3_f32_len( struct vec3_f32 v )
{
    float result = sqrtf( v.x * v.x + v.y * v.y + v.z * v.z );
    return result;
}

// Calculate vector square length
static inline float vec3_f32_len_sq( struct vec3_f32 v )
{
    float result = v.x * v.x + v.y * v.y + v.z * v.z;
    return result;
}

// Calculate two vectors dot product
static inline float vec3_f32_dot( struct vec3_f32 a, struct vec3_f32 b )
{
    float result = ( a.x * b.x + a.y * b.y + a.z * b.z );
    return result;
}

// Calculate distance between two vectors
static inline float vec3_f32_dist( struct vec3_f32 a, struct vec3_f32 b )
{
    float result = 0.0f;

    float dx = b.x - a.x;
    float dy = b.y - a.y;
    float dz = b.z - a.z;
    result = sqrtf( dx * dx + dy * dy + dz * dz );

    return result;
}

// Calculate square distance between two vectors
static inline float vec3_f32_dist_sq( struct vec3_f32 a, struct vec3_f32 b )
{
    float result = 0.0f;

    float dx = b.x - a.x;
    float dy = b.y - a.y;
    float dz = b.z - a.z;
    result = dx * dx + dy * dy + dz * dz;

    return result;
}

// Calculate angle between two vectors
static inline float vec3_f32_angle( struct vec3_f32 a, struct vec3_f32 b )
{
    float result = 0.0f;

    struct vec3_f32 cross = { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
    float len = sqrtf( cross.x * cross.x + cross.y * cross.y + cross.z * cross.z );
    float dot = ( a.x * b.x + a.y * b.y + a.z * b.z );
    result = atan2f( len, dot );

    return result;
}

// Negate provided vector (invert direction)
static inline struct vec3_f32 vec3_f32_negate( struct vec3_f32 v )
{
    struct vec3_f32 result = { -v.x, -v.y, -v.z };
    return result;
}

// Divide vector by vector
static inline struct vec3_f32 vec3_f32_div( struct vec3_f32 a, struct vec3_f32 b )
{
    struct vec3_f32 result = { a.x / b.x, a.y / b.y, a.z / b.z };
    return result;
}

// Normalize provided vector
static inline struct vec3_f32 vec3_f32_normalize( struct vec3_f32 v )
{
    struct vec3_f32 result = { 0 };

    float len = sqrtf( v.x * v.x + v.y * v.y + v.z * v.z );
    if ( len > 0.0f )
    {
        float ilen = 1.0f / len;
        result.x = v.x * ilen;
        result.y = v.y * ilen;
        result.z = v.z * ilen;
    }

    return result;
}

//Calculate the projection of the vector a on to b
static inline struct vec3_f32 vec3_f32_project( struct vec3_f32 a, struct vec3_f32 b )
{
    struct vec3_f32 result = { 0 };

    // a dot b . b dot b
    float adb = ( a.x * b.x + a.y * b.y + a.z * b.z );
    float bdb = ( b.x * b.x + b.y * b.y + b.z * b.z );

    float mag = adb / bdb;

    result.x = b.x * mag;
    result.y = b.y * mag;
    result.z = b.z * mag;

    return result;
}

//Calculate the rejection of the vector v1 on to v2
static inline struct vec3_f32 vec3_f32_reject( struct vec3_f32 a, struct vec3_f32 b )
{
    struct vec3_f32 result = { 0 };

    float adb = ( a.x * b.x + a.y * b.y + a.z * b.z );
    float bdb = ( b.x * b.x + b.y * b.y + b.z * b.z );

    float mag = adb / bdb;

    result.x = a.x - ( b.x * mag );
    result.y = a.y - ( b.y * mag );
    result.z = a.z - ( b.z * mag );

    return result;
}

// Orthonormalize provided vectors
// Makes vectors normalized and orthogonal to each other
// Gram-Schmidt function implementation
static inline void vec3_f32_ortho_normalize( struct vec3_f32 *a, struct vec3_f32 *b )
{
    float len = 0.0f;
    float ilen = 0.0f;

    // struct vec3_f32Normalize( *a );
    struct vec3_f32 v = *a;
    len = sqrtf( v.x * v.x + v.y * v.y + v.z * v.z );
    if ( len == 0.0f ) len = 1.0f;
    ilen = 1.0f / len;
    a->x *= ilen;
    a->y *= ilen;
    a->z *= ilen;

    // vec3_f32_cross( *a, *b )
    struct vec3_f32 an = { a->y * b->z - a->z * b->y, a->z * b->x - a->x * b->z, a->x * b->y - a->y * b->x };

    // vec3_f32_normalize( an );
    v = an;
    len = sqrtf( v.x * v.x + v.y * v.y + v.z * v.z );
    if ( len == 0.0f ) len = 1.0f;
    ilen = 1.0f / len;
    an.x *= ilen;
    an.y *= ilen;
    an.z *= ilen;

    // vec3_f32_cross( an, *a )
    struct vec3_f32 bn = { an.y * a->z - an.z * a->y, an.z * a->x - an.x * a->z, an.x * a->y - an.y * a->x };

    *b = bn;
}

// Transforms a struct vec3_f32 by a given Matrix
static inline struct vec3_f32 vec3_f32_transform( struct vec3_f32 v, struct mat4_f32 m )
{
    struct vec3_f32 result = { 0 };

    float x = v.x;
    float y = v.y;
    float z = v.z;

    result.x = m.m00 * x + m.m01 * y + m.m02 * z + m.m03;
    result.y = m.m10 * x + m.m11 * y + m.m12 * z + m.m13;
    result.z = m.m20 * x + m.m21 * y + m.m22 * z + m.m23;

    return result;
}

// Transform a vector by quaternion rotation
static inline struct vec3_f32 vec3_f32_rotate( struct vec3_f32 v, struct quat_f32 q )
{
    struct vec3_f32 result = { 0 };

    result.x = v.x * ( q.x * q.x + q.w * q.w - q.y * q.y - q.z * q.z ) + v.y * ( 2 * q.x * q.y - 2 * q.w * q.z ) + v.z * ( 2 * q.x * q.z + 2 * q.w * q.y );
    result.y = v.x * ( 2 * q.w * q.z + 2 * q.x * q.y ) + v.y * ( q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z ) + v.z * ( -2 * q.w * q.x + 2 * q.y * q.z );
    result.z = v.x * ( -2 * q.w * q.y + 2 * q.x * q.z ) + v.y * ( 2 * q.w * q.x + 2 * q.y * q.z ) + v.z * ( q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z );

    return result;
}

// Rotates a vector around an axis
static inline struct vec3_f32 vec3_f32_rotate_around_axis( struct vec3_f32 v, struct vec3_f32 axis, float angle )
{
    // Using Euler-Rodrigues Formula
    // Ref.: https://en.wikipedia.org/w/index.php?title=Euler%E2%80%93Rodrigues_formula

    struct vec3_f32 result = v;

    // vec3_f32_normalize(axis);
    float len = sqrtf( axis.x * axis.x + axis.y * axis.y + axis.z * axis.z );
    if ( len == 0.0f ) len = 1.0f;
    float ilen = 1.0f / len;
    axis.x *= ilen;
    axis.y *= ilen;
    axis.z *= ilen;

    angle /= 2.0f;
    float a = sinf( angle );
    float b = axis.x * a;
    float c = axis.y * a;
    float d = axis.z * a;
    a = cosf( angle );
    struct vec3_f32 w = { b, c, d };

    // vec3_f32_cross( w, v )
    struct vec3_f32 wv = { w.y * v.z - w.z * v.y, w.z * v.x - w.x * v.z, w.x * v.y - w.y * v.x };

    // vec3_f32_cross( w, wv )
    struct vec3_f32 wwv = { w.y * wv.z - w.z * wv.y, w.z * wv.x - w.x * wv.z, w.x * wv.y - w.y * wv.x };

    // vec3_f32_scale( wv, 2 * a )
    a *= 2;
    wv.x *= a;
    wv.y *= a;
    wv.z *= a;

    // vec3_f32_scale( wwv, 2 )
    wwv.x *= 2;
    wwv.y *= 2;
    wwv.z *= 2;

    result.x += wv.x;
    result.y += wv.y;
    result.z += wv.z;

    result.x += wwv.x;
    result.y += wwv.y;
    result.z += wwv.z;

    return result;
}

// Move Vector towards target
static inline struct vec3_f32 vec3_f32_move_towards( struct vec3_f32 v, struct vec3_f32 target, float max )
{
    struct vec3_f32 result = { 0 };

    float dx = target.x - v.x;
    float dy = target.y - v.y;
    float dz = target.z - v.z;
    float value = ( dx * dx ) + ( dy * dy ) + ( dz * dz );

    if ( ( value == 0 ) || ( ( max >= 0 ) && ( value <= max * max ) ) )
        return target;

    float dist = sqrtf( value );

    result.x = v.x + dx / dist * max;
    result.y = v.y + dy / dist * max;
    result.z = v.z + dz / dist * max;

    return result;
}

// Calculate linear interpolation between two vectors
static inline struct vec3_f32 vec3_f32_lerp( struct vec3_f32 a, struct vec3_f32 b, float t )
{
    struct vec3_f32 result = { 0 };

    result.x = a.x + t * ( b.x - a.x );
    result.y = a.y + t * ( b.y - a.y );
    result.z = a.z + t * ( b.z - a.z );

    return result;
}

// Calculate cubic hermite interpolation between two vectors and their tangents
// as described in the GLTF 2.0 specification: https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html#interpolation-cubic
static inline struct vec3_f32 vec3_f32_cubic_hermite( struct vec3_f32 a, struct vec3_f32 tan_a, struct vec3_f32 b, struct vec3_f32 tan_b, float t )
{
    struct vec3_f32 result = { 0 };

    float t2 = t * t;
    float t3 = t * t * t;

    result.x = ( 2 * t3 - 3 * t2 + 1 ) * a.x + ( t3 - 2 * t2 + t ) * tan_a.x + ( -2 * t3 + 3 * t2 ) * b.x + ( t3 - t2 ) * tan_b.x;
    result.y = ( 2 * t3 - 3 * t2 + 1 ) * a.y + ( t3 - 2 * t2 + t ) * tan_a.y + ( -2 * t3 + 3 * t2 ) * b.y + ( t3 - t2 ) * tan_b.y;
    result.z = ( 2 * t3 - 3 * t2 + 1 ) * a.z + ( t3 - 2 * t2 + t ) * tan_a.z + ( -2 * t3 + 3 * t2 ) * b.z + ( t3 - t2 ) * tan_b.z;

    return result;
}

// Calculate reflected vector to normal
static inline struct vec3_f32 vec3_f32_reflect( struct vec3_f32 v, struct vec3_f32 normal )
{
    struct vec3_f32 result = { 0 };

    // I is the original vector
    // N is the normal of the incident plane
    // R = I - (2*N*(DotProduct[I, N]))

    float dot = ( v.x * normal.x + v.y * normal.y + v.z * normal.z );

    result.x = v.x - ( 2.0f * normal.x ) * dot;
    result.y = v.y - ( 2.0f * normal.y ) * dot;
    result.z = v.z - ( 2.0f * normal.z ) * dot;

    return result;
}

// Get min value for each pair of components
static inline struct vec3_f32 vec3_f32_min( struct vec3_f32 a, struct vec3_f32 b )
{
    struct vec3_f32 result = { 0 };

    result.x = fminf( a.x, b.x );
    result.y = fminf( a.y, b.y );
    result.z = fminf( a.z, b.z );

    return result;
}

// Get max value for each pair of components
static inline struct vec3_f32 vec3_f32_max( struct vec3_f32 a, struct vec3_f32 b )
{
    struct vec3_f32 result = { 0 };

    result.x = fmaxf( a.x, b.x );
    result.y = fmaxf( a.y, b.y );
    result.z = fmaxf( a.z, b.z );

    return result;
}

// Compute barycenter coordinates (u, v, w) for point p with respect to triangle (a, b, c)
// NOTE: Assumes P is on the plane of the triangle
static inline struct vec3_f32 vec3_f32_barycenter( struct vec3_f32 p, struct vec3_f32 a, struct vec3_f32 b, struct vec3_f32 c )
{
    struct vec3_f32 result = { 0 };

    struct vec3_f32 v0 = { b.x - a.x, b.y - a.y, b.z - a.z };			// vec3_f32_sub(b, a)
    struct vec3_f32 v1 = { c.x - a.x, c.y - a.y, c.z - a.z };   			// vec3_f32_sub(c, a)
    struct vec3_f32 v2 = { p.x - a.x, p.y - a.y, p.z - a.z };   			// vec3_f32_sub(p, a)
    float d00 = ( v0.x * v0.x + v0.y * v0.y + v0.z * v0.z );    // vec3_f32_dot(v0, v0)
    float d01 = ( v0.x * v1.x + v0.y * v1.y + v0.z * v1.z );    // vec3_f32_dot(v0, v1)
    float d11 = ( v1.x * v1.x + v1.y * v1.y + v1.z * v1.z );    // vec3_f32_dot(v1, v1)
    float d20 = ( v2.x * v0.x + v2.y * v0.y + v2.z * v0.z );    // vec3_f32_dot(v2, v0)
    float d21 = ( v2.x * v1.x + v2.y * v1.y + v2.z * v1.z );    // vec3_f32_dot(v2, v1)

    float denom = d00 * d11 - d01 * d01;

    result.y = ( d11 * d20 - d01 * d21 ) / denom;
    result.z = ( d00 * d21 - d01 * d20 ) / denom;
    result.x = 1.0f - ( result.z + result.y );

    return result;
}

// Projects a struct vec3_f32 from screen space into object space
// NOTE: We are avoiding calling other raymath functions despite available
static inline struct vec3_f32 vec3_f32_unproject( struct vec3_f32 source, struct mat4_f32 proj, struct mat4_f32 view )
{
    struct vec3_f32 result = { 0 };

    // Calculate unprojected matrix (multiply view matrix by projection matrix) and invert it
    struct mat4_f32 view_proj = {      // MatrixMultiply(view, projection);
        view.m00 * proj.m00 + view.m10 * proj.m01 + view.m20 * proj.m02 + view.m30 * proj.m03,
        view.m00 * proj.m10 + view.m10 * proj.m11 + view.m20 * proj.m12 + view.m30 * proj.m13,
        view.m00 * proj.m20 + view.m10 * proj.m21 + view.m20 * proj.m22 + view.m30 * proj.m23,
        view.m00 * proj.m30 + view.m10 * proj.m31 + view.m20 * proj.m32 + view.m30 * proj.m33,
        view.m01 * proj.m00 + view.m11 * proj.m01 + view.m21 * proj.m02 + view.m31 * proj.m03,
        view.m01 * proj.m10 + view.m11 * proj.m11 + view.m21 * proj.m12 + view.m31 * proj.m13,
        view.m01 * proj.m20 + view.m11 * proj.m21 + view.m21 * proj.m22 + view.m31 * proj.m23,
        view.m01 * proj.m30 + view.m11 * proj.m31 + view.m21 * proj.m32 + view.m31 * proj.m33,
        view.m02 * proj.m00 + view.m12 * proj.m01 + view.m22 * proj.m02 + view.m32 * proj.m03,
        view.m02 * proj.m10 + view.m12 * proj.m11 + view.m22 * proj.m12 + view.m32 * proj.m13,
        view.m02 * proj.m20 + view.m12 * proj.m21 + view.m22 * proj.m22 + view.m32 * proj.m23,
        view.m02 * proj.m30 + view.m12 * proj.m31 + view.m22 * proj.m32 + view.m32 * proj.m33,
        view.m03 * proj.m00 + view.m13 * proj.m01 + view.m23 * proj.m02 + view.m33 * proj.m03,
        view.m03 * proj.m10 + view.m13 * proj.m11 + view.m23 * proj.m12 + view.m33 * proj.m13,
        view.m03 * proj.m20 + view.m13 * proj.m21 + view.m23 * proj.m22 + view.m33 * proj.m23,
        view.m03 * proj.m30 + view.m13 * proj.m31 + view.m23 * proj.m32 + view.m33 * proj.m33
    };

    // Calculate inverted matrix -> MatrixInvert(view_proj);
    // Cache the matrix values (speed optimization)
    float a00 = view_proj.m00, a01 = view_proj.m10, a02 = view_proj.m20, a03 = view_proj.m30;
    float a10 = view_proj.m01, a11 = view_proj.m11, a12 = view_proj.m21, a13 = view_proj.m31;
    float a20 = view_proj.m02, a21 = view_proj.m12, a22 = view_proj.m22, a23 = view_proj.m32;
    float a30 = view_proj.m03, a31 = view_proj.m13, a32 = view_proj.m23, a33 = view_proj.m33;

    float b00 = a00 * a11 - a01 * a10;
    float b01 = a00 * a12 - a02 * a10;
    float b02 = a00 * a13 - a03 * a10;
    float b03 = a01 * a12 - a02 * a11;
    float b04 = a01 * a13 - a03 * a11;
    float b05 = a02 * a13 - a03 * a12;
    float b06 = a20 * a31 - a21 * a30;
    float b07 = a20 * a32 - a22 * a30;
    float b08 = a20 * a33 - a23 * a30;
    float b09 = a21 * a32 - a22 * a31;
    float b10 = a21 * a33 - a23 * a31;
    float b11 = a22 * a33 - a23 * a32;

    // Calculate the invert determinant (inlined to avoid double-caching)
    float idet = 1.0f / ( b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06 );

    struct mat4_f32 view_proj_inv = {
        ( a11 * b11 - a12 * b10 + a13 * b09 ) * idet,
        ( -a01 * b11 + a02 * b10 - a03 * b09 ) * idet,
        ( a31 * b05 - a32 * b04 + a33 * b03 ) * idet,
        ( -a21 * b05 + a22 * b04 - a23 * b03 ) * idet,
        ( -a10 * b11 + a12 * b08 - a13 * b07 ) * idet,
        ( a00 * b11 - a02 * b08 + a03 * b07 ) * idet,
        ( -a30 * b05 + a32 * b02 - a33 * b01 ) * idet,
        ( a20 * b05 - a22 * b02 + a23 * b01 ) * idet,
        ( a10 * b10 - a11 * b08 + a13 * b06 ) * idet,
        ( -a00 * b10 + a01 * b08 - a03 * b06 ) * idet,
        ( a30 * b04 - a31 * b02 + a33 * b00 ) * idet,
        ( -a20 * b04 + a21 * b02 - a23 * b00 ) * idet,
        ( -a10 * b09 + a11 * b07 - a12 * b06 ) * idet,
        ( a00 * b09 - a01 * b07 + a02 * b06 ) * idet,
        ( -a30 * b03 + a31 * b01 - a32 * b00 ) * idet,
        ( a20 * b03 - a21 * b01 + a22 * b00 ) * idet
    };

    // Create quaternion from source point
    struct quat_f32 quat = { source.x, source.y, source.z, 1.0f };

    // Multiply quat point by unprojecte matrix
    struct quat_f32 qtransformed = {     // QuaternionTransform(quat, view_proj_inv)
        view_proj_inv.m00 * quat.x + view_proj_inv.m01 * quat.y + view_proj_inv.m02 * quat.z + view_proj_inv.m03 * quat.w,
        view_proj_inv.m10 * quat.x + view_proj_inv.m11 * quat.y + view_proj_inv.m12 * quat.z + view_proj_inv.m13 * quat.w,
        view_proj_inv.m20 * quat.x + view_proj_inv.m21 * quat.y + view_proj_inv.m22 * quat.z + view_proj_inv.m23 * quat.w,
        view_proj_inv.m30 * quat.x + view_proj_inv.m31 * quat.y + view_proj_inv.m32 * quat.z + view_proj_inv.m33 * quat.w };

    // Normalized world points in vectors
    result.x = qtransformed.x / qtransformed.w;
    result.y = qtransformed.y / qtransformed.w;
    result.z = qtransformed.z / qtransformed.w;

    return result;
}

// Invert the given vector
static inline struct vec3_f32 vec3_f32_invert( struct vec3_f32 v )
{
    struct vec3_f32 result = { 1.0f / v.x, 1.0f / v.y, 1.0f / v.z };
    return result;
}

// Clamp the components of the vector between
// min and max values specified by the given vectors
static inline struct vec3_f32 vec3_f32_clamp( struct vec3_f32 v, struct vec3_f32 min, struct vec3_f32 max )
{
    struct vec3_f32 result = { 0 };

    result.x = fminf( max.x, fmaxf( min.x, v.x ) );
    result.y = fminf( max.y, fmaxf( min.y, v.y ) );
    result.z = fminf( max.z, fmaxf( min.z, v.z ) );

    return result;
}

static inline struct vec3_f32 vec3_f32_clamp_val( struct vec3_f32 v, float min, float max )
{
    struct vec3_f32 result = { 0 };

    result.x = fminf( max, fmaxf( min, v.x ) );
    result.y = fminf( max, fmaxf( min, v.y ) );
    result.z = fminf( max, fmaxf( min, v.z ) );

    return result;
}

// Clamp the magnitude of the vector between two values
static inline struct vec3_f32 vec3_f32_clamp_len( struct vec3_f32 v, float min, float max )
{
    struct vec3_f32 result = v;

    float len = ( v.x * v.x ) + ( v.y * v.y ) + ( v.z * v.z );
    if ( len > 0.0f )
    {
        len = sqrtf( len );

        float scale = 1;    // By default, 1 as the neutral element.
        if ( len < min )
        {
            scale = min / len;
        }
        else if ( len > max )
        {
            scale = max / len;
        }

        result.x = v.x * scale;
        result.y = v.y * scale;
        result.z = v.z * scale;
    }

    return result;
}

// Check whether two given vectors are almost equal
static inline int vec3_f32_equals( struct vec3_f32 p, struct vec3_f32 q, float epsilon )
{
    int result =
        ( ( fabsf( p.x - q.x ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.x ), fabsf( q.x ) ) ) ) ) &&
        ( ( fabsf( p.y - q.y ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.y ), fabsf( q.y ) ) ) ) ) &&
        ( ( fabsf( p.z - q.z ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.z ), fabsf( q.z ) ) ) ) );

    return result;
}

// Compute the direction of a refracted ray
// v: normalized direction of the incoming ray
// n: normalized normal vector of the interface of two optical media
// r: ratio of the refractive index of the medium from where the ray comes
//    to the refractive index of the medium on the other side of the surface
static inline struct vec3_f32 vec3_f32_refract( struct vec3_f32 v, struct vec3_f32 n, float r )
{
    struct vec3_f32 result = { 0 };

    float dot = v.x * n.x + v.y * n.y + v.z * n.z;
    float d = 1.0f - r * r * ( 1.0f - dot * dot );

    if ( d >= 0.0f )
    {
        d = sqrtf( d );
        v.x = r * v.x - ( r * dot + d ) * n.x;
        v.y = r * v.y - ( r * dot + d ) * n.y;
        v.z = r * v.z - ( r * dot + d ) * n.z;

        result = v;
    }

    return result;
}

#endif