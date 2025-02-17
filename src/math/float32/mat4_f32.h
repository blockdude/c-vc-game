#ifndef MAT4_F32_H
#define MAT4_F32_H

#include "../../util/types.h"
#include "../math.h"
#include "quat_f32.h"
#include "vec3_f32.h"
#include <math.h>

// Compute matrix determinant
static inline float mat4_f32_det( struct mat4_f32 m )
{
    float result = 0.0f;

    // Cache the matrix values (speed optimization)
    float a00 = m.m00, a01 = m.m10, a02 = m.m20, a03 = m.m30;
    float a10 = m.m01, a11 = m.m11, a12 = m.m21, a13 = m.m31;
    float a20 = m.m02, a21 = m.m12, a22 = m.m22, a23 = m.m32;
    float a30 = m.m03, a31 = m.m13, a32 = m.m23, a33 = m.m33;

    result =
        a30 * a21 * a12 * a03 - a20 * a31 * a12 * a03 - a30 * a11 * a22 * a03 + a10 * a31 * a22 * a03 +
        a20 * a11 * a32 * a03 - a10 * a21 * a32 * a03 - a30 * a21 * a02 * a13 + a20 * a31 * a02 * a13 +
        a30 * a01 * a22 * a13 - a00 * a31 * a22 * a13 - a20 * a01 * a32 * a13 + a00 * a21 * a32 * a13 +
        a30 * a11 * a02 * a23 - a10 * a31 * a02 * a23 - a30 * a01 * a12 * a23 + a00 * a31 * a12 * a23 +
        a10 * a01 * a32 * a23 - a00 * a11 * a32 * a23 - a20 * a11 * a02 * a33 + a10 * a21 * a02 * a33 +
        a20 * a01 * a12 * a33 - a00 * a21 * a12 * a33 - a10 * a01 * a22 * a33 + a00 * a11 * a22 * a33;

    return result;
}

// Get the trace of the matrix (sum of the values along the diagonal)
static inline float mat4_f32_trace( struct mat4_f32 m )
{
    float result = ( m.m00 + m.m11 + m.m22 + m.m33 );
    return result;
}

// Transposes provided matrix
static inline struct mat4_f32 mat4_f32_transpose( struct mat4_f32 m )
{
    struct mat4_f32 result = { 0 };

    result.m00 = m.m00;
    result.m10 = m.m01;
    result.m20 = m.m02;
    result.m30 = m.m03;
    result.m01 = m.m10;
    result.m11 = m.m11;
    result.m21 = m.m12;
    result.m31 = m.m13;
    result.m02 = m.m20;
    result.m12 = m.m21;
    result.m22 = m.m22;
    result.m32 = m.m23;
    result.m03 = m.m30;
    result.m13 = m.m31;
    result.m23 = m.m32;
    result.m33 = m.m33;

    return result;
}

// Invert provided matrix
static inline struct mat4_f32 mat4_f32_invert( struct mat4_f32 m )
{
    struct mat4_f32 result = { 0 };

    // Cache the matrix values (speed optimization)
    float a00 = m.m00, a01 = m.m10, a02 = m.m20, a03 = m.m30;
    float a10 = m.m01, a11 = m.m11, a12 = m.m21, a13 = m.m31;
    float a20 = m.m02, a21 = m.m12, a22 = m.m22, a23 = m.m32;
    float a30 = m.m03, a31 = m.m13, a32 = m.m23, a33 = m.m33;

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

    result.m00 = ( a11 * b11 - a12 * b10 + a13 * b09 ) * idet;
    result.m10 = ( -a01 * b11 + a02 * b10 - a03 * b09 ) * idet;
    result.m20 = ( a31 * b05 - a32 * b04 + a33 * b03 ) * idet;
    result.m30 = ( -a21 * b05 + a22 * b04 - a23 * b03 ) * idet;
    result.m01 = ( -a10 * b11 + a12 * b08 - a13 * b07 ) * idet;
    result.m11 = ( a00 * b11 - a02 * b08 + a03 * b07 ) * idet;
    result.m21 = ( -a30 * b05 + a32 * b02 - a33 * b01 ) * idet;
    result.m31 = ( a20 * b05 - a22 * b02 + a23 * b01 ) * idet;
    result.m02 = ( a10 * b10 - a11 * b08 + a13 * b06 ) * idet;
    result.m12 = ( -a00 * b10 + a01 * b08 - a03 * b06 ) * idet;
    result.m22 = ( a30 * b04 - a31 * b02 + a33 * b00 ) * idet;
    result.m32 = ( -a20 * b04 + a21 * b02 - a23 * b00 ) * idet;
    result.m03 = ( -a10 * b09 + a11 * b07 - a12 * b06 ) * idet;
    result.m13 = ( a00 * b09 - a01 * b07 + a02 * b06 ) * idet;
    result.m23 = ( -a30 * b03 + a31 * b01 - a32 * b00 ) * idet;
    result.m33 = ( a20 * b03 - a21 * b01 + a22 * b00 ) * idet;

    return result;
}

