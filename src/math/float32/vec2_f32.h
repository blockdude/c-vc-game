#ifndef VEC2_F32_H
#define VEC2_F32_H

#include "../../util/types.h"
#include <math.h>

// Vector2 with components value 0.0f
static inline struct vec2_f32 vec2_f32_zero( void )
{
    struct vec2_f32 result = { 0.0f, 0.0f };
    return result;
}

// Vector2 with components value 1.0f
static inline struct vec2_f32 vec2_f32_one( void )
{
    struct vec2_f32 result = { 1.0f, 1.0f };
    return result;
}

// Add two vectors (a + b)
static inline struct vec2_f32 vec2_f32_add( struct vec2_f32 a, struct vec2_f32 b )
{
    struct vec2_f32 result = { a.x + b.x, a.y + b.y };
    return result;
}

// Add a value to a vector
static inline struct vec2_f32 vec2_f32_add_val( struct vec2_f32 v, float val )
{
    struct vec2_f32 result = { v.x + val, v.y + val };
    return result;
}

// Subtract two vectors (a - b)
static inline struct vec2_f32 vec2_f32_sub( struct vec2_f32 a, struct vec2_f32 b )
{
    struct vec2_f32 result = { a.x - b.x, a.y - b.y };
    return result;
}

// Subtract a value from a vector
static inline struct vec2_f32 vec2_f32_sub_val( struct vec2_f32 v, float val )
{
    struct vec2_f32 result = { v.x - val, v.y - val };
    return result;
}

// Calculate the length of a vector
static inline float vec2_f32_len( struct vec2_f32 v )
{
    float result = sqrtf( ( v.x * v.x ) + ( v.y * v.y ) );
    return result;
}

// Calculate the squared length of a vector
static inline float vec2_f32_len_sq( struct vec2_f32 v )
{
    float result = ( v.x * v.x ) + ( v.y * v.y );
    return result;
}

// Calculate two vectors dot product
static inline float vec2_f32_dot( struct vec2_f32 a, struct vec2_f32 b )
{
    float result = ( a.x * b.x ) + ( a.y * b.y );
    return result;
}

// Calculate distance between two vectors
static inline float vec2_f32_dist( struct vec2_f32 a, struct vec2_f32 b )
{
    float result = sqrtf( ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) );
    return result;
}

// Calculate squared distance between two vectors
static inline float vec2_f32_dist_sq( struct vec2_f32 a, struct vec2_f32 b )
{
    float result = ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y );
    return result;
}

// Calculate angle between two vectors
// NOTE: Angle is calculated from origin point (0, 0)
static inline float vec2_f32_angle( struct vec2_f32 a, struct vec2_f32 b )
{
    float result = 0.0f;

    float dot = a.x * b.x + a.y * b.y;
    float det = a.x * b.y - a.y * b.x;

    result = atan2f( det, dot );

    return result;
}

// Calculate angle defined by a two vectors line
// NOTE: Parameters need to be normalized
// Current implementation should be aligned with glm::angle
static inline float vec2_f32_line_angle( struct vec2_f32 start, struct vec2_f32 end )
{
    float result = 0.0f;

    result = -atan2f( end.y - start.y, end.x - start.x );

    return result;
}

// Scale vector (multiply by value)
static inline struct vec2_f32 vec2_f32_scale( struct vec2_f32 v, float scale )
{
    struct vec2_f32 result = { v.x * scale, v.y * scale };
    return result;
}

// Multiply vector by vector
static inline struct vec2_f32 vec2_f32_mul( struct vec2_f32 a, struct vec2_f32 b )
{
    struct vec2_f32 result = { a.x * b.x, a.y * b.y };
    return result;
}

// Negate vector
static inline struct vec2_f32 vec2_f32_negate( struct vec2_f32 v )
{
    struct vec2_f32 result = { -v.x, -v.y };
    return result;
}

// Divide vector by vector
static inline struct vec2_f32 vec2_f32_div( struct vec2_f32 a, struct vec2_f32 b )
{
    struct vec2_f32 result = { a.x / b.x, a.y / b.y };

    return result;
}

// Normalize provided vector
static inline struct vec2_f32 vec2_f32_normalize( struct vec2_f32 v )
{
    struct vec2_f32 result = { 0 };

    float len = sqrtf( ( v.x * v.x ) + ( v.y * v.y ) );
    if ( len > 0 )
    {
        float ilen = 1.0f / len;
        result.x = v.x * ilen;
        result.y = v.y * ilen;
    }

    return result;
}

// Transforms a struct vec2_f32 by a given Matrix
static inline struct vec2_f32 vec2_f32_transform( struct vec2_f32 v, struct mat4_f32 m )
{
    struct vec2_f32 result = { 0 };

    float x = v.x;
    float y = v.y;
    float z = 0;

    result.x = m.m00 * x + m.m01 * y + m.m02 * z + m.m03;
    result.y = m.m10 * x + m.m11 * y + m.m12 * z + m.m13;

    return result;
}

