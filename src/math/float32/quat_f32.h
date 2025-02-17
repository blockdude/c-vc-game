#ifndef QUAT_F32_H
#define QUAT_F32_H

#include "../../util/types.h"
#include <math.h>

// Add two quaternions
static inline struct quat_f32 quat_f32_add( struct quat_f32 p, struct quat_f32 q )
{
    struct quat_f32 result = { p.x + q.x, p.y + q.y, p.z + q.z, p.w + q.w };
    return result;
}

// Add quaternion and float value
static inline struct quat_f32 quat_f32_add_val( struct quat_f32 q, float val )
{
    struct quat_f32 result = { q.x + val, q.y + val, q.z + val, q.w + val };
    return result;
}

// Subtract two quaternions
static inline struct quat_f32 quat_f32_sub( struct quat_f32 p, struct quat_f32 q )
{
    struct quat_f32 result = { p.x - q.x, p.y - q.y, p.z - q.z, p.w - q.w };
    return result;
}

// Subtract quaternion and float value
static inline struct quat_f32 quat_f32_sub_val( struct quat_f32 q, float val )
{
    struct quat_f32 result = { q.x - val, q.y - val, q.z - val, q.w - val };
    return result;
}

// Get identity quaternion
static inline struct quat_f32 quat_f32_identity( void )
{
    struct quat_f32 result = { 0.0f, 0.0f, 0.0f, 1.0f };
    return result;
}

// Computes the length of a quaternion
static inline float quat_f32_len( struct quat_f32 q )
{
    float result = sqrtf( q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w );
    return result;
}