// Get identity matrix
static inline struct mat4_f32 mat4_f32_identity( void )
{
    struct mat4_f32 result = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    return result;
}

// Add two matrices
static inline struct mat4_f32 mat4_f32_add( struct mat4_f32 a, struct mat4_f32 b )
{
    struct mat4_f32 result = { 0 };

    result.m00 = a.m00 + b.m00;
    result.m10 = a.m10 + b.m10;
    result.m20 = a.m20 + b.m20;
    result.m30 = a.m30 + b.m30;
    result.m01 = a.m01 + b.m01;
    result.m11 = a.m11 + b.m11;
    result.m21 = a.m21 + b.m21;
    result.m31 = a.m31 + b.m31;
    result.m02 = a.m02 + b.m02;
    result.m12 = a.m12 + b.m12;
    result.m22 = a.m22 + b.m22;
    result.m32 = a.m32 + b.m32;
    result.m03 = a.m03 + b.m03;
    result.m13 = a.m13 + b.m13;
    result.m23 = a.m23 + b.m23;
    result.m33 = a.m33 + b.m33;

    return result;
}

// Subtract two matrices (left - right)
// a - left matrix
// b - right matrix
static inline struct mat4_f32 mat4_f32_sub( struct mat4_f32 a, struct mat4_f32 b )
{
    struct mat4_f32 result = { 0 };

    result.m00 = a.m00 - b.m00;
    result.m10 = a.m10 - b.m10;
    result.m20 = a.m20 - b.m20;
    result.m30 = a.m30 - b.m30;
    result.m01 = a.m01 - b.m01;
    result.m11 = a.m11 - b.m11;
    result.m21 = a.m21 - b.m21;
    result.m31 = a.m31 - b.m31;
    result.m02 = a.m02 - b.m02;
    result.m12 = a.m12 - b.m12;
    result.m22 = a.m22 - b.m22;
    result.m32 = a.m32 - b.m32;
    result.m03 = a.m03 - b.m03;
    result.m13 = a.m13 - b.m13;
    result.m23 = a.m23 - b.m23;
    result.m33 = a.m33 - b.m33;

    return result;
}

// Get two matrix multiplication
// NOTE: When multiplying matrices... the order matters!
static inline struct mat4_f32 mat4_f32_mul( struct mat4_f32 a, struct mat4_f32 b )
{
    struct mat4_f32 result = { 0 };

    result.m00 = a.m00 * b.m00 + a.m10 * b.m01 + a.m20 * b.m02 + a.m30 * b.m03;
    result.m10 = a.m00 * b.m10 + a.m10 * b.m11 + a.m20 * b.m12 + a.m30 * b.m13;
    result.m20 = a.m00 * b.m20 + a.m10 * b.m21 + a.m20 * b.m22 + a.m30 * b.m23;
    result.m30 = a.m00 * b.m30 + a.m10 * b.m31 + a.m20 * b.m32 + a.m30 * b.m33;
    result.m01 = a.m01 * b.m00 + a.m11 * b.m01 + a.m21 * b.m02 + a.m31 * b.m03;
    result.m11 = a.m01 * b.m10 + a.m11 * b.m11 + a.m21 * b.m12 + a.m31 * b.m13;
    result.m21 = a.m01 * b.m20 + a.m11 * b.m21 + a.m21 * b.m22 + a.m31 * b.m23;
    result.m31 = a.m01 * b.m30 + a.m11 * b.m31 + a.m21 * b.m32 + a.m31 * b.m33;
    result.m02 = a.m02 * b.m00 + a.m12 * b.m01 + a.m22 * b.m02 + a.m32 * b.m03;
    result.m12 = a.m02 * b.m10 + a.m12 * b.m11 + a.m22 * b.m12 + a.m32 * b.m13;
    result.m22 = a.m02 * b.m20 + a.m12 * b.m21 + a.m22 * b.m22 + a.m32 * b.m23;
    result.m32 = a.m02 * b.m30 + a.m12 * b.m31 + a.m22 * b.m32 + a.m32 * b.m33;
    result.m03 = a.m03 * b.m00 + a.m13 * b.m01 + a.m23 * b.m02 + a.m33 * b.m03;
    result.m13 = a.m03 * b.m10 + a.m13 * b.m11 + a.m23 * b.m12 + a.m33 * b.m13;
    result.m23 = a.m03 * b.m20 + a.m13 * b.m21 + a.m23 * b.m22 + a.m33 * b.m23;
    result.m33 = a.m03 * b.m30 + a.m13 * b.m31 + a.m23 * b.m32 + a.m33 * b.m33;

    return result;
}