// Calculate linear interpolation between two vectors
static inline struct vec2_f32 vec2_f32_lerp( struct vec2_f32 a, struct vec2_f32 b, float t )
{
    struct vec2_f32 result = { 0 };

    result.x = a.x + t * ( b.x - a.x );
    result.y = a.y + t * ( b.y - a.y );

    return result;
}

// Calculate reflected vector to normal
static inline struct vec2_f32 vec2_f32_reflect( struct vec2_f32 v, struct vec2_f32 normal )
{
    struct vec2_f32 result = { 0 };

    float dot = ( v.x * normal.x + v.y * normal.y );

    result.x = v.x - ( 2.0f * normal.x ) * dot;
    result.y = v.y - ( 2.0f * normal.y ) * dot;

    return result;
}

// Get min value for each pair of components
static inline struct vec2_f32 vec2_f32_min( struct vec2_f32 a, struct vec2_f32 b )
{
    struct vec2_f32 result = { 0 };

    result.x = fminf( a.x, b.x );
    result.y = fminf( a.y, b.y );

    return result;
}

// Get max value for each pair of components
static inline struct vec2_f32 vec2_f32_max( struct vec2_f32 a, struct vec2_f32 b )
{
    struct vec2_f32 result = { 0 };

    result.x = fmaxf( a.x, b.x );
    result.y = fmaxf( a.y, b.y );

    return result;
}

// Rotate vector by angle
static inline struct vec2_f32 vec2_f32_rotate( struct vec2_f32 v, float angle )
{
    struct vec2_f32 result = { 0 };

    float cos = cosf( angle );
    float sin = sinf( angle );

    result.x = v.x * cos - v.y * sin;
    result.y = v.x * sin + v.y * cos;

    return result;
}

// Move Vector towards target
static inline struct vec2_f32 vec2_f32_move_towards( struct vec2_f32 v, struct vec2_f32 target, float max )
{
    struct vec2_f32 result = { 0 };

    float dx = target.x - v.x;
    float dy = target.y - v.y;
    float value = ( dx * dx ) + ( dy * dy );

    if ( ( value == 0 ) || ( ( max >= 0 ) && ( value <= max * max ) ) )
        return target;

    float dist = sqrtf( value );

    result.x = v.x + dx / dist * max;
    result.y = v.y + dy / dist * max;

    return result;
}

// Invert the given vector
static inline struct vec2_f32 vec2_f32_invert( struct vec2_f32 v )
{
    struct vec2_f32 result = { 1.0f / v.x, 1.0f / v.y };
    return result;
}

// Clamp the components of the vector between
// min and max values specified by the given vectors
static inline struct vec2_f32 vec2_f32_clamp( struct vec2_f32 v, struct vec2_f32 min, struct vec2_f32 max )
{
    struct vec2_f32 result = { 0 };

    result.x = fminf( max.x, fmaxf( min.x, v.x ) );
    result.y = fminf( max.y, fmaxf( min.y, v.y ) );

    return result;
}

// Clamp the components of the vector between
// min and max values
static inline struct vec2_f32 vec2_f32_clamp_val( struct vec2_f32 v, float min, float max )
{
    struct vec2_f32 result = { 0 };

    result.x = fminf( max, fmaxf( min, v.x ) );
    result.y = fminf( max, fmaxf( min, v.y ) );

    return result;
}

// Clamp the magnitude of the vector between two min and max values
static inline struct vec2_f32 vec2_f32_clamp_len( struct vec2_f32 v, float min, float max )
{
    struct vec2_f32 result = v;

    float len = ( v.x * v.x ) + ( v.y * v.y );
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
    }

    return result;
}

// Check whether two given vectors are almost equal
static inline int vec2_f32_equals( struct vec2_f32 p, struct vec2_f32 q, float epsilon )
{
    int result =
        ( ( fabsf( p.x - q.x ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.x ), fabsf( q.x ) ) ) ) ) &&
        ( ( fabsf( p.y - q.y ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.y ), fabsf( q.y ) ) ) ) );

    return result;
}

// Compute the direction of a refracted ray
// v: normalized direction of the incoming ray
// n: normalized normal vector of the interface of two optical media
// r: ratio of the refractive index of the medium from where the ray comes
//    to the refractive index of the medium on the other side of the surface
static inline struct vec2_f32 vec2_f32_refract( struct vec2_f32 v, struct vec2_f32 n, float r )
{
    struct vec2_f32 result = { 0 };

    float dot = v.x * n.x + v.y * n.y;
    float d = 1.0f - r * r * ( 1.0f - dot * dot );

    if ( d >= 0.0f )
    {
        d = sqrtf( d );
        v.x = r * v.x - ( r * dot + d ) * n.x;
        v.y = r * v.y - ( r * dot + d ) * n.y;

        result = v;
    }

    return result;
}

#endif