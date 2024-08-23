#ifndef QUAT_H
#define QUAT_H

#include <math.h>
#include "types.h"

/*
 * This is a fork of the raymath v1.5 library.
 * There are no modifications other than some formating and
 * naming differences.
 */

//----------------------------------------------------------------------------------
// Module Functions Definition - Quaternion math
//----------------------------------------------------------------------------------

// Add two quaternions
static inline quat_t quat_add( quat_t p, quat_t q )
{
    quat_t result = { p.x + q.x, p.y + q.y, p.z + q.z, p.w + q.w };
    return result;
}

// Add quaternion and float value
static inline quat_t quat_add_s( quat_t q, float s )
{
    quat_t result = { q.x + s, q.y + s, q.z + s, q.w + s };
    return result;
}

// Subtract two quaternions
static inline quat_t quat_sub( quat_t p, quat_t q )
{
    quat_t result = { p.x - q.x, p.y - q.y, p.z - q.z, p.w - q.w };
    return result;
}

// Subtract quaternion and float value
static inline quat_t quat_sub_s( quat_t q, float s )
{
    quat_t result = { q.x - s, q.y - s, q.z - s, q.w - s };
    return result;
}

// Get identity quaternion
static inline quat_t quat_identity( void )
{
    quat_t result = { 0.0f, 0.0f, 0.0f, 1.0f };
    return result;
}

// Computes the length of a quaternion
static inline float quat_len( quat_t q )
{
    float result = sqrtf( q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w );
    return result;
}

// Normalize provided quaternion
static inline quat_t quat_normalize( quat_t q )
{
    quat_t result = { 0 };

    float len = sqrtf( q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w );
    if ( len == 0.0f ) len = 1.0f;
    float ilen = 1.0f / len;

    result.x = q.x * ilen;
    result.y = q.y * ilen;
    result.z = q.z * ilen;
    result.w = q.w * ilen;

    return result;
}

// Invert provided quaternion
static inline quat_t quat_invert( quat_t q )
{
    quat_t result = q;

    float len = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;

    if ( len != 0.0f )
    {
        float ilen = 1.0f / len;

        result.x *= -ilen;
        result.y *= -ilen;
        result.z *= -ilen;
        result.w *= ilen;
    }

    return result;
}

// Calculate two quaternion multiplication
static inline quat_t quat_mul( quat_t p, quat_t q )
{
    quat_t result = { 0 };

    float qax = p.x, qay = p.y, qaz = p.z, qaw = p.w;
    float qbx = q.x, qby = q.y, qbz = q.z, qbw = q.w;

    result.x = qax * qbw + qaw * qbx + qay * qbz - qaz * qby;
    result.y = qay * qbw + qaw * qby + qaz * qbx - qax * qbz;
    result.z = qaz * qbw + qaw * qbz + qax * qby - qay * qbx;
    result.w = qaw * qbw - qax * qbx - qay * qby - qaz * qbz;

    return result;
}

// Scale quaternion by float value
static inline quat_t quat_scale( quat_t q, float s )
{
    quat_t result = { 0 };

    result.x = q.x * s;
    result.y = q.y * s;
    result.z = q.z * s;
    result.w = q.w * s;

    return result;
}

// Divide two quaternions
static inline quat_t quat_div( quat_t p, quat_t q )
{
    quat_t result = { p.x / q.x, p.y / q.y, p.z / q.z, p.w / q.w };
    return result;
}

// Calculate linear interpolation between two quaternions
static inline quat_t quat_lerp( quat_t a, quat_t b, float t )
{
    quat_t result = { 0 };

    result.x = a.x + t * ( b.x - a.x );
    result.y = a.y + t * ( b.y - a.y );
    result.z = a.z + t * ( b.z - a.z );
    result.w = a.w + t * ( b.w - a.w );

    return result;
}

// Calculate slerp-optimized interpolation between two quaternions
static inline quat_t quat_nlerp( quat_t a, quat_t b, float t )
{
    quat_t result = { 0 };

    // quat_tLerp(a, b, t)
    result.x = a.x + t * ( b.x - a.x );
    result.y = a.y + t * ( b.y - a.y );
    result.z = a.z + t * ( b.z - a.z );
    result.w = a.w + t * ( b.w - a.w );

    // quat_tNormalize(q);
    quat_t q = result;
    float len = sqrtf( q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w );
    if ( len == 0.0f ) len = 1.0f;
    float ilen = 1.0f / len;

    result.x = q.x * ilen;
    result.y = q.y * ilen;
    result.z = q.z * ilen;
    result.w = q.w * ilen;

    return result;
}

