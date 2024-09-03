#ifndef VEC2_H
#define VEC2_H

#include <math.h>
#include "types.h"

/*
 * This is a fork of the raymath v1.5 library.
 * There are no modifications other than some formating and
 * naming differences.
 */

//----------------------------------------------------------------------------------
// Module Functions Definition - Vector2 math
//----------------------------------------------------------------------------------

static inline vec2_t vec2_zero( void )
{
	vec2_t result = { 0.0f, 0.0f };
	return result;
}

static inline vec2_t vec2_one( void )
{
	vec2_t result = { 1.0f, 1.0f };
	return result;
}

static inline vec2_t vec2_add( vec2_t a, vec2_t b )
{
	vec2_t result = { a.x + b.x, a.y + b.y };
	return result;
}

static inline vec2_t vec2_add_s( vec2_t v, float s )
{
	vec2_t result = { v.x + s, v.y + s };
	return result;
}

static inline vec2_t vec2_sub( vec2_t a, vec2_t b )
{
	vec2_t result = { a.x - b.x, a.y - b.y };
	return result;
}

static inline vec2_t vec2_sub_s( vec2_t v, float s )
{
	vec2_t result = { v.x - s, v.y - s };
	return result;
}

static inline float vec2_len( vec2_t v )
{
	float result = sqrtf( ( v.x * v.x ) + ( v.y * v.y ) );
	return result;
}

static inline float vec2_len_sq( vec2_t v )
{
	float result = ( v.x * v.x ) + ( v.y * v.y );
	return result;
}

static inline float vec2_dot( vec2_t a, vec2_t b )
{
	float result = ( a.x * b.x ) + ( a.y * b.y );
	return result;
}

static inline float vec2_dist( vec2_t a, vec2_t b )
{
	float result = sqrtf( ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) );
	return result;
}

static inline float vec2_dist_sq( vec2_t a, vec2_t b )
{
	float result = ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y );
	return result;
}

// Calculate angle between two vectors
// NOTE: Angle is calculated from origin point (0, 0)
static inline float vec2_angle( vec2_t a, vec2_t b )
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
static inline float vec2_line_angle( vec2_t start, vec2_t end)
{
    float result = 0.0f;

    result = -atan2f(end.y - start.y, end.x - start.x);

    return result;
}

// Scale vector (multiply by value)
static inline vec2_t vec2_scale( vec2_t v, float scale )
{
    vec2_t result = { v.x * scale, v.y * scale };
    return result;
}

// Multiply vector by vector
static inline vec2_t vec2_mul( vec2_t a, vec2_t b )
{
    vec2_t result = { a.x * b.x, a.y * b.y };
    return result;
}

// Negate vector
static inline vec2_t vec2_negate( vec2_t v )
{
    vec2_t result = { -v.x, -v.y };
    return result;
}

// Divide vector by vector
static inline vec2_t vec2_div( vec2_t a, vec2_t b )
{
    vec2_t result = { a.x / b.x, a.y / b.y };

    return result;
}

// Normalize provided vector
static inline vec2_t vec2_normalize( vec2_t v )
{
    vec2_t result = { 0 };

    float len = sqrtf( ( v.x * v.x ) + ( v.y * v.y ) );
    if ( len > 0 )
    {
		float ilen = 1.0f / len;
        result.x = v.x * ilen;
        result.y = v.y * ilen;
    }

    return result;
}

// Transforms a vec2_t by a given Matrix
static inline vec2_t vec2_transform( vec2_t v, mat4_t m )
{
    vec2_t result = { 0 };

    float x = v.x;
    float y = v.y;
    float z = 0;

    result.x = m.m00 * x + m.m01 * y + m.m02 * z + m.m03;
    result.y = m.m10 * x + m.m11 * y + m.m12 * z + m.m13;

    return result;
}

// Calculate linear interpolation between two vectors
static inline vec2_t vec2_lerp( vec2_t a, vec2_t b, float t )
{
    vec2_t result = { 0 };

    result.x = a.x + t * ( b.x - a.x );
    result.y = a.y + t * ( b.y - a.y );

    return result;
}

// Calculate reflected vector to normal
static inline vec2_t vec2_reflect( vec2_t v, vec2_t normal )
{
    vec2_t result = { 0 };

    float dot = ( v.x * normal.x + v.y * normal.y );

    result.x = v.x - ( 2.0f * normal.x ) * dot;
    result.y = v.y - ( 2.0f * normal.y ) * dot;

    return result;
}

// Get min value for each pair of components
static inline vec2_t vec2_min( vec2_t a, vec2_t b )
{
    vec2_t result = { 0 };

    result.x = fminf( a.x, b.x );
    result.y = fminf( a.y, b.y );

    return result;
}

// Get max value for each pair of components
static inline vec2_t vec2_max( vec2_t a, vec2_t b )
{
    vec2_t result = { 0 };

    result.x = fmaxf( a.x, b.x );
    result.y = fmaxf( a.y, b.y );

    return result;
}

// Rotate vector by angle
static inline vec2_t vec2_rotate( vec2_t v, float angle )
{
    vec2_t result = { 0 };

    float cos = cosf( angle );
    float sin = sinf( angle );

    result.x = v.x * cos - v.y * sin;
    result.y = v.x * sin + v.y * cos;

    return result;
}

// Move Vector towards target
static inline vec2_t vec2_move_towards( vec2_t v, vec2_t target, float max )
{
    vec2_t result = { 0 };

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
static inline vec2_t vec2_invert( vec2_t v )
{
    vec2_t result = { 1.0f / v.x, 1.0f / v.y };
    return result;
}

// Clamp the components of the vector between
// min and max values specified by the given vectors
static inline vec2_t vec2_clamp( vec2_t v, vec2_t min, vec2_t max )
{
    vec2_t result = { 0 };

    result.x = fminf( max.x, fmaxf( min.x, v.x ) );
    result.y = fminf( max.y, fmaxf( min.y, v.y ) );

    return result;
}

// Clamp the components of the vector between
// min and max scalar values
static inline vec2_t vec2_clamp_s( vec2_t v, float min, float max )
{
    vec2_t result = { 0 };

    result.x = fminf( max, fmaxf( min, v.x ) );
    result.y = fminf( max, fmaxf( min, v.y ) );

    return result;
}

// Clamp the magnitude of the vector between two min and max values
static inline vec2_t vec2_clamp_len( vec2_t v, float min, float max )
{
    vec2_t result = v;

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
static inline int vec2_equals( vec2_t p, vec2_t q, float epsilon )
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
static inline vec2_t vec2_refract( vec2_t v, vec2_t n, float r )
{
    vec2_t result = { 0 };

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