// Get translation matrix
static inline struct mat4_f32 mat4_f32_translate( struct vec3_f32 v )
{
    struct mat4_f32 result = {
        1.0f, 0.0f, 0.0f, v.x,
        0.0f, 1.0f, 0.0f, v.y,
        0.0f, 0.0f, 1.0f, v.z,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    return result;
}

// Create rotation matrix from axis and angle
// NOTE: Angle should be provided in radians
static inline struct mat4_f32 mat4_f32_rotate( struct vec3_f32 axis, float angle )
{
    struct mat4_f32 result = { 0 };

    float x = axis.x, y = axis.y, z = axis.z;
    float len = x * x + y * y + z * z;

    if ( ( len != 1.0f ) && ( len != 0.0f ) )
    {
        float ilen = 1.0f / sqrtf( len );
        x *= ilen;
        y *= ilen;
        z *= ilen;
    }

    float sin = sinf( angle );
    float cos = cosf( angle );
    float t = 1.0f - cos;

    result.m00 = x * x * t + cos;
    result.m10 = y * x * t + z * sin;
    result.m20 = z * x * t - y * sin;
    result.m30 = 0.0f;

    result.m01 = x * y * t - z * sin;
    result.m11 = y * y * t + cos;
    result.m21 = z * y * t + x * sin;
    result.m31 = 0.0f;

    result.m02 = x * z * t + y * sin;
    result.m12 = y * z * t - x * sin;
    result.m22 = z * z * t + cos;
    result.m32 = 0.0f;

    result.m03 = 0.0f;
    result.m13 = 0.0f;
    result.m23 = 0.0f;
    result.m33 = 1.0f;

    return result;
}

// Get x-rotation matrix
// NOTE: Angle must be provided in radians
static inline struct mat4_f32 mat4_f32_rotate_x( float angle )
{
    struct mat4_f32 result = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    }; // MatrixIdentity()

    float cos = cosf( angle );
    float sin = sinf( angle );

    result.m11 = cos;
    result.m21 = sin;
    result.m12 = -sin;
    result.m22 = cos;

    return result;
}

// Get y-rotation matrix
// NOTE: Angle must be provided in radians
static inline struct mat4_f32 mat4_f32_rotate_y( float angle )
{
    struct mat4_f32 result = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    }; // MatrixIdentity()

    float cos = cosf( angle );
    float sin = sinf( angle );

    result.m00 = cos;
    result.m20 = -sin;
    result.m02 = sin;
    result.m22 = cos;

    return result;
}

// Get z-rotation matrix
// NOTE: Angle must be provided in radians
static inline struct mat4_f32 mat4_f32_rotate_z( float angle )
{
    struct mat4_f32 result = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    }; // MatrixIdentity()

    float cos = cosf( angle );
    float sin = sinf( angle );

    result.m00 = cos;
    result.m10 = sin;
    result.m01 = -sin;
    result.m11 = cos;

    return result;
}


// Get xyz-rotation matrix
// NOTE: Angle must be provided in radians
static inline struct mat4_f32 mat4_f32_rotate_xyz( struct vec3_f32 angle )
{
    struct mat4_f32 result = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    }; // MatrixIdentity()

    float cosz = cosf( -angle.z );
    float sinz = sinf( -angle.z );
    float cosy = cosf( -angle.y );
    float siny = sinf( -angle.y );
    float cosx = cosf( -angle.x );
    float sinx = sinf( -angle.x );

    result.m00 = cosz * cosy;
    result.m10 = ( cosz * siny * sinx ) - ( sinz * cosx );
    result.m20 = ( cosz * siny * cosx ) + ( sinz * sinx );

    result.m01 = sinz * cosy;
    result.m11 = ( sinz * siny * sinx ) + ( cosz * cosx );
    result.m21 = ( sinz * siny * cosx ) - ( cosz * sinx );

    result.m02 = -siny;
    result.m12 = cosy * sinx;
    result.m22 = cosy * cosx;

    return result;
}

