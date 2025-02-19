#include "../../util/types.h"

#define _VEC2_TYPE struct vec2_f32
#define _BASE_TYPE float
#define _FUNC_SPEC static inline
#define _FUNC_PREFIX vec2_f32
#define _BASE_SUFFIX f
#define _SIN sinf
#define _COS cosf
#define _TAN tanf
#define _ATAN2 atan2f
#define _SQRT sqrtf
#define _ABS fabsf
#define _MIN fminf
#define _MAX fminf

#define _CONCAT( _a, _b ) _a##_b
#define MATHLIB _CONCAT( <math, .h> )
#include MATHLIB

#define _NAME_HELPER( _prefix, _fn ) _CONCAT( _prefix, _##_fn )
#define _FUNC_NAME( _fn ) _NAME_HELPER( _FUNC_PREFIX, _fn )

#define _LITERAL_HELPER( _v, _s ) _CONCAT( _v, _s )
#define _LITERAL( _v ) _LITERAL_HELPER( _v, _BASE_SUFFIX )

// Vector2 with components value LIT( 0.0 )
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( zero )( void )
{
    _VEC2_TYPE result = { _LITERAL( 0.0 ), _LITERAL( 0.0 ) };
    return result;
}

// Vector2 with components value LIT( 1.0 )
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( one )( void )
{
    _VEC2_TYPE result = { _LITERAL( 1.0 ), _LITERAL( 1.0 ) };
    return result;
}

// Add two vectors (a + b)
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( add )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _VEC2_TYPE result = { a.x + b.x, a.y + b.y };
    return result;
}

// Add a value to a vector
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( add_val )( _VEC2_TYPE v, _BASE_TYPE val )
{
    _VEC2_TYPE result = { v.x + val, v.y + val };
    return result;
}

// Subtract two vectors (a - b)
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( sub )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _VEC2_TYPE result = { a.x - b.x, a.y - b.y };
    return result;
}

// Subtract a value from a vector
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( sub_val )( _VEC2_TYPE v, _BASE_TYPE val )
{
    _VEC2_TYPE result = { v.x - val, v.y - val };
    return result;
}

// Calculate the length of a vector
_FUNC_SPEC _BASE_TYPE _FUNC_NAME( len )( _VEC2_TYPE v )
{
    _BASE_TYPE result = _SQRT( ( v.x * v.x ) + ( v.y * v.y ) );
    return result;
}

// Calculate the squared length of a vector
_FUNC_SPEC _BASE_TYPE _FUNC_NAME( len_sq )( _VEC2_TYPE v )
{
    _BASE_TYPE result = ( v.x * v.x ) + ( v.y * v.y );
    return result;
}

// Calculate two vectors dot product
_FUNC_SPEC _BASE_TYPE _FUNC_NAME( dot )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _BASE_TYPE result = ( a.x * b.x ) + ( a.y * b.y );
    return result;
}

// Calculate distance between two vectors
_FUNC_SPEC _BASE_TYPE _FUNC_NAME( dist )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _BASE_TYPE result = _SQRT( ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) );
    return result;
}

// Calculate squared distance between two vectors
_FUNC_SPEC _BASE_TYPE _FUNC_NAME( dist_sq )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _BASE_TYPE result = ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y );
    return result;
}

// Calculate angle between two vectors
// NOTE: Angle is calculated from origin point (0, 0)
_FUNC_SPEC _BASE_TYPE _FUNC_NAME( angle )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _BASE_TYPE result = _LITERAL( 0.0 );

    _BASE_TYPE dot = a.x * b.x + a.y * b.y;
    _BASE_TYPE det = a.x * b.y - a.y * b.x;

    result = _ATAN2( det, dot );

    return result;
}

// Calculate angle defined by a two vectors line
// NOTE: Parameters need to be normalized
// Current implementation should be aligned with glm::angle
_FUNC_SPEC _BASE_TYPE _FUNC_NAME( line_angle )( _VEC2_TYPE start, _VEC2_TYPE end )
{
    _BASE_TYPE result = _LITERAL( 0.0 );

    result = -_ATAN2( end.y - start.y, end.x - start.x );

    return result;
}

// Scale vector (multiply by value)
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( scale )( _VEC2_TYPE v, _BASE_TYPE scale )
{
    _VEC2_TYPE result = { v.x * scale, v.y * scale };
    return result;
}

// Multiply vector by vector
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( mul )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _VEC2_TYPE result = { a.x * b.x, a.y * b.y };
    return result;
}

// Negate vector
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( negate )( _VEC2_TYPE v )
{
    _VEC2_TYPE result = { -v.x, -v.y };
    return result;
}

// Divide vector by vector
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( div )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _VEC2_TYPE result = { a.x / b.x, a.y / b.y };

    return result;
}

// Normalize provided vector
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( normalize )( _VEC2_TYPE v )
{
    _VEC2_TYPE result = { 0 };

    _BASE_TYPE len = _SQRT( ( v.x * v.x ) + ( v.y * v.y ) );
    if ( len > 0 )
    {
        _BASE_TYPE ilen = _LITERAL( 1.0 ) / len;
        result.x = v.x * ilen;
        result.y = v.y * ilen;
    }

    return result;
}

