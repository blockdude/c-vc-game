#ifndef VEC4_F64_H
#define VEC4_F64_H

#include "../../util/types.h"
#include <math.h>

static inline struct vec4_f64 vec4_f64_zero( void )
{
    struct vec4_f64 result = { 0.0f, 0.0f, 0.0f, 0.0f };
    return result;
}

static inline struct vec4_f64 vec4_f64_one( void )
{
    struct vec4_f64 result = { 1.0f, 1.0f, 1.0f, 1.0f };
    return result;
}

static inline struct vec4_f64 vec4_f64_add( struct vec4_f64 a, struct vec4_f64 b )
{
    struct vec4_f64 result = {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w
    };
    return result;
}

static inline struct vec4_f64 vec4_f64_add_val( struct vec4_f64 v, double val )
{
    struct vec4_f64 result = {
        v.x + val,
        v.y + val,
        v.z + val,
        v.w + val
    };
    return result;
}

static inline struct vec4_f64 vec4_f64_sub( struct vec4_f64 a, struct vec4_f64 b )
{
    struct vec4_f64 result = {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
        a.w - b.w
    };
    return result;
}

static inline struct vec4_f64 vec4_f64_sub_val( struct vec4_f64 v, double val )
{
    struct vec4_f64 result = {
        v.x - val,
        v.y - val,
        v.z - val,
        v.w - val
    };
    return result;
}

static inline double vec4_f64_len( struct vec4_f64 v )
{
    double result = sqrtf( ( v.x * v.x ) + ( v.y * v.y ) + ( v.z * v.z ) + ( v.w * v.w ) );
    return result;
}

static inline double vec4_f64_len_sq( struct vec4_f64 v )
{
    double result = ( v.x * v.x ) + ( v.y * v.y ) + ( v.z * v.z ) + ( v.w * v.w );
    return result;
}

static inline double vec4_f64_dot( struct vec4_f64 a, struct vec4_f64 b )
{
    double result = ( a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w );
    return result;
}

// Calculate distance between two vectors
static inline double vec4_f64_dist( struct vec4_f64 a, struct vec4_f64 b )
{
    double result = sqrtf(
			( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) +
			( a.z - b.z ) * ( a.z - b.z ) + ( a.w - b.w ) * ( a.w - b.w ) );
    return result;
}

// Calculate square distance between two vectors
static inline double vec4_f64_dist_sq( struct vec4_f64 a, struct vec4_f64 b )
{
    double result =
        ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) +
        ( a.z - b.z ) * ( a.z - b.z ) + ( a.w - b.w ) * ( a.w - b.w );
    return result;
}

static inline struct vec4_f64 vec4_f64_scale( struct vec4_f64 v, double scale )
{
    struct vec4_f64 result = { v.x * scale, v.y * scale, v.z * scale, v.w * scale };
    return result;
}

// Multiply vector by vector
static inline struct vec4_f64 vec4_f64_mul( struct vec4_f64 a, struct vec4_f64 b )
{
    struct vec4_f64 result = { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
    return result;
}

// Negate vector
static inline struct vec4_f64 vec4_f64_negate( struct vec4_f64 v )
{
    struct vec4_f64 result = { -v.x, -v.y, -v.z, -v.w };
    return result;
}

// Divide vector by vector
static inline struct vec4_f64 vec4_f64_div( struct vec4_f64 a, struct vec4_f64 b )
{
    struct vec4_f64 result = { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
    return result;
}

// Normalize provided vector
static inline struct vec4_f64 vec4_f64_normalize( struct vec4_f64 v )
{
    struct vec4_f64 result = { 0 };
    double len = sqrtf( ( v.x * v.x ) + ( v.y * v.y ) + ( v.z * v.z ) + ( v.w * v.w ) );

    if ( len > 0 )
    {
        double ilen = 1.0f / len;
        result.x = v.x * ilen;
        result.y = v.y * ilen;
        result.z = v.z * ilen;
        result.w = v.w * ilen;
    }

    return result;
}

// Get min value for each pair of components
static inline struct vec4_f64 vec4_f64_min( struct vec4_f64 a, struct vec4_f64 b )
{
    struct vec4_f64 result = { 0 };

    result.x = fminf( a.x, b.x );
    result.y = fminf( a.y, b.y );
    result.z = fminf( a.z, b.z );
    result.w = fminf( a.w, b.w );

    return result;
}

// Get max value for each pair of components
static inline struct vec4_f64 vec4_f64_max( struct vec4_f64 a, struct vec4_f64 b )
{
    struct vec4_f64 result = { 0 };

    result.x = fmaxf( a.x, b.x );
    result.y = fmaxf( a.y, b.y );
    result.z = fmaxf( a.z, b.z );
    result.w = fmaxf( a.w, b.w );

    return result;
}

// Calculate linear interpolation between two vectors
static inline struct vec4_f64 vec4_f64_lerp( struct vec4_f64 a, struct vec4_f64 b, double t )
{
    struct vec4_f64 result = { 0 };

    result.x = a.x + t * ( b.x - a.x );
    result.y = a.y + t * ( b.y - a.y );
    result.z = a.z + t * ( b.z - a.z );
    result.w = a.w + t * ( b.w - a.w );

    return result;
}

// Move Vector towards target
static inline struct vec4_f64 vec4_f64_move_towards( struct vec4_f64 v, struct vec4_f64 target, double max )
{
    struct vec4_f64 result = { 0 };

    double dx = target.x - v.x;
    double dy = target.y - v.y;
    double dz = target.z - v.z;
    double dw = target.w - v.w;
    double value = ( dx * dx ) + ( dy * dy ) + ( dz * dz ) + ( dw * dw );

    if ( ( value == 0 ) || ( ( max >= 0 ) && ( value <= max * max ) ) )
		return target;

    double dist = sqrtf( value );

    result.x = v.x + dx / dist * max;
    result.y = v.y + dy / dist * max;
    result.z = v.z + dz / dist * max;
    result.w = v.w + dw / dist * max;

    return result;
}

// Invert the given vector
static inline struct vec4_f64 vec4_f64_invert( struct vec4_f64 v )
{
    struct vec4_f64 result = { 1.0f / v.x, 1.0f / v.y, 1.0f / v.z, 1.0f / v.w };
    return result;
}

// Check whether two given vectors are almost equal
static inline int vec4_f64_equals( struct vec4_f64 p, struct vec4_f64 q, double epsilon )
{
    int result =
		( ( fabsf( p.x - q.x ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.x ), fabsf( q.x ) ) ) ) ) &&
        ( ( fabsf( p.y - q.y ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.y ), fabsf( q.y ) ) ) ) ) &&
        ( ( fabsf( p.z - q.z ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.z ), fabsf( q.z ) ) ) ) ) &&
        ( ( fabsf( p.w - q.w ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( p.w ), fabsf( q.w ) ) ) ) );
    return result;
}

#endif