// Get zyx-rotation matrix
// NOTE: Angle must be provided in radians
static inline struct mat4_f32 mat4_f32_rotate_zyx( struct vec3_f32 angle )
{
    struct mat4_f32 result = { 0 };

    float cosz = cosf( angle.z );
    float sinz = sinf( angle.z );
    float cosy = cosf( angle.y );
    float siny = sinf( angle.y );
    float cosx = cosf( angle.x );
    float sinx = sinf( angle.x );

    result.m00 = cosz * cosy;
    result.m01 = cosz * siny * sinx - cosx * sinz;
    result.m02 = sinz * sinx + cosz * cosx * siny;
    result.m03 = 0.0f;

    result.m10 = cosy * sinz;
    result.m11 = cosz * cosx + sinz * siny * sinx;
    result.m12 = cosx * sinz * siny - cosz * sinx;
    result.m13 = 0.0f;

    result.m20 = -siny;
    result.m21 = cosy * sinx;
    result.m22 = cosy * cosx;
    result.m23 = 0.0f;

    result.m30 = 0.0f;
    result.m31 = 0.0f;
    result.m32 = 0.0f;
    result.m33 = 1.0f;

    return result;
}

// Get scaling matrix
static inline struct mat4_f32 mat4_f32_scale( struct vec3_f32 v )
{
    struct mat4_f32 result = {
        v.x, 0.0f, 0.0f, 0.0f,
        0.0f, v.y, 0.0f, 0.0f,
        0.0f, 0.0f, v.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    return result;
}

// Get perspective projection matrix
static inline struct mat4_f32 mat4_f32_frustum( float left, float right, float bottom, float top, float near, float far )
{
    struct mat4_f32 result = { 0 };

    float rl = right - left;
    float tb = top - bottom;
    float fn = far - near;

    result.m00 = ( near * 2.0f ) / rl;
    result.m10 = 0.0f;
    result.m20 = 0.0f;
    result.m30 = 0.0f;

    result.m01 = 0.0f;
    result.m11 = ( near * 2.0f ) / tb;
    result.m21 = 0.0f;
    result.m31 = 0.0f;

    result.m02 = ( right + left ) / rl;
    result.m12 = ( top + bottom ) / tb;
    result.m22 = -( far + near ) / fn;
    result.m32 = -1.0f;

    result.m03 = 0.0f;
    result.m13 = 0.0f;
    result.m23 = -( far * near * 2.0f ) / fn;
    result.m33 = 0.0f;

    return result;
}

// Get perspective projection matrix
// NOTE: Fovy angle must be provided in radians
static inline struct mat4_f32 mat4_f32_perspective( float fovy, float aspect, float near, float far )
{
    struct mat4_f32 result = { 0 };

    float top = near * tan( fovy * 0.5 );
    float bottom = -top;
    float right = top * aspect;
    float left = -right;

    // MatrixFrustum( -right, right, -top, top, near, far );
    float rl = right - left;
    float tb = top - bottom;
    float fn = far - near;

    result.m00 = ( near * 2.0f ) / rl;
    result.m11 = ( near * 2.0f ) / tb;
    result.m02 = ( right + left ) / rl;
    result.m12 = ( top + bottom ) / tb;
    result.m22 = -( far + near ) / fn;
    result.m32 = -1.0f;
    result.m23 = -( far * near * 2.0f ) / fn;

    return result;
}

// Get orthographic projection matrix
static inline struct mat4_f32 mat4_f32_ortho( float left, float right, float bottom, float top, float near, float far )
{
    struct mat4_f32 result = { 0 };

    float rl = right - left;
    float tb = top - bottom;
    float fn = far - near;

    result.m00 = 2.0f / rl;
    result.m10 = 0.0f;
    result.m20 = 0.0f;
    result.m30 = 0.0f;
    result.m01 = 0.0f;
    result.m11 = 2.0f / tb;
    result.m21 = 0.0f;
    result.m31 = 0.0f;
    result.m02 = 0.0f;
    result.m12 = 0.0f;
    result.m22 = -2.0f / fn;
    result.m32 = 0.0f;
    result.m03 = -( left + right ) / rl;
    result.m13 = -( top + bottom ) / tb;
    result.m23 = -( far + near ) / fn;
    result.m33 = 1.0f;

    return result;
}

// Get camera look-at matrix (view matrix)
static inline struct mat4_f32 mat4_f32_lookat( struct vec3_f32 eye, struct vec3_f32 target, struct vec3_f32 up )
{
    struct mat4_f32 result = { 0 };

    float len = 0.0f;
    float ilen = 0.0f;

    // Vector3Subtract( eye, target )
    struct vec3_f32 vz = { eye.x - target.x, eye.y - target.y, eye.z - target.z };

    // Vector3Normalize( vz )
    struct vec3_f32 v = vz;
    len = sqrtf( v.x * v.x + v.y * v.y + v.z * v.z );
    if ( len == 0.0f ) len = 1.0f;
    ilen = 1.0f / len;
    vz.x *= ilen;
    vz.y *= ilen;
    vz.z *= ilen;

    // Vector3CrossProduct( up, vz )
    struct vec3_f32 vx = { up.y * vz.z - up.z * vz.y, up.z * vz.x - up.x * vz.z, up.x * vz.y - up.y * vz.x };

    // Vector3Normalize( x )
    v = vx;
    len = sqrtf( v.x * v.x + v.y * v.y + v.z * v.z );
    if ( len == 0.0f ) len = 1.0f;
    ilen = 1.0f / len;
    vx.x *= ilen;
    vx.y *= ilen;
    vx.z *= ilen;

    // Vector3CrossProduct( vz, vx )
    struct vec3_f32 vy = { vz.y * vx.z - vz.z * vx.y, vz.z * vx.x - vz.x * vx.z, vz.x * vx.y - vz.y * vx.x };

    result.m00 = vx.x;
    result.m10 = vy.x;
    result.m20 = vz.x;
    result.m30 = 0.0f;
    result.m01 = vx.y;
    result.m11 = vy.y;
    result.m21 = vz.y;
    result.m31 = 0.0f;
    result.m02 = vx.z;
    result.m12 = vy.z;
    result.m22 = vz.z;
    result.m32 = 0.0f;
    result.m03 = -( vx.x * eye.x + vx.y * eye.y + vx.z * eye.z );   // Vector3DotProduct( vx, eye )
    result.m13 = -( vy.x * eye.x + vy.y * eye.y + vy.z * eye.z );   // Vector3DotProduct( vy, eye )
    result.m23 = -( vz.x * eye.x + vz.y * eye.y + vz.z * eye.z );   // Vector3DotProduct( vz, eye )
    result.m33 = 1.0f;

    return result;
}

// Get float array of matrix data. convert matrix to a flat array
static inline struct mat4_f32_flat mat4_f32_flatten( struct mat4_f32 m )
{
    struct mat4_f32_flat result = { 0 };

    result.m[ 0 ] = m.m00;
    result.m[ 1 ] = m.m10;
    result.m[ 2 ] = m.m20;
    result.m[ 3 ] = m.m30;

    result.m[ 4 ] = m.m01;
    result.m[ 5 ] = m.m11;
    result.m[ 6 ] = m.m21;
    result.m[ 7 ] = m.m31;

    result.m[ 8 ] = m.m02;
    result.m[ 9 ] = m.m12;
    result.m[ 10 ] = m.m22;
    result.m[ 11 ] = m.m32;

    result.m[ 12 ] = m.m03;
    result.m[ 13 ] = m.m13;
    result.m[ 14 ] = m.m23;
    result.m[ 15 ] = m.m33;

    return result;
}

// Decompose a transformation matrix into its rotational, translational and scaling components
static inline void mat4_f32_decompose( struct mat4_f32 m, struct vec3_f32 *translation, struct quat_f32 *rotation, struct vec3_f32 *scale )
{
    // Extract translation.
    translation->x = m.m03;
    translation->y = m.m13;
    translation->z = m.m23;

    // Extract upper-left for determinant computation
    const float a = m.m00;
    const float b = m.m01;
    const float c = m.m02;
    const float d = m.m10;
    const float e = m.m11;
    const float f = m.m12;
    const float g = m.m20;
    const float h = m.m21;
    const float i = m.m22;
    const float A = e * i - f * h;
    const float B = f * g - d * i;
    const float C = d * h - e * g;

    // Extract scale
    const float det = a * A + b * B + c * C;
    struct vec3_f32 abc = { a, b, c };
    struct vec3_f32 def = { d, e, f };
    struct vec3_f32 ghi = { g, h, i };

    float scalex = vec3_f32_len( abc );
    float scaley = vec3_f32_len( def );
    float scalez = vec3_f32_len( ghi );
    struct vec3_f32 s = { scalex, scaley, scalez };

    if ( det < 0 ) s = vec3_f32_negate( s );

    *scale = s;

    // Remove scale from the matrix if it is not close to zero
    struct mat4_f32 clone = m;
    if ( !f32_equals( det, 0, EPSILON ) )
    {
        clone.m00 /= s.x;
        clone.m11 /= s.y;
        clone.m22 /= s.z;

        // Extract rotation
        *rotation = quat_f32_from_mat4_f32( clone );
    }
    else
    {
        // Set to identity if close to zero
        *rotation = quat_f32_identity();
    }
}

#endif