// Calculates spherical linear interpolation between two quaternions
static inline quat_t quat_slerp( quat_t a, quat_t b, float t, float epsilon )
{
    quat_t result = { 0 };

    float cos_half_theta = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;

    if ( cos_half_theta < 0.0f )
    {
        b.x = -b.x; b.y = -b.y; b.z = -b.z; b.w = -b.w;
        cos_half_theta = -cos_half_theta;
    }

    if ( fabsf( cos_half_theta ) >= 1.0f ) result = a;
    else if ( cos_half_theta > 0.95f ) result = quat_nlerp( a, b, t );
    else
    {
        float half_theta = acosf( cos_half_theta );
        float sin_half_theta = sqrtf( 1.0f - cos_half_theta * cos_half_theta );

        if ( fabsf( sin_half_theta ) < epsilon )
        {
            result.x = ( a.x * 0.5f + b.x * 0.5f );
            result.y = ( a.y * 0.5f + b.y * 0.5f );
            result.z = ( a.z * 0.5f + b.z * 0.5f );
            result.w = ( a.w * 0.5f + b.w * 0.5f );
        }
        else
        {
            float ratio_a = sinf( ( 1.0f - t ) * half_theta ) / sin_half_theta;
            float ratio_b = sinf( t * half_theta )/sin_half_theta;

            result.x = ( a.x * ratio_a + b.x * ratio_b );
            result.y = ( a.y * ratio_a + b.y * ratio_b );
            result.z = ( a.z * ratio_a + b.z * ratio_b );
            result.w = ( a.w * ratio_a + b.w * ratio_b );
        }
    }

    return result;
}

// Calculate quaternion cubic spline interpolation using Cubic Hermite Spline algorithm
// as described in the GLTF 2.0 specification: https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html#interpolation-cubic
static inline quat_t quat_cubic_hermite_spline( quat_t a, quat_t out_tan_a, quat_t b, quat_t in_tan_b, float t )
{
    float t2 = t * t;
    float t3 = t2 * t;
    float h00 = 2.0f * t3 - 3.0f * t2 + 1.0f;
    float h10 = t3 - 2.0f * t2 + t;
    float h01 = -2.0f * t3 + 3.0f * t2;
    float h11 = t3 - t2;

    quat_t p0 = quat_scale( a, h00 );
    quat_t m0 = quat_scale( out_tan_a, h10 );
    quat_t p1 = quat_scale( b, h01 );
    quat_t m1 = quat_scale( in_tan_b, h11 );

    quat_t result = { 0 };

    result = quat_add( p0, m0 );
    result = quat_add( result, p1 );
    result = quat_add( result, m1 );
    result = quat_normalize( result );

    return result;
}

