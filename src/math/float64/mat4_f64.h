#ifndef MAT4_F64_H
#define MAT4_F64_H

#include "../../util/types.h"
#include "../math.h"
#include "quat_f64.h"
#include "vec3_f64.h"
#include <math.h>

// Compute matrix determinant
static inline double mat4_f64_det( struct mat4_f64 m )
{
    double result = 0.0f;

    // Cache the matrix values (speed optimization)
    double a00 = m.m00, a01 = m.m10, a02 = m.m20, a03 = m.m30;
    double a10 = m.m01, a11 = m.m11, a12 = m.m21, a13 = m.m31;
    double a20 = m.m02, a21 = m.m12, a22 = m.m22, a23 = m.m32;
    double a30 = m.m03, a31 = m.m13, a32 = m.m23, a33 = m.m33;

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
static inline double mat4_f64_trace( struct mat4_f64 m )
{
    double result = ( m.m00 + m.m11 + m.m22 + m.m33 );
    return result;
}

// Transposes provided matrix
static inline struct mat4_f64 mat4_f64_transpose( struct mat4_f64 m )
{
    struct mat4_f64 result = { 0 };

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
static inline struct mat4_f64 mat4_f64_invert( struct mat4_f64 m )
{
    struct mat4_f64 result = { 0 };

    // Cache the matrix values (speed optimization)
    double a00 = m.m00, a01 = m.m10, a02 = m.m20, a03 = m.m30;
    double a10 = m.m01, a11 = m.m11, a12 = m.m21, a13 = m.m31;
    double a20 = m.m02, a21 = m.m12, a22 = m.m22, a23 = m.m32;
    double a30 = m.m03, a31 = m.m13, a32 = m.m23, a33 = m.m33;

    double b00 = a00 * a11 - a01 * a10;
    double b01 = a00 * a12 - a02 * a10;
    double b02 = a00 * a13 - a03 * a10;
    double b03 = a01 * a12 - a02 * a11;
    double b04 = a01 * a13 - a03 * a11;
    double b05 = a02 * a13 - a03 * a12;
    double b06 = a20 * a31 - a21 * a30;
    double b07 = a20 * a32 - a22 * a30;
    double b08 = a20 * a33 - a23 * a30;
    double b09 = a21 * a32 - a22 * a31;
    double b10 = a21 * a33 - a23 * a31;
    double b11 = a22 * a33 - a23 * a32;

    // Calculate the invert determinant (inlined to avoid double-caching)
    double idet = 1.0f / ( b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06 );

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
static inline struct mat4_f64 mat4_f64_identity( void )
{
    struct mat4_f64 result = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    return result;
}

// Add two matrices
static inline struct mat4_f64 mat4_f64_add( struct mat4_f64 a, struct mat4_f64 b )
{
    struct mat4_f64 result = { 0 };

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
static inline struct mat4_f64 mat4_f64_sub( struct mat4_f64 a, struct mat4_f64 b )
{
    struct mat4_f64 result = { 0 };

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
static inline struct mat4_f64 mat4_f64_mul( struct mat4_f64 a, struct mat4_f64 b )
{
    struct mat4_f64 result = { 0 };

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
static inline struct mat4_f64 mat4_f64_translate( struct vec3_f64 v )
{
    struct mat4_f64 result = {
        1.0f, 0.0f, 0.0f, v.x,
        0.0f, 1.0f, 0.0f, v.y,
        0.0f, 0.0f, 1.0f, v.z,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    return result;
}

// Create rotation matrix from axis and angle
// NOTE: Angle should be provided in radians
static inline struct mat4_f64 mat4_f64_rotate( struct vec3_f64 axis, double angle )
{
    struct mat4_f64 result = { 0 };

    double x = axis.x, y = axis.y, z = axis.z;
    double len = x * x + y * y + z * z;

    if ( ( len != 1.0f ) && ( len != 0.0f ) )
    {
        double ilen = 1.0f / sqrt( len );
        x *= ilen;
        y *= ilen;
        z *= ilen;
    }

    double s = sin( angle );
    double c = cos( angle );
    double t = 1.0f - c;

    result.m00 = x * x * t + c;
    result.m10 = y * x * t + z * s;
    result.m20 = z * x * t - y * s;
    result.m30 = 0.0f;

    result.m01 = x * y * t - z * s;
    result.m11 = y * y * t + c;
    result.m21 = z * y * t + x * s;
    result.m31 = 0.0f;

    result.m02 = x * z * t + y * s;
    result.m12 = y * z * t - x * s;
    result.m22 = z * z * t + c;
    result.m32 = 0.0f;

    result.m03 = 0.0f;
    result.m13 = 0.0f;
    result.m23 = 0.0f;
    result.m33 = 1.0f;

    return result;
}

// Get x-rotation matrix
// NOTE: Angle must be provided in radians
static inline struct mat4_f64 mat4_f64_rotate_x( double angle )
{
    struct mat4_f64 result = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    }; // MatrixIdentity()

    double c = cos( angle );
    double s = sin( angle );

    result.m11 = c;
    result.m21 = s;
    result.m12 = -s;
    result.m22 = c;

    return result;
}

// Get y-rotation matrix
// NOTE: Angle must be provided in radians
static inline struct mat4_f64 mat4_f64_rotate_y( double angle )
{
    struct mat4_f64 result = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    }; // MatrixIdentity()

    double c = cos( angle );
    double s = sin( angle );

    result.m00 = c;
    result.m20 = -s;
    result.m02 = s;
    result.m22 = c;

    return result;
}

// Get z-rotation matrix
// NOTE: Angle must be provided in radians
static inline struct mat4_f64 mat4_f64_rotate_z( double angle )
{
    struct mat4_f64 result = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    }; // MatrixIdentity()

    double c = cos( angle );
    double s = sin( angle );

    result.m00 = c;
    result.m10 = s;
    result.m01 = -s;
    result.m11 = c;

    return result;
}


// Get xyz-rotation matrix
// NOTE: Angle must be provided in radians
static inline struct mat4_f64 mat4_f64_rotate_xyz( struct vec3_f64 angle )
{
    struct mat4_f64 result = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    }; // MatrixIdentity()

    double cosz = cos( -angle.z );
    double sinz = sin( -angle.z );
    double cosy = cos( -angle.y );
    double siny = sin( -angle.y );
    double cosx = cos( -angle.x );
    double sinx = sin( -angle.x );

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
static inline struct mat4_f64 mat4_f64_rotate_zyx( struct vec3_f64 angle )
{
    struct mat4_f64 result = { 0 };

    double cosz = cos( angle.z );
    double sinz = sin( angle.z );
    double cosy = cos( angle.y );
    double siny = sin( angle.y );
    double cosx = cos( angle.x );
    double sinx = sin( angle.x );

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
static inline struct mat4_f64 mat4_f64_scale( struct vec3_f64 v )
{
    struct mat4_f64 result = {
        v.x, 0.0f, 0.0f, 0.0f,
        0.0f, v.y, 0.0f, 0.0f,
        0.0f, 0.0f, v.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    return result;
}

// Get perspective projection matrix
static inline struct mat4_f64 mat4_f64_frustum( double left, double right, double bottom, double top, double near, double far )
{
    struct mat4_f64 result = { 0 };

    double rl = right - left;
    double tb = top - bottom;
    double fn = far - near;

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
static inline struct mat4_f64 mat4_f64_perspective( double fovy, double aspect, double near, double far )
{
    struct mat4_f64 result = { 0 };

    double top = near * tan( fovy * 0.5 );
    double bottom = -top;
    double right = top * aspect;
    double left = -right;

    // MatrixFrustum( -right, right, -top, top, near, far );
    double rl = right - left;
    double tb = top - bottom;
    double fn = far - near;

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
static inline struct mat4_f64 mat4_f64_ortho( double left, double right, double bottom, double top, double near, double far )
{
    struct mat4_f64 result = { 0 };

    double rl = right - left;
    double tb = top - bottom;
    double fn = far - near;

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
static inline struct mat4_f64 mat4_f64_lookat( struct vec3_f64 eye, struct vec3_f64 target, struct vec3_f64 up )
{
    struct mat4_f64 result = { 0 };

    double len = 0.0f;
    double ilen = 0.0f;

    // Vector3Subtract( eye, target )
    struct vec3_f64 vz = { eye.x - target.x, eye.y - target.y, eye.z - target.z };

    // Vector3Normalize( vz )
    struct vec3_f64 v = vz;
    len = sqrt( v.x * v.x + v.y * v.y + v.z * v.z );
    if ( len == 0.0f ) len = 1.0f;
    ilen = 1.0f / len;
    vz.x *= ilen;
    vz.y *= ilen;
    vz.z *= ilen;

    // Vector3CrossProduct( up, vz )
    struct vec3_f64 vx = { up.y * vz.z - up.z * vz.y, up.z * vz.x - up.x * vz.z, up.x * vz.y - up.y * vz.x };

    // Vector3Normalize( x )
    v = vx;
    len = sqrt( v.x * v.x + v.y * v.y + v.z * v.z );
    if ( len == 0.0f ) len = 1.0f;
    ilen = 1.0f / len;
    vx.x *= ilen;
    vx.y *= ilen;
    vx.z *= ilen;

    // Vector3CrossProduct( vz, vx )
    struct vec3_f64 vy = { vz.y * vx.z - vz.z * vx.y, vz.z * vx.x - vz.x * vx.z, vz.x * vx.y - vz.y * vx.x };

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

// Get double array of matrix data. convert matrix to a flat array
static inline struct mat4_f64_flat mat4_f64_flatten( struct mat4_f64 m )
{
    struct mat4_f64_flat result = { 0 };

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
static inline void mat4_f64_decompose( struct mat4_f64 m, struct vec3_f64 *translation, struct quat_f64 *rotation, struct vec3_f64 *scale )
{
    // Extract translation.
    translation->x = m.m03;
    translation->y = m.m13;
    translation->z = m.m23;

    // Extract upper-left for determinant computation
    const double a = m.m00;
    const double b = m.m01;
    const double c = m.m02;
    const double d = m.m10;
    const double e = m.m11;
    const double f = m.m12;
    const double g = m.m20;
    const double h = m.m21;
    const double i = m.m22;
    const double A = e * i - f * h;
    const double B = f * g - d * i;
    const double C = d * h - e * g;

    // Extract scale
    const double det = a * A + b * B + c * C;
    struct vec3_f64 abc = { a, b, c };
    struct vec3_f64 def = { d, e, f };
    struct vec3_f64 ghi = { g, h, i };

    double scalex = vec3_f64_len( abc );
    double scaley = vec3_f64_len( def );
    double scalez = vec3_f64_len( ghi );
    struct vec3_f64 s = { scalex, scaley, scalez };

    if ( det < 0 ) s = vec3_f64_negate( s );

    *scale = s;

    // Remove scale from the matrix if it is not close to zero
    struct mat4_f64 clone = m;
    if ( !f64_equals( det, 0, EPSILON ) )
    {
        clone.m00 /= s.x;
        clone.m11 /= s.y;
        clone.m22 /= s.z;

        // Extract rotation
        *rotation = quat_f64_from_mat4_f64( clone );
    }
    else
    {
        // Set to identity if close to zero
        *rotation = quat_f64_identity();
    }
}

#endif