// Normalize provided quaternion
static inline struct quat_f32 quat_f32_normalize( struct quat_f32 q )
{
    struct quat_f32 result = { 0 };

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
static inline struct quat_f32 quat_f32_invert( struct quat_f32 q )
{
    struct quat_f32 result = q;

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
static inline struct quat_f32 quat_f32_mul( struct quat_f32 p, struct quat_f32 q )
{
    struct quat_f32 result = { 0 };

    float qax = p.x, qay = p.y, qaz = p.z, qaw = p.w;
    float qbx = q.x, qby = q.y, qbz = q.z, qbw = q.w;

    result.x = qax * qbw + qaw * qbx + qay * qbz - qaz * qby;
    result.y = qay * qbw + qaw * qby + qaz * qbx - qax * qbz;
    result.z = qaz * qbw + qaw * qbz + qax * qby - qay * qbx;
    result.w = qaw * qbw - qax * qbx - qay * qby - qaz * qbz;

    return result;
}

// Scale quaternion by float value
static inline struct quat_f32 quat_f32_scale( struct quat_f32 q, float s )
{
    struct quat_f32 result = { 0 };

    result.x = q.x * s;
    result.y = q.y * s;
    result.z = q.z * s;
    result.w = q.w * s;

    return result;
}

// Divide two quaternions
static inline struct quat_f32 quat_f32_div( struct quat_f32 p, struct quat_f32 q )
{
    struct quat_f32 result = { p.x / q.x, p.y / q.y, p.z / q.z, p.w / q.w };
    return result;
}

// Calculate linear interpolation between two quaternions
static inline struct quat_f32 quat_f32_lerp( struct quat_f32 p, struct quat_f32 q, float t )
{
    struct quat_f32 result = { 0 };

    result.x = p.x + t * ( q.x - p.x );
    result.y = p.y + t * ( q.y - p.y );
    result.z = p.z + t * ( q.z - p.z );
    result.w = p.w + t * ( q.w - p.w );

    return result;
}

// Calculate slerp-optimized interpolation between two quaternions
static inline struct quat_f32 quat_f32_nlerp( struct quat_f32 p, struct quat_f32 q, float t )
{
    struct quat_f32 result = { 0 };

    // struct quat_f32Lerp(p, q, t)
    result.x = p.x + t * ( q.x - p.x );
    result.y = p.y + t * ( q.y - p.y );
    result.z = p.z + t * ( q.z - p.z );
    result.w = p.w + t * ( q.w - p.w );

    // quat_f32_Normalize(n);
    struct quat_f32 n = result;
    float len = sqrtf( n.x * n.x + n.y * n.y + n.z * n.z + n.w * n.w );
    if ( len == 0.0f ) len = 1.0f;
    float ilen = 1.0f / len;

    result.x = n.x * ilen;
    result.y = n.y * ilen;
    result.z = n.z * ilen;
    result.w = n.w * ilen;

    return result;
}

// Calculates spherical linear interpolation between two quaternions
static inline struct quat_f32 quat_f32_slerp( struct quat_f32 p, struct quat_f32 q, float t, float epsilon )
{
    struct quat_f32 result = { 0 };

    float cos_half_theta = p.x * q.x + p.y * q.y + p.z * q.z + p.w * q.w;

    if ( cos_half_theta < 0.0f )
    {
        q.x = -q.x; q.y = -q.y; q.z = -q.z; q.w = -q.w;
        cos_half_theta = -cos_half_theta;
    }

    if ( fabsf( cos_half_theta ) >= 1.0f ) result = p;
    else if ( cos_half_theta > 0.95f ) result = quat_f32_nlerp( p, q, t );
    else
    {
        float half_theta = acosf( cos_half_theta );
        float sin_half_theta = sqrtf( 1.0f - cos_half_theta * cos_half_theta );

        if ( fabsf( sin_half_theta ) < epsilon )
        {
            result.x = ( p.x * 0.5f + q.x * 0.5f );
            result.y = ( p.y * 0.5f + q.y * 0.5f );
            result.z = ( p.z * 0.5f + q.z * 0.5f );
            result.w = ( p.w * 0.5f + q.w * 0.5f );
        }
        else
        {
            float ratio_a = sinf( ( 1.0f - t ) * half_theta ) / sin_half_theta;
            float ratio_b = sinf( t * half_theta )/sin_half_theta;

            result.x = ( p.x * ratio_a + q.x * ratio_b );
            result.y = ( p.y * ratio_a + q.y * ratio_b );
            result.z = ( p.z * ratio_a + q.z * ratio_b );
            result.w = ( p.w * ratio_a + q.w * ratio_b );
        }
    }

    return result;
}

// Calculate quaternion cubic spline interpolation using Cubic Hermite Spline algorithm
// as described in the GLTF 2.0 specification: https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html#interpolation-cubic
static inline struct quat_f32 quat_f32_cubic_hermite_spline( struct quat_f32 p, struct quat_f32 out_tan_p, struct quat_f32 q, struct quat_f32 in_tan_q, float t )
{
    float t2 = t * t;
    float t3 = t2 * t;
    float h00 = 2.0f * t3 - 3.0f * t2 + 1.0f;
    float h10 = t3 - 2.0f * t2 + t;
    float h01 = -2.0f * t3 + 3.0f * t2;
    float h11 = t3 - t2;

    struct quat_f32 p0 = quat_f32_scale( p, h00 );
    struct quat_f32 m0 = quat_f32_scale( out_tan_p, h10 );
    struct quat_f32 p1 = quat_f32_scale( q, h01 );
    struct quat_f32 m1 = quat_f32_scale( in_tan_q, h11 );

    struct quat_f32 result = { 0 };

    result = quat_f32_add( p0, m0 );
    result = quat_f32_add( result, p1 );
    result = quat_f32_add( result, m1 );
    result = quat_f32_normalize( result );

    return result;
}

// Calculate quaternion based on the rotation from vector a to vector b
static inline struct quat_f32 quat_f32_from_vec3_f32( struct vec3_f32 p, struct vec3_f32 q )
{
    struct quat_f32 result = { 0 };

    float dot = ( p.x * q.x + p.y * q.y + p.z * q.z );    // vec3_DotProduct(p, q) | cos2theta
    struct vec3_f32 cross = { p.y * q.z - p.z * q.y, p.z * q.x - p.x * q.z, p.x * q.y - p.y * q.x }; // Vecbr3CrossProduct(p, q)

    result.x = cross.x;
    result.y = cross.y;
    result.z = cross.z;
    result.w = 1.0f + dot;

    // struct quat_f32Normalize(n);
    // NOTE: Normalize q essentially nlerp the original and identity q 0.5
    struct quat_f32 n = result;
    float len = sqrtf( n.x * n.x + n.y * n.y + n.z * n.z + n.w * n.w );
    if ( len == 0.0f ) len = 1.0f;
    float ilen = 1.0f / len;

    result.x = n.x * ilen;
    result.y = n.y * ilen;
    result.z = n.z * ilen;
    result.w = n.w * ilen;

    return result;
}

// Get a quaternion for a given rotation matrix
static inline struct quat_f32 quat_f32_from_mat4_f32( struct mat4_f32 m )
{
    struct quat_f32 result = { 0 };

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
static inline struct mat4_f32 quat_f32_to_mat4_f32( struct quat_f32 q )
{
    struct mat4_f32 result = {
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
static inline struct quat_f32 quat_f32_from_axis_angle( struct vec3_f32 axis, float angle )
{
    struct quat_f32 result = { 0.0f, 0.0f, 0.0f, 1.0f };

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

        // struct quat_f32Normalize( q );
        struct quat_f32 q = result;
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
static inline void quat_f32_to_axis_angle( struct quat_f32 q, float epsilon, struct vec3_f32 *out_axis, float *out_angle )
{
    if ( fabsf( q.w ) > 1.0f )
    {
        // struct quat_f32Normalize( q );
        float len = sqrtf( q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w );
        if ( len == 0.0f ) len = 1.0f;
        float ilen = 1.0f / len;

        q.x = q.x * ilen;
        q.y = q.y * ilen;
        q.z = q.z * ilen;
        q.w = q.w * ilen;
    }

    struct vec3_f32 res_axis = { 0.0f, 0.0f, 0.0f };
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
static inline struct quat_f32 quat_f32_from_euler( float pitch, float yaw, float roll )
{
    struct quat_f32 result = { 0 };

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
static inline struct vec3_f32 quat_f32_to_euler( struct quat_f32 q )
{
    struct vec3_f32 result = { 0 };

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
static inline struct quat_f32 quat_f32_transform( struct quat_f32 q, struct mat4_f32 m )
{
    struct quat_f32 result = { 0 };

    result.x = m.m00 * q.x + m.m01 * q.y + m.m02 * q.z + m.m03 * q.w;
    result.y = m.m10 * q.x + m.m11 * q.y + m.m12 * q.z + m.m13 * q.w;
    result.z = m.m20 * q.x + m.m21 * q.y + m.m22 * q.z + m.m23 * q.w;
    result.w = m.m30 * q.x + m.m31 * q.y + m.m32 * q.z + m.m33 * q.w;

    return result;
}

// Check whether two given quaternions are almost equal
static inline int quat_f32_equals( struct quat_f32 p, struct quat_f32 q, float epsilon )
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