// Calculate quaternion based on the rotation from vector a to vector b
static inline quat_t quat_from_vec3s( vec3_t a, vec3_t b )
{
    quat_t result = { 0 };

    float dot = ( a.x * b.x + a.y * b.y + a.z * b.z );    // vec3_DotProduct(a, b) | cos2theta
    vec3_t cross = { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; // Vecbr3CrossProduct(a, b)

    result.x = cross.x;
    result.y = cross.y;
    result.z = cross.z;
    result.w = 1.0f + dot;

    // quat_tNormalize(q);
    // NOTE: Normalize b essentially nlerp the original and identity b 0.5
    quat_t q = result;
    float len = sqrtf( q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w );
    if ( len == 0.0f ) len = 1.0f;
    float ilen = 1.0f / len;

    result.x = q.x * ilen;
    result.y = q.y * ilen;
    result.z = q.z * ilen;
    result.w = q.w * ilen;

    return result;
}

// Get a quaternion for a given rotation matrix
static inline quat_t quat_from_mat4( mat4_t m )
{
    quat_t result = { 0 };

    float four_w_sq_sub_one = m.m00 + m.m11 + m.m22;
    float four_x_sq_sub_one = m.m00 - m.m11 - m.m22;
    float four_y_sq_sub_one = m.m11 - m.m00 - m.m22;
    float four_z_sq_sub_one = m.m22 - m.m00 - m.m11;

    int biggest_idx = 0;
    float four_biggest_sq_sub_one = four_w_sq_sub_one;

    if ( four_x_sq_sub_one > four_biggest_sq_sub_one )
    {
        four_biggest_sq_sub_one = four_x_sq_sub_one;
        biggest_idx = 1;
    }

    if ( four_y_sq_sub_one > four_biggest_sq_sub_one )
    {
        four_biggest_sq_sub_one = four_y_sq_sub_one;
        biggest_idx = 2;
    }

    if ( four_z_sq_sub_one > four_biggest_sq_sub_one )
    {
        four_biggest_sq_sub_one = four_z_sq_sub_one;
        biggest_idx = 3;
    }

    float biggest_val = sqrtf( four_biggest_sq_sub_one + 1.0f ) * 0.5f;
    float mult = 0.25f / biggest_val;

    switch ( biggest_idx )
    {
        case 0:
            result.w = biggest_val;
            result.x = ( m.m21 - m.m12 ) * mult;
            result.y = ( m.m02 - m.m20 ) * mult;
            result.z = ( m.m10 - m.m01 ) * mult;
            break;
        case 1:
            result.x = biggest_val;
            result.w = ( m.m21 - m.m12 ) * mult;
            result.y = ( m.m10 + m.m01 ) * mult;
            result.z = ( m.m02 + m.m20 ) * mult;
            break;
        case 2:
            result.y = biggest_val;
            result.w = ( m.m02 - m.m20 ) * mult;
            result.x = ( m.m10 + m.m01 ) * mult;
            result.z = ( m.m21 + m.m12 ) * mult;
            break;
        case 3:
            result.z = biggest_val;
            result.w = ( m.m10 - m.m01 ) * mult;
            result.x = ( m.m02 + m.m20 ) * mult;
            result.y = ( m.m21 + m.m12 ) * mult;
            break;
    }

    return result;
}

// Get a matrix for a given quaternion
static inline mat4_t quat_to_mat4( quat_t q )
{
    mat4_t result = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	}; // MatrixIdentity()

    float a2 = q.x * q.x;
    float b2 = q.y * q.y;
    float c2 = q.z * q.z;
    float ac = q.x * q.z;
    float ab = q.x * q.y;
    float bc = q.y * q.z;
    float ad = q.w * q.x;
    float bd = q.w * q.y;
    float cd = q.w * q.z;

    result.m00 = 1.0f - 2.0f * ( b2 + c2 );
    result.m10 = 2.0f * ( ab + cd );
    result.m20 = 2.0f * ( ac - bd );

    result.m01 = 2.0f * ( ab - cd );
    result.m11 = 1.0f - 2.0f * ( a2 + c2 );
    result.m21 = 2.0f * ( bc + ad );

    result.m02 = 2.0f * ( ac + bd );
    result.m12 = 2.0f * ( bc - ad );
    result.m22 = 1.0f - 2.0f * ( a2 + b2 );

    return result;
}

// Get rotation quaternion for an angle and axis
// NOTE: Angle must be provided in radians
static inline quat_t quat_from_axis_angle( vec3_t axis, float angle )
{
    quat_t result = { 0.0f, 0.0f, 0.0f, 1.0f };

    float axislen = sqrtf( axis.x * axis.x + axis.y * axis.y + axis.z * axis.z );

    if ( axislen != 0.0f )
    {
        angle *= 0.5f;

        float len = 0.0f;
        float ilen = 0.0f;

        // Vector3Normalize( axis )
        len = axislen;
        if ( len == 0.0f ) len = 1.0f;
        ilen = 1.0f / len;
        axis.x *= ilen;
        axis.y *= ilen;
        axis.z *= ilen;

        float sin = sinf( angle );
        float cos = cosf( angle );

        result.x = axis.x * sin;
        result.y = axis.y * sin;
        result.z = axis.z * sin;
        result.w = cos;

        // quat_tNormalize( q );
        quat_t q = result;
        len = sqrtf( q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w );
        if ( len == 0.0f ) len = 1.0f;
        ilen = 1.0f / len;
        result.x = q.x * ilen;
        result.y = q.y * ilen;
        result.z = q.z * ilen;
        result.w = q.w * ilen;
    }

    return result;
}