// Transforms a TYPE by a given Matrix
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( transform )( _VEC2_TYPE v, struct mat4_f32 m )
{
    _VEC2_TYPE result = { 0 };

    _BASE_TYPE x = v.x;
    _BASE_TYPE y = v.y;
    _BASE_TYPE z = _LITERAL( 0.0 );

    result.x = m.m00 * x + m.m01 * y + m.m02 * z + m.m03;
    result.y = m.m10 * x + m.m11 * y + m.m12 * z + m.m13;

    return result;
}

// Calculate linear interpolation between two vectors
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( lerp )( _VEC2_TYPE a, _VEC2_TYPE b, _BASE_TYPE t )
{
    _VEC2_TYPE result = { 0 };

    result.x = a.x + t * ( b.x - a.x );
    result.y = a.y + t * ( b.y - a.y );

    return result;
}

// Calculate reflected vector to normal
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( reflect )( _VEC2_TYPE v, _VEC2_TYPE normal )
{
    _VEC2_TYPE result = { 0 };

    _BASE_TYPE dot = ( v.x * normal.x + v.y * normal.y );

    result.x = v.x - ( _LITERAL( 2.0 ) * normal.x ) * dot;
    result.y = v.y - ( _LITERAL( 2.0 ) * normal.y ) * dot;

    return result;
}

// Get min value for each pair of components
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( min )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _VEC2_TYPE result = { 0 };

    result.x = _MIN( a.x, b.x );
    result.y = _MIN( a.y, b.y );

    return result;
}

// Get max value for each pair of components
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( max )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _VEC2_TYPE result = { 0 };

    result.x = _MAX( a.x, b.x );
    result.y = _MAX( a.y, b.y );

    return result;
}

// Rotate vector by angle
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( rotate )( _VEC2_TYPE v, _BASE_TYPE angle )
{
    _VEC2_TYPE result = { 0 };

    _BASE_TYPE c = _COS( angle );
    _BASE_TYPE s = _SIN( angle );

    result.x = v.x * c - v.y * s;
    result.y = v.x * s + v.y * c;

    return result;
}

// Move Vector towards target
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( move_towards )( _VEC2_TYPE v, _VEC2_TYPE target, _BASE_TYPE max )
{
    _VEC2_TYPE result = { 0 };

    _BASE_TYPE dx = target.x - v.x;
    _BASE_TYPE dy = target.y - v.y;
    _BASE_TYPE value = ( dx * dx ) + ( dy * dy );

    if ( ( value == 0 ) || ( ( max >= 0 ) && ( value <= max * max ) ) )
        return target;

    _BASE_TYPE dist = _SQRT( value );

    result.x = v.x + dx / dist * max;
    result.y = v.y + dy / dist * max;

    return result;
}

// Invert the given vector
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( invert )( _VEC2_TYPE v )
{
    _VEC2_TYPE result = { _LITERAL( 1.0 ) / v.x, _LITERAL( 1.0 ) / v.y };
    return result;
}

// Clamp the components of the vector between
// min and max values specified by the given vectors
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( clamp )( _VEC2_TYPE v, _VEC2_TYPE min, _VEC2_TYPE max )
{
    _VEC2_TYPE result = { 0 };

    result.x = _MIN( max.x, _MAX( min.x, v.x ) );
    result.y = _MIN( max.y, _MAX( min.y, v.y ) );

    return result;
}

// Clamp the components of the vector between
// min and max values
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( clamp_val )( _VEC2_TYPE v, _BASE_TYPE min, _BASE_TYPE max )
{
    _VEC2_TYPE result = { 0 };

    result.x = _MIN( max, _MAX( min, v.x ) );
    result.y = _MIN( max, _MAX( min, v.y ) );

    return result;
}

// Clamp the magnitude of the vector between two min and max values
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( clamp_len )( _VEC2_TYPE v, _BASE_TYPE min, _BASE_TYPE max )
{
    _VEC2_TYPE result = v;

    _BASE_TYPE len = ( v.x * v.x ) + ( v.y * v.y );
    if ( len > _LITERAL( 0.0 ) )
    {
        len = _SQRT( len );

        _BASE_TYPE scale = _LITERAL( 1.0 );    // By default, 1 as the neutral element.
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
_FUNC_SPEC int _FUNC_NAME( equals )( _VEC2_TYPE p, _VEC2_TYPE q, _BASE_TYPE epsilon )
{
    int result =
        ( ( _ABS( p.x - q.x ) ) <= ( epsilon * _MAX( _LITERAL( 1.0 ), _MAX( _ABS( p.x ), _ABS( q.x ) ) ) ) ) &&
        ( ( _ABS( p.y - q.y ) ) <= ( epsilon * _MAX( _LITERAL( 1.0 ), _MAX( _ABS( p.y ), _ABS( q.y ) ) ) ) );

    return result;
}

// Compute the direction of a refracted ray
// v: normalized direction of the incoming ray
// n: normalized normal vector of the interface of two optical media
// r: ratio of the refractive index of the medium from where the ray comes
//    to the refractive index of the medium on the other side of the surface
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( refract )( _VEC2_TYPE v, _VEC2_TYPE n, _BASE_TYPE r )
{
    _VEC2_TYPE result = { 0 };

    _BASE_TYPE dot = v.x * n.x + v.y * n.y;
    _BASE_TYPE d = _LITERAL( 1.0 ) - r * r * ( _LITERAL( 1.0 ) - dot * dot );

    if ( d >= _LITERAL( 0.0 ) )
    {
        d = _SQRT( d );
        v.x = r * v.x - ( r * dot + d ) * n.x;
        v.y = r * v.y - ( r * dot + d ) * n.y;

        result = v;
    }

    return result;
}