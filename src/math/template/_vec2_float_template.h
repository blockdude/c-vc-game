#include "../../types.h"
#include <math.h>

#define VEC2_TYPE struct vec2_f32
#define VEC2_BASE_TYPE float
#define VEC2_FUNCTION_SPEC static inline
#define VEC2_FUNCTION_PREFIX vec2_f32

#if ( VEC2_BASE_TYPE == float )

#define VEC2_SIN sinf
#define VEC2_COS cosf
#define VEC2_TAN tanf
#define VEC2_ATAN2 atan2f
#define VEC2_SQRT sqrtf
#define VEC2_ABS fabsf
#define VEC2_MIN fminf
#define VEC2_MAX fminf
#define VEC2_BASE_TYPE_SUFFIX f

#elif ( VEC2_BASE_TYPE == double )

#define VEC2_SIN sin
#define VEC2_COS cos
#define VEC2_TAN tan
#define VEC2_ATAN2 atan2
#define VEC2_SQRT sqrt
#define VEC2_ABS fabs
#define VEC2_MIN fmin
#define VEC2_MAX fmin
#define VEC2_BASE_TYPE_SUFFIX

#elif ( VEC2_BASE_TYPE == long double )

#define VEC2_SIN sinl
#define VEC2_COS cosl
#define VEC2_TAN tanl
#define VEC2_ATAN2 atan2l
#define VEC2_SQRT sqrtl
#define VEC2_ABS fabsl
#define VEC2_MIN fminl
#define VEC2_MAX fminl
#define VEC2_BASE_TYPE_SUFFIX l

#endif

#define CAT( _a, _b ) _a##_b

#define DECL_HELPER( _prefix, _fn ) CAT( _prefix, _##_fn )
#define DECL( _fn ) DECL_HELPER( VEC2_FUNCTION_PREFIX, _fn )

#define LIT_HELPER( _v, _s ) CAT( _v, _s )
#define LIT( _v ) LIT_HELPER( _v, VEC2_BASE_TYPE_SUFFIX )

// Vector2 with components value LIT( 0.0 )
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( zero )( void )
{
    VEC2_TYPE result = { LIT( 0.0 ), LIT( 0.0 ) };
    return result;
}

// Vector2 with components value LIT( 1.0 )
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( one )( void )
{
    VEC2_TYPE result = { LIT( 1.0 ), LIT( 1.0 ) };
    return result;
}

// Add two vectors (a + b)
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( add )( VEC2_TYPE a, VEC2_TYPE b )
{
    VEC2_TYPE result = { a.x + b.x, a.y + b.y };
    return result;
}

// Add a value to a vector
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( add_val )( VEC2_TYPE v, VEC2_BASE_TYPE val )
{
    VEC2_TYPE result = { v.x + val, v.y + val };
    return result;
}

// Subtract two vectors (a - b)
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( sub)( VEC2_TYPE a, VEC2_TYPE b )
{
    VEC2_TYPE result = { a.x - b.x, a.y - b.y };
    return result;
}

// Subtract a value from a vector
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( sub_val )( VEC2_TYPE v, VEC2_BASE_TYPE val )
{
    VEC2_TYPE result = { v.x - val, v.y - val };
    return result;
}

// Calculate the length of a vector
VEC2_FUNCTION_SPEC VEC2_BASE_TYPE DECL( len )( VEC2_TYPE v )
{
    VEC2_BASE_TYPE result = VEC2_SQRT( ( v.x * v.x ) + ( v.y * v.y ) );
    return result;
}

// Calculate the squared length of a vector
VEC2_FUNCTION_SPEC VEC2_BASE_TYPE DECL( len_sq )( VEC2_TYPE v )
{
    VEC2_BASE_TYPE result = ( v.x * v.x ) + ( v.y * v.y );
    return result;
}

// Calculate two vectors dot product
VEC2_FUNCTION_SPEC VEC2_BASE_TYPE DECL( dot )( VEC2_TYPE a, VEC2_TYPE b )
{
    VEC2_BASE_TYPE result = ( a.x * b.x ) + ( a.y * b.y );
    return result;
}

// Calculate distance between two vectors
VEC2_FUNCTION_SPEC VEC2_BASE_TYPE DECL( dist )( VEC2_TYPE a, VEC2_TYPE b )
{
    VEC2_BASE_TYPE result = VEC2_SQRT( ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) );
    return result;
}

// Calculate squared distance between two vectors
VEC2_FUNCTION_SPEC VEC2_BASE_TYPE DECL( dist_sq )( VEC2_TYPE a, VEC2_TYPE b )
{
    VEC2_BASE_TYPE result = ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y );
    return result;
}

// Calculate angle between two vectors
// NOTE: Angle is calculated from origin point (0, 0)
VEC2_FUNCTION_SPEC VEC2_BASE_TYPE DECL( angle )( VEC2_TYPE a, VEC2_TYPE b )
{
    VEC2_BASE_TYPE result = LIT( 0.0 );

    VEC2_BASE_TYPE dot = a.x * b.x + a.y * b.y;
    VEC2_BASE_TYPE det = a.x * b.y - a.y * b.x;

    result = VEC2_ATAN2( det, dot );

    return result;
}

// Calculate angle defined by a two vectors line
// NOTE: Parameters need to be normalized
// Current implementation should be aligned with glm::angle
VEC2_FUNCTION_SPEC VEC2_BASE_TYPE DECL( line_angle )( VEC2_TYPE start, VEC2_TYPE end )
{
    VEC2_BASE_TYPE result = LIT( 0.0 );

    result = -VEC2_ATAN2( end.y - start.y, end.x - start.x );

    return result;
}

// Scale vector (multiply by value)
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( scale )( VEC2_TYPE v, VEC2_BASE_TYPE scale )
{
    VEC2_TYPE result = { v.x * scale, v.y * scale };
    return result;
}

// Multiply vector by vector
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( mul )( VEC2_TYPE a, VEC2_TYPE b )
{
    VEC2_TYPE result = { a.x * b.x, a.y * b.y };
    return result;
}

// Negate vector
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( negate )( VEC2_TYPE v )
{
    VEC2_TYPE result = { -v.x, -v.y };
    return result;
}

// Divide vector by vector
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( div )( VEC2_TYPE a, VEC2_TYPE b )
{
    VEC2_TYPE result = { a.x / b.x, a.y / b.y };

    return result;
}

// Normalize provided vector
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( normalize )( VEC2_TYPE v )
{
    VEC2_TYPE result = { 0 };

    VEC2_BASE_TYPE len = VEC2_SQRT( ( v.x * v.x ) + ( v.y * v.y ) );
    if ( len > 0 )
    {
        VEC2_BASE_TYPE ilen = LIT( 1.0 ) / len;
        result.x = v.x * ilen;
        result.y = v.y * ilen;
    }

    return result;
}

// Transforms a TYPE by a given Matrix
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( transform )( VEC2_TYPE v, struct mat4_f32 m )
{
    VEC2_TYPE result = { 0 };

    VEC2_BASE_TYPE x = v.x;
    VEC2_BASE_TYPE y = v.y;
    VEC2_BASE_TYPE z = LIT( 0.0 );

    result.x = m.m00 * x + m.m01 * y + m.m02 * z + m.m03;
    result.y = m.m10 * x + m.m11 * y + m.m12 * z + m.m13;

    return result;
}

// Calculate linear interpolation between two vectors
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( lerp )( VEC2_TYPE a, VEC2_TYPE b, VEC2_BASE_TYPE t )
{
    VEC2_TYPE result = { 0 };

    result.x = a.x + t * ( b.x - a.x );
    result.y = a.y + t * ( b.y - a.y );

    return result;
}

// Calculate reflected vector to normal
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( reflect )( VEC2_TYPE v, VEC2_TYPE normal )
{
    VEC2_TYPE result = { 0 };

    VEC2_BASE_TYPE dot = ( v.x * normal.x + v.y * normal.y );

    result.x = v.x - ( LIT( 2.0 ) * normal.x ) * dot;
    result.y = v.y - ( LIT( 2.0 ) * normal.y ) * dot;

    return result;
}

// Get min value for each pair of components
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( min )( VEC2_TYPE a, VEC2_TYPE b )
{
    VEC2_TYPE result = { 0 };

    result.x = VEC2_MIN( a.x, b.x );
    result.y = VEC2_MIN( a.y, b.y );

    return result;
}

// Get max value for each pair of components
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( max )( VEC2_TYPE a, VEC2_TYPE b )
{
    VEC2_TYPE result = { 0 };

    result.x = VEC2_MAX( a.x, b.x );
    result.y = VEC2_MAX( a.y, b.y );

    return result;
}