// Get the rotation angle and axis for a given quaternion
static inline void quat_to_axis_angle( quat_t q, float epsilon, vec3_t *out_axis, float *out_angle )
{
    if ( fabsf( q.w ) > 1.0f )
    {
        // quat_tNormalize( q );
        float len = sqrtf( q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w );
        if ( len == 0.0f ) len = 1.0f;
        float ilen = 1.0f / len;

        q.x = q.x * ilen;
        q.y = q.y * ilen;
        q.z = q.z * ilen;
        q.w = q.w * ilen;
    }

    vec3_t res_axis = { 0.0f, 0.0f, 0.0f };
    float res_angle = 2.0f * acosf( q.w );
    float den = sqrtf( 1.0f - q.w * q.w );

    if ( den > epsilon )
    {
        res_axis.x = q.x / den;
        res_axis.y = q.y / den;
        res_axis.z = q.z / den;
    }
    else
    {
        // This occurs when the angle is zero.
        // Not a problem: just set an arbitrary normalized axis.
        res_axis.x = 1.0f;
    }

    *out_axis = res_axis;
    *out_angle = res_angle;
}

// Get the quaternion equivalent to Euler angles
// NOTE: Rotation order is ZYX
static inline quat_t quat_from_euler( float pitch, float yaw, float roll )
{
    quat_t result = { 0 };

    float x0 = cosf( pitch * 0.5f );
    float x1 = sinf( pitch * 0.5f );
    float y0 = cosf( yaw * 0.5f );
    float y1 = sinf( yaw * 0.5f );
    float z0 = cosf( roll * 0.5f );
    float z1 = sinf( roll * 0.5f );

    result.x = x1 * y0 * z0 - x0 * y1 * z1;
    result.y = x0 * y1 * z0 + x1 * y0 * z1;
    result.z = x0 * y0 * z1 - x1 * y1 * z0;
    result.w = x0 * y0 * z0 + x1 * y1 * z1;

    return result;
}

// Get the Euler angles equivalent to quaternion (roll, pitch, yaw)
// NOTE: Angles are returned in a Vector3 struct in radians
static inline vec3_t quat_to_euler( quat_t q )
{
    vec3_t result = { 0 };

    // Roll ( x-axis rotation )
    float x0 = 2.0f * ( q.w * q.x + q.y * q.z );
    float x1 = 1.0f - 2.0f * ( q.x * q.x + q.y * q.y );
    result.x = atan2f( x0, x1 );

    // Pitch ( y-axis rotation )
    float y0 = 2.0f * ( q.w * q.y - q.z * q.x );
    y0 = y0 > 1.0f ? 1.0f : y0;
    y0 = y0 < -1.0f ? -1.0f : y0;
    result.y = asinf( y0 );

    // Yaw ( z-axis rotation )
    float z0 = 2.0f * ( q.w * q.z + q.x * q.y );
    float z1 = 1.0f - 2.0f * ( q.y * q.y + q.z * q.z );
    result.z = atan2f( z0, z1 );

    return result;
}

// Transform a quaternion given a transformation matrix
static inline quat_t quat_transform( quat_t q, mat4_t m )
{
    quat_t result = { 0 };

    result.x = m.m00 * q.x + m.m01 * q.y + m.m02 * q.z + m.m03 * q.w;
    result.y = m.m10 * q.x + m.m11 * q.y + m.m12 * q.z + m.m13 * q.w;
    result.z = m.m20 * q.x + m.m21 * q.y + m.m22 * q.z + m.m23 * q.w;
    result.w = m.m30 * q.x + m.m31 * q.y + m.m32 * q.z + m.m33 * q.w;

    return result;
}

// Check whether two given quaternions are almost equal
static inline int quat_equals( quat_t p, quat_t q, float epsilon )
{
    int result =
		( ( ( fabsf( p.x - q.x ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.x ), fabsf( q.x ) ) ) ) )   &&
		  ( ( fabsf( p.y - q.y ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.y ), fabsf( q.y ) ) ) ) )   &&
		  ( ( fabsf( p.z - q.z ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.z ), fabsf( q.z ) ) ) ) )   &&
		  ( ( fabsf( p.w - q.w ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.w ), fabsf( q.w ) ) ) ) ) ) ||

		( ( ( fabsf( p.x + q.x ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.x ), fabsf( q.x ) ) ) ) )   &&
		  ( ( fabsf( p.y + q.y ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.y ), fabsf( q.y ) ) ) ) )   &&
		  ( ( fabsf( p.z + q.z ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.z ), fabsf( q.z ) ) ) ) )   &&
		  ( ( fabsf( p.w + q.w ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.w ), fabsf( q.w ) ) ) ) ) );

    return result;
}

#endif
