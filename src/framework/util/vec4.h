#ifndef VEC4_H
#define VEC4_H

#include <math.h>
#include "types.h"

/*
 * This is a fork of the raymath v1.5 library.
 * There are no modifications other than some formating and
 * naming differences.
 */

//----------------------------------------------------------------------------------
// Module Functions Definition - Vector4 math
//----------------------------------------------------------------------------------

static inline vec4_t vec4_zero( void )
{
    vec4_t result = { 0.0f, 0.0f, 0.0f, 0.0f };
    return result;
}

static inline vec4_t vec4_one( void )
{
    vec4_t result = { 1.0f, 1.0f, 1.0f, 1.0f };
    return result;
}

static inline vec4_t vec4_add( vec4_t a, vec4_t b )
{
    vec4_t result = {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w
    };
    return result;
}

static inline vec4_t vec4_add_s( vec4_t v, float s )
{
    vec4_t result = {
        v.x + s,
        v.y + s,
        v.z + s,
        v.w + s
    };
    return result;
}

static inline vec4_t vec4_sub( vec4_t a, vec4_t b )
{
    vec4_t result = {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
        a.w - b.w
    };
    return result;
}

static inline vec4_t vec4_sub_s( vec4_t v, float s )
{
    vec4_t result = {
        v.x - s,
        v.y - s,
        v.z - s,
        v.w - s
    };
    return result;
}

static inline float vec4_len( vec4_t v )
{
    float result = sqrtf( ( v.x * v.x ) + ( v.y * v.y ) + ( v.z * v.z ) + ( v.w * v.w ) );
    return result;
}

static inline float vec4_len_sq( vec4_t v )
{
    float result = ( v.x * v.x ) + ( v.y * v.y ) + ( v.z * v.z ) + ( v.w * v.w );
    return result;
}

static inline float vec4_dot( vec4_t a, vec4_t b )
{
    float result = ( a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w );
    return result;
}

// Calculate distance between two vectors
static inline float vec4_dist( vec4_t a, vec4_t b )
{
    float result = sqrtf(
			( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) +
			( a.z - b.z ) * ( a.z - b.z ) + ( a.w - b.w ) * ( a.w - b.w ) );
    return result;
}

// Calculate square distance between two vectors
static inline float vec4_dist_sq( vec4_t a, vec4_t b )
{
    float result =
        ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) +
        ( a.z - b.z ) * ( a.z - b.z ) + ( a.w - b.w ) * ( a.w - b.w );
    return result;
}

static inline vec4_t vec4_scale( vec4_t v, float scale )
{
    vec4_t result = { v.x * scale, v.y * scale, v.z * scale, v.w * scale };
    return result;
}

// Multiply vector by vector
static inline vec4_t vec4_mul( vec4_t a, vec4_t b )
{
    vec4_t result = { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
    return result;
}

// Negate vector
static inline vec4_t vec4_negate( vec4_t v )
{
    vec4_t result = { -v.x, -v.y, -v.z, -v.w };
    return result;
}

// Divide vector by vector
static inline vec4_t vec4_div( vec4_t a, vec4_t b )
{
    vec4_t result = { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
    return result;
}

// Normalize provided vector
static inline vec4_t vec4_normalize( vec4_t v )
{
    vec4_t result = { 0 };
    float len = sqrtf( ( v.x * v.x ) + ( v.y * v.y ) + ( v.z * v.z ) + ( v.w * v.w ) );

    if ( len > 0 )
    {
        float ilen = 1.0f / len;
        result.x = v.x * ilen;
        result.y = v.y * ilen;
        result.z = v.z * ilen;
        result.w = v.w * ilen;
    }

    return result;
}

// Get min value for each pair of components
static inline vec4_t vec4_min( vec4_t a, vec4_t b )
{
    vec4_t result = { 0 };

    result.x = fminf( a.x, b.x );
    result.y = fminf( a.y, b.y );
    result.z = fminf( a.z, b.z );
    result.w = fminf( a.w, b.w );

    return result;
}

// Get max value for each pair of components
static inline vec4_t vec4_max( vec4_t a, vec4_t b )
{
    vec4_t result = { 0 };

    result.x = fmaxf( a.x, b.x );
    result.y = fmaxf( a.y, b.y );
    result.z = fmaxf( a.z, b.z );
    result.w = fmaxf( a.w, b.w );

    return result;
}

// Calculate linear interpolation between two vectors
static inline vec4_t vec4_lerp( vec4_t a, vec4_t b, float t )
{
    vec4_t result = { 0 };

    result.x = a.x + t * ( b.x - a.x );
    result.y = a.y + t * ( b.y - a.y );
    result.z = a.z + t * ( b.z - a.z );
    result.w = a.w + t * ( b.w - a.w );

    return result;
}

// Move Vector towards target
static inline vec4_t vec4_move_towards( vec4_t v, vec4_t target, float max )
{
    vec4_t result = { 0 };

    float dx = target.x - v.x;
    float dy = target.y - v.y;
    float dz = target.z - v.z;
    float dw = target.w - v.w;
    float value = ( dx * dx ) + ( dy * dy ) + ( dz * dz ) + ( dw * dw );

    if ( ( value == 0 ) || ( ( max >= 0 ) && ( value <= max * max ) ) )
		return target;

    float dist = sqrtf( value );

    result.x = v.x + dx / dist * max;
    result.y = v.y + dy / dist * max;
    result.z = v.z + dz / dist * max;
    result.w = v.w + dw / dist * max;

    return result;
}

// Invert the given vector
static inline vec4_t vec4_invert( vec4_t v )
{
    vec4_t result = { 1.0f / v.x, 1.0f / v.y, 1.0f / v.z, 1.0f / v.w };
    return result;
}

// Check whether two given vectors are almost equal
static inline int vec4_equals( vec4_t p, vec4_t q, float epsilon )
{
    int result =
		( ( fabsf( p.x - q.x ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.x ), fabsf( q.x ) ) ) ) ) &&
        ( ( fabsf( p.y - q.y ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.y ), fabsf( q.y ) ) ) ) ) &&
        ( ( fabsf( p.z - q.z ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.z ), fabsf( q.z ) ) ) ) ) &&
        ( ( fabsf( p.w - q.w ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.w ), fabsf( q.w ) ) ) ) );
    return result;
}

#endif