// Rotate vector by angle
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( rotate )( VEC2_TYPE v, VEC2_BASE_TYPE angle )
{
    VEC2_TYPE result = { 0 };

    VEC2_BASE_TYPE cos = VEC2_COS( angle );
    VEC2_BASE_TYPE sin = VEC2_SIN( angle );

    result.x = v.x * cos - v.y * sin;
    result.y = v.x * sin + v.y * cos;

    return result;
}

// Move Vector towards target
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( move_towards )( VEC2_TYPE v, VEC2_TYPE target, VEC2_BASE_TYPE max )
{
    VEC2_TYPE result = { 0 };

    VEC2_BASE_TYPE dx = target.x - v.x;
    VEC2_BASE_TYPE dy = target.y - v.y;
    VEC2_BASE_TYPE value = ( dx * dx ) + ( dy * dy );

    if ( ( value == 0 ) || ( ( max >= 0 ) && ( value <= max * max ) ) )
        return target;

    VEC2_BASE_TYPE dist = VEC2_SQRT( value );

    result.x = v.x + dx / dist * max;
    result.y = v.y + dy / dist * max;

    return result;
}

// Invert the given vector
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( invert )( VEC2_TYPE v )
{
    VEC2_TYPE result = { LIT( 1.0 ) / v.x, LIT( 1.0 ) / v.y };
    return result;
}

// Clamp the components of the vector between
// min and max values specified by the given vectors
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( clamp )( VEC2_TYPE v, VEC2_TYPE min, VEC2_TYPE max )
{
    VEC2_TYPE result = { 0 };

    result.x = VEC2_MIN( max.x, VEC2_MAX( min.x, v.x ) );
    result.y = VEC2_MIN( max.y, VEC2_MAX( min.y, v.y ) );

    return result;
}

// Clamp the components of the vector between
// min and max values
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( clamp_val )( VEC2_TYPE v, VEC2_BASE_TYPE min, VEC2_BASE_TYPE max )
{
    VEC2_TYPE result = { 0 };

    result.x = VEC2_MIN( max, VEC2_MAX( min, v.x ) );
    result.y = VEC2_MIN( max, VEC2_MAX( min, v.y ) );

    return result;
}

// Clamp the magnitude of the vector between two min and max values
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( clamp_len )( VEC2_TYPE v, VEC2_BASE_TYPE min, VEC2_BASE_TYPE max )
{
    VEC2_TYPE result = v;

    VEC2_BASE_TYPE len = ( v.x * v.x ) + ( v.y * v.y );
    if ( len > LIT( 0.0 ) )
    {
        len = VEC2_SQRT( len );

        VEC2_BASE_TYPE scale = LIT( 1.0 );    // By default, 1 as the neutral element.
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
VEC2_FUNCTION_SPEC int DECL( equals )( VEC2_TYPE p, VEC2_TYPE q, VEC2_BASE_TYPE epsilon )
{
    int result =
        ( ( VEC2_ABS( p.x - q.x ) ) <= ( epsilon * VEC2_MAX( LIT( 1.0 ), VEC2_MAX( VEC2_ABS( p.x ), VEC2_ABS( q.x ) ) ) ) ) &&
        ( ( VEC2_ABS( p.y - q.y ) ) <= ( epsilon * VEC2_MAX( LIT( 1.0 ), VEC2_MAX( VEC2_ABS( p.y ), VEC2_ABS( q.y ) ) ) ) );

    return result;
}

// Compute the direction of a refracted ray
// v: normalized direction of the incoming ray
// n: normalized normal vector of the interface of two optical media
// r: ratio of the refractive index of the medium from where the ray comes
//    to the refractive index of the medium on the other side of the surface
VEC2_FUNCTION_SPEC VEC2_TYPE DECL( refract )( VEC2_TYPE v, VEC2_TYPE n, VEC2_BASE_TYPE r )
{
    VEC2_TYPE result = { 0 };

    VEC2_BASE_TYPE dot = v.x * n.x + v.y * n.y;
    VEC2_BASE_TYPE d = LIT( 1.0 ) - r * r * ( LIT( 1.0 ) - dot * dot );

    if ( d >= LIT( 0.0 ) )
    {
        d = VEC2_SQRT( d );
        v.x = r * v.x - ( r * dot + d ) * n.x;
        v.y = r * v.y - ( r * dot + d ) * n.y;

        result = v;
    }

    return result;
}