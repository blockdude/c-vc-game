#if defined( LINEAR_ALGEBRA_CLEANUP )

#undef _VEC2_TYPE
#undef _VEC3_TYPE
#undef _VEC4_TYPE
#undef _QUAT_TYPE
#undef _MAT4_TYPE
#undef _BASE_TYPE

#undef _FUNC_SPEC
#undef _FUNC_CONV

#undef _VEC2_PREFIX
#undef _VEC3_PREFIX
#undef _VEC4_PREFIX
#undef _MAT4_PREFIX
#undef _QUAT_PREFIX
#undef _BASE_SUFFIX

#undef _SIN
#undef _COS
#undef _TAN
#undef _ATAN2
#undef _SQRT
#undef _ABS
#undef _MIN
#undef _MAX

#undef _CONCAT
#undef _LITERAL_HELPER
#undef _LITERAL
#undef _NAME_HELPER
#undef _FUNC_VEC2
#undef _FUNC_VEC3
#undef _FUNC_VEC4
#undef _FUNC_MAT4
#undef _FUNC_QUAT

#undef LINEAR_ALGEBRA_CLEANUP

#else

#include "../../util/types.h"
#include <math.h>

#if defined( LINEAR_ALGEBRA_HEADER )
#undef LINEAR_ALGEBRA_HEADER

#define _FUNC_SPEC
#define _FUNC_CONV

#elif defined ( LINEAR_ALGEBRA_IMPLEMENTATION )
#undef LINEAR_ALGEBRA_IMPLEMENTATION

#define _FUNC_SPEC
#define _FUNC_CONV

#endif

#if defined( LINEAR_ALGEBRA_FLT )
#undef LINEAR_ALGEBRA_FLT

#define _VEC2_TYPE struct vec2
#define _VEC3_TYPE struct vec3
#define _VEC4_TYPE struct vec4
#define _QUAT_TYPE struct quat
#define _MAT4_TYPE struct mat4
#define _BASE_TYPE float

#define _VEC2_PREFIX vec2
#define _VEC3_PREFIX vec3
#define _VEC4_PREFIX vec4
#define _MAT4_PREFIX mat4
#define _QUAT_PREFIX quat
#define _BASE_SUFFIX f

#define _SIN sinf
#define _COS cosf
#define _TAN tanf
#define _ATAN2 atan2f
#define _SQRT sqrtf
#define _ABS fabsf
#define _MIN fminf
#define _MAX fminf

#elif defined( LINEAR_ALGEBRA_F32 )
#undef LINEAR_ALGEBRA_F32

#define _VEC2_TYPE struct vec2_f32
#define _VEC3_TYPE struct vec3_f32
#define _VEC4_TYPE struct vec4_f32
#define _QUAT_TYPE struct quat_f32
#define _MAT4_TYPE struct mat4_f32
#define _BASE_TYPE float

#define _VEC2_PREFIX vec2_f32
#define _VEC3_PREFIX vec3_f32
#define _VEC4_PREFIX vec4_f32
#define _MAT4_PREFIX mat4_f32
#define _QUAT_PREFIX quat_f32
#define _BASE_SUFFIX f

#define _SIN sinf
#define _COS cosf
#define _TAN tanf
#define _ATAN2 atan2f
#define _SQRT sqrtf
#define _ABS fabsf
#define _MIN fminf
#define _MAX fminf

#elif defined( LINEAR_ALGEBRA_F64 )
#undef LINEAR_ALGEBRA_F64

#define _VEC2_TYPE struct vec2_f64
#define _VEC3_TYPE struct vec3_f64
#define _VEC4_TYPE struct vec4_f64
#define _QUAT_TYPE struct quat_f64
#define _MAT4_TYPE struct mat4_f64
#define _BASE_TYPE double

#define _VEC2_PREFIX vec2_f64
#define _VEC3_PREFIX vec3_f64
#define _VEC4_PREFIX vec4_f64
#define _MAT4_PREFIX mat4_f64
#define _QUAT_PREFIX quat_f64
#define _BASE_SUFFIX f

#define _SIN sin
#define _COS cos
#define _TAN tan
#define _ATAN2 atan2
#define _SQRT sqrt
#define _ABS fabs
#define _MIN fmin
#define _MAX fmin

#else
#error "Only F32 and F64 version are supported"
#endif



#define _CONCAT( _a, _b ) _a##_b

#define _LITERAL_HELPER( _v, _s ) _CONCAT( _v, _s )
#define _LITERAL( _v ) _LITERAL_HELPER( _v, _BASE_SUFFIX )

#define _NAME_HELPER( _prefix, _fn ) _CONCAT( _prefix, _##_fn )

#define _FUNC_VEC2( _fn ) _NAME_HELPER( _VEC2_PREFIX, _fn )
#define _FUNC_VEC3( _fn ) _NAME_HELPER( _VEC3_PREFIX, _fn )
#define _FUNC_VEC4( _fn ) _NAME_HELPER( _VEC4_PREFIX, _fn )
#define _FUNC_MAT4( _fn ) _NAME_HELPER( _MAT4_PREFIX, _fn )
#define _FUNC_QUAT( _fn ) _NAME_HELPER( _QUAT_PREFIX, _fn )



/*
 * =============================
 * -----------------------------
 * VECTOR2
 * -----------------------------
 */

#ifdef LINEAR_ALGEBRA_VEC2_HEADER
#undef LINEAR_ALGEBRA_VEC2_HEADER

extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( zero )( void );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( one )( void );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( add )( _VEC2_TYPE a, _VEC2_TYPE b );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( add_val )( _VEC2_TYPE v, _BASE_TYPE val );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( sub )( _VEC2_TYPE a, _VEC2_TYPE b );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( sub_val )( _VEC2_TYPE v, _BASE_TYPE val );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC2( len )( _VEC2_TYPE v );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC2( len_sq )( _VEC2_TYPE v );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC2( dot )( _VEC2_TYPE a, _VEC2_TYPE b );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC2( dist )( _VEC2_TYPE a, _VEC2_TYPE b );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC2( dist_sq )( _VEC2_TYPE a, _VEC2_TYPE b );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC2( angle )( _VEC2_TYPE a, _VEC2_TYPE b );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC2( line_angle )( _VEC2_TYPE start, _VEC2_TYPE end );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( scale )( _VEC2_TYPE v, _BASE_TYPE scale );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( mul )( _VEC2_TYPE a, _VEC2_TYPE b );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( negate )( _VEC2_TYPE v );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( div )( _VEC2_TYPE a, _VEC2_TYPE b );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( normalize )( _VEC2_TYPE v );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( transform )( _VEC2_TYPE v, _MAT4_TYPE m );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( lerp )( _VEC2_TYPE a, _VEC2_TYPE b, _BASE_TYPE t );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( reflect )( _VEC2_TYPE v, _VEC2_TYPE normal );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( min )( _VEC2_TYPE a, _VEC2_TYPE b );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( max )( _VEC2_TYPE a, _VEC2_TYPE b );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( rotate )( _VEC2_TYPE v, _BASE_TYPE angle );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( move_towards )( _VEC2_TYPE v, _VEC2_TYPE target, _BASE_TYPE max );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( invert )( _VEC2_TYPE v );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( clamp )( _VEC2_TYPE v, _VEC2_TYPE min, _VEC2_TYPE max );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( clamp_val )( _VEC2_TYPE v, _BASE_TYPE min, _BASE_TYPE max );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( clamp_len )( _VEC2_TYPE v, _BASE_TYPE min, _BASE_TYPE max );
extern _FUNC_SPEC int        _FUNC_CONV _FUNC_VEC2( equals )( _VEC2_TYPE p, _VEC2_TYPE q, _BASE_TYPE epsilon );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( refract )( _VEC2_TYPE v, _VEC2_TYPE n, _BASE_TYPE r );

#endif



#ifdef LINEAR_ALGEBRA_VEC2_IMPLEMENTATION
#undef LINEAR_ALGEBRA_VEC2_IMPLEMENTATION

// Vector2 with components value LIT( 0.0 )
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( zero )( void )
{
    _VEC2_TYPE result = { _LITERAL( 0.0 ), _LITERAL( 0.0 ) };
    return result;
}

// Vector2 with components value LIT( 1.0 )
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( one )( void )
{
    _VEC2_TYPE result = { _LITERAL( 1.0 ), _LITERAL( 1.0 ) };
    return result;
}

// Add two vectors (a + b)
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( add )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _VEC2_TYPE result = { a.x + b.x, a.y + b.y };
    return result;
}

// Add a value to a vector
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( add_val )( _VEC2_TYPE v, _BASE_TYPE val )
{
    _VEC2_TYPE result = { v.x + val, v.y + val };
    return result;
}

// Subtract two vectors (a - b)
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( sub )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _VEC2_TYPE result = { a.x - b.x, a.y - b.y };
    return result;
}

// Subtract a value from a vector
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( sub_val )( _VEC2_TYPE v, _BASE_TYPE val )
{
    _VEC2_TYPE result = { v.x - val, v.y - val };
    return result;
}

// Calculate the length of a vector
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC2( len )( _VEC2_TYPE v )
{
    _BASE_TYPE result = _SQRT( ( v.x * v.x ) + ( v.y * v.y ) );
    return result;
}

// Calculate the squared length of a vector
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC2( len_sq )( _VEC2_TYPE v )
{
    _BASE_TYPE result = ( v.x * v.x ) + ( v.y * v.y );
    return result;
}

// Calculate two vectors dot product
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC2( dot )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _BASE_TYPE result = ( a.x * b.x ) + ( a.y * b.y );
    return result;
}

// Calculate distance between two vectors
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC2( dist )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _BASE_TYPE result = _SQRT( ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) );
    return result;
}

// Calculate squared distance between two vectors
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC2( dist_sq )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _BASE_TYPE result = ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y );
    return result;
}

// Calculate angle between two vectors
// NOTE: Angle is calculated from origin point (0, 0)
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC2( angle )( _VEC2_TYPE a, _VEC2_TYPE b )
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
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC2( line_angle )( _VEC2_TYPE start, _VEC2_TYPE end )
{
    _BASE_TYPE result = _LITERAL( 0.0 );

    result = -_ATAN2( end.y - start.y, end.x - start.x );

    return result;
}

// Scale vector (multiply by value)
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( scale )( _VEC2_TYPE v, _BASE_TYPE scale )
{
    _VEC2_TYPE result = { v.x * scale, v.y * scale };
    return result;
}

// Multiply vector by vector
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( mul )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _VEC2_TYPE result = { a.x * b.x, a.y * b.y };
    return result;
}

// Negate vector
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( negate )( _VEC2_TYPE v )
{
    _VEC2_TYPE result = { -v.x, -v.y };
    return result;
}

// Divide vector by vector
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( div )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _VEC2_TYPE result = { a.x / b.x, a.y / b.y };

    return result;
}

// Normalize provided vector
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( normalize )( _VEC2_TYPE v )
{
    _VEC2_TYPE result = { 0 };

    _BASE_TYPE len = _SQRT( ( v.x * v.x ) + ( v.y * v.y ) );
    if ( len > _LITERAL( 0.0 ) )
    {
        _BASE_TYPE ilen = _LITERAL( 1.0 ) / len;
        result.x = v.x * ilen;
        result.y = v.y * ilen;
    }

    return result;
}

// Transforms a TYPE by a given Matrix
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( transform )( _VEC2_TYPE v, _MAT4_TYPE m )
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
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( lerp )( _VEC2_TYPE a, _VEC2_TYPE b, _BASE_TYPE t )
{
    _VEC2_TYPE result = { 0 };

    result.x = a.x + t * ( b.x - a.x );
    result.y = a.y + t * ( b.y - a.y );

    return result;
}

// Calculate reflected vector to normal
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( reflect )( _VEC2_TYPE v, _VEC2_TYPE normal )
{
    _VEC2_TYPE result = { 0 };

    _BASE_TYPE dot = ( v.x * normal.x + v.y * normal.y );

    result.x = v.x - ( _LITERAL( 2.0 ) * normal.x ) * dot;
    result.y = v.y - ( _LITERAL( 2.0 ) * normal.y ) * dot;

    return result;
}

// Get min value for each pair of components
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( min )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _VEC2_TYPE result = { 0 };

    result.x = _MIN( a.x, b.x );
    result.y = _MIN( a.y, b.y );

    return result;
}

// Get max value for each pair of components
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( max )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _VEC2_TYPE result = { 0 };

    result.x = _MAX( a.x, b.x );
    result.y = _MAX( a.y, b.y );

    return result;
}

// Rotate vector by angle
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( rotate )( _VEC2_TYPE v, _BASE_TYPE angle )
{
    _VEC2_TYPE result = { 0 };

    _BASE_TYPE c = _COS( angle );
    _BASE_TYPE s = _SIN( angle );

    result.x = v.x * c - v.y * s;
    result.y = v.x * s + v.y * c;

    return result;
}

// Move Vector towards target
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( move_towards )( _VEC2_TYPE v, _VEC2_TYPE target, _BASE_TYPE max )
{
    _VEC2_TYPE result = { 0 };

    _BASE_TYPE dx = target.x - v.x;
    _BASE_TYPE dy = target.y - v.y;
    _BASE_TYPE value = ( dx * dx ) + ( dy * dy );

    if ( ( value == _LITERAL( 0.0 ) ) || ( ( max >= _LITERAL( 0.0 ) ) && ( value <= max * max ) ) )
        return target;

    _BASE_TYPE dist = _SQRT( value );

    result.x = v.x + dx / dist * max;
    result.y = v.y + dy / dist * max;

    return result;
}

// Invert the given vector
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( invert )( _VEC2_TYPE v )
{
    _VEC2_TYPE result = { _LITERAL( 1.0 ) / v.x, _LITERAL( 1.0 ) / v.y };
    return result;
}

// Clamp the components of the vector between
// min and max values specified by the given vectors
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( clamp )( _VEC2_TYPE v, _VEC2_TYPE min, _VEC2_TYPE max )
{
    _VEC2_TYPE result = { 0 };

    result.x = _MIN( max.x, _MAX( min.x, v.x ) );
    result.y = _MIN( max.y, _MAX( min.y, v.y ) );

    return result;
}

// Clamp the components of the vector between
// min and max values
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( clamp_val )( _VEC2_TYPE v, _BASE_TYPE min, _BASE_TYPE max )
{
    _VEC2_TYPE result = { 0 };

    result.x = _MIN( max, _MAX( min, v.x ) );
    result.y = _MIN( max, _MAX( min, v.y ) );

    return result;
}

// Clamp the magnitude of the vector between two min and max values
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( clamp_len )( _VEC2_TYPE v, _BASE_TYPE min, _BASE_TYPE max )
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
_FUNC_SPEC int _FUNC_CONV _FUNC_VEC2( equals )( _VEC2_TYPE p, _VEC2_TYPE q, _BASE_TYPE epsilon )
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
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( refract )( _VEC2_TYPE v, _VEC2_TYPE n, _BASE_TYPE r )
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

#endif

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * VECTOR3
 * -----------------------------
 */

#ifdef LINEAR_ALGEBRA_VEC3_HEADER
#undef LINEAR_ALGEBRA_VEC3_HEADER

extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( zero )( void );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( one )( void );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( add )( _VEC3_TYPE a, _VEC3_TYPE b );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( add_val )( _VEC3_TYPE v, _BASE_TYPE val );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( sub )( _VEC3_TYPE a, _VEC3_TYPE b );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( sub_val )( _VEC3_TYPE v, _BASE_TYPE val );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( scale )( _VEC3_TYPE v, _BASE_TYPE scale );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( mul )( _VEC3_TYPE a, _VEC3_TYPE b );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( cross )( _VEC3_TYPE a, _VEC3_TYPE b );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( perpendicular )( _VEC3_TYPE v );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( center )( _VEC3_TYPE a, _VEC3_TYPE b );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC3( len )( _VEC3_TYPE v );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC3( len_sq )( _VEC3_TYPE v );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC3( dot )( _VEC3_TYPE a, _VEC3_TYPE b );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC3( dist )( _VEC3_TYPE a, _VEC3_TYPE b );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC3( dist_sq )( _VEC3_TYPE a, _VEC3_TYPE b );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC3( angle )( _VEC3_TYPE a, _VEC3_TYPE b );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( negate )( _VEC3_TYPE v );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( div )( _VEC3_TYPE a, _VEC3_TYPE b );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( normalize )( _VEC3_TYPE v );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( project )( _VEC3_TYPE a, _VEC3_TYPE b );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( reject )( _VEC3_TYPE a, _VEC3_TYPE b );
extern _FUNC_SPEC void       _FUNC_CONV _FUNC_VEC3( ortho_normalize )( _VEC3_TYPE *a, _VEC3_TYPE *b );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( transform )( _VEC3_TYPE v, _MAT4_TYPE m );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( rotate )( _VEC3_TYPE v, _QUAT_TYPE q );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( rotate_around_axis )( _VEC3_TYPE v, _VEC3_TYPE axis, _BASE_TYPE angle );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( move_towards )( _VEC3_TYPE v, _VEC3_TYPE target, _BASE_TYPE max );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( lerp )( _VEC3_TYPE a, _VEC3_TYPE b, _BASE_TYPE t );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( cubic_hermite )( _VEC3_TYPE a, _VEC3_TYPE tan_a, _VEC3_TYPE b, _VEC3_TYPE tan_b, _BASE_TYPE t );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( reflect )( _VEC3_TYPE v, _VEC3_TYPE normal );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( min )( _VEC3_TYPE a, _VEC3_TYPE b );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( max )( _VEC3_TYPE a, _VEC3_TYPE b );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( barycenter )( _VEC3_TYPE p, _VEC3_TYPE a, _VEC3_TYPE b, _VEC3_TYPE c );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( unproject )( _VEC3_TYPE source, _MAT4_TYPE proj, _MAT4_TYPE view );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( invert )( _VEC3_TYPE v );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( clamp )( _VEC3_TYPE v, _VEC3_TYPE min, _VEC3_TYPE max );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( clamp_val )( _VEC3_TYPE v, _BASE_TYPE min, _BASE_TYPE max );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( clamp_len )( _VEC3_TYPE v, _BASE_TYPE min, _BASE_TYPE max );
extern _FUNC_SPEC int        _FUNC_CONV _FUNC_VEC3( equals )( _VEC3_TYPE p, _VEC3_TYPE q, _BASE_TYPE epsilon );
extern _FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( refract )( _VEC3_TYPE v, _VEC3_TYPE n, _BASE_TYPE r );

#endif



#ifdef LINEAR_ALGEBRA_VEC3_IMPLEMENTATION
#undef LINEAR_ALGEBRA_VEC3_IMPLEMENTATION

// Vector with components value 0.0f
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( zero )( void )
{
    _VEC3_TYPE result = {
        _LITERAL( 0.0 ),
        _LITERAL( 0.0 ),
        _LITERAL( 0.0 )
    };

    return result;
}

// Vector with components value 1.0f
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( one )( void )
{
    _VEC3_TYPE result = {
        _LITERAL( 1.0 ),
        _LITERAL( 1.0 ),
        _LITERAL( 1.0 )
    };

    return result;
}

// Add two vectors
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( add )( _VEC3_TYPE a, _VEC3_TYPE b )
{
    _VEC3_TYPE result = { a.x + b.x, a.y + b.y, a.z + b.z };
    return result;
}

// Add vector and float value
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( add_val )( _VEC3_TYPE v, _BASE_TYPE val )
{
    _VEC3_TYPE result = { v.x + val, v.y + val, v.z + val };
    return result;
}

// Subtract two vectors
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( sub )( _VEC3_TYPE a, _VEC3_TYPE b )
{
    _VEC3_TYPE result = { a.x - b.x, a.y - b.y, a.z - b.z };
    return result;
}

// Subtract vector by float value
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( sub_val )( _VEC3_TYPE v, _BASE_TYPE val )
{
    _VEC3_TYPE result = { v.x - val, v.y - val, v.z - val };
    return result;
}

// Multiply vector by scalar
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( scale )( _VEC3_TYPE v, _BASE_TYPE scale )
{
    _VEC3_TYPE result = { v.x * scale, v.y * scale, v.z * scale };
    return result;
}

// Multiply vector by vector
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( mul )( _VEC3_TYPE a, _VEC3_TYPE b )
{
    _VEC3_TYPE result = { a.x * b.x, a.y * b.y, a.z * b.z };
    return result;
}

// Calculate two vectors cross product
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( cross )( _VEC3_TYPE a, _VEC3_TYPE b )
{
    _VEC3_TYPE result = { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
    return result;
}

// Calculate one vector perpendicular vector
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( perpendicular )( _VEC3_TYPE v )
{
    _VEC3_TYPE result = { 0 };

    _BASE_TYPE min = _ABS( v.x );
    _VEC3_TYPE cardinal_axis = { _LITERAL( 1.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ) };

    if ( _ABS( v.y ) < min )
    {
        min = _ABS( v.y );
        _VEC3_TYPE tmp = { _LITERAL( 0.0 ), _LITERAL( 1.0 ), _LITERAL( 0.0 ) };
        cardinal_axis = tmp;
    }

    if ( _ABS( v.z ) < min )
    {
        _VEC3_TYPE tmp = { _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 1.0 ) };
        cardinal_axis = tmp;
    }

    // Cross product between vectors
    result.x = v.y * cardinal_axis.z - v.z * cardinal_axis.y;
    result.y = v.z * cardinal_axis.x - v.x * cardinal_axis.z;
    result.z = v.x * cardinal_axis.y - v.y * cardinal_axis.x;

    return result;
}

// Calcuate the center point of two vectors
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( center )( _VEC3_TYPE a, _VEC3_TYPE b )
{
    _VEC3_TYPE result = { _LITERAL( 0.0 ) };

    result.x = ( a.x + b.x ) / _LITERAL( 2.0 );
    result.y = ( a.y + b.y ) / _LITERAL( 2.0 );
    result.z = ( a.z + b.z ) / _LITERAL( 2.0 );

    return result;
}

// Calculate vector length
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC3( len )( _VEC3_TYPE v )
{
    _BASE_TYPE result = _SQRT( v.x * v.x + v.y * v.y + v.z * v.z );
    return result;
}

// Calculate vector square length
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC3( len_sq )( _VEC3_TYPE v )
{
    _BASE_TYPE result = v.x * v.x + v.y * v.y + v.z * v.z;
    return result;
}

// Calculate two vectors dot product
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC3( dot )( _VEC3_TYPE a, _VEC3_TYPE b )
{
    _BASE_TYPE result = ( a.x * b.x + a.y * b.y + a.z * b.z );
    return result;
}

// Calculate distance between two vectors
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC3( dist )( _VEC3_TYPE a, _VEC3_TYPE b )
{
    _BASE_TYPE result = _LITERAL( 0.0 );

    _BASE_TYPE dx = b.x - a.x;
    _BASE_TYPE dy = b.y - a.y;
    _BASE_TYPE dz = b.z - a.z;
    result = _SQRT( dx * dx + dy * dy + dz * dz );

    return result;
}

// Calculate square distance between two vectors
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC3( dist_sq )( _VEC3_TYPE a, _VEC3_TYPE b )
{
    _BASE_TYPE result = _LITERAL( 0.0 );

    _BASE_TYPE dx = b.x - a.x;
    _BASE_TYPE dy = b.y - a.y;
    _BASE_TYPE dz = b.z - a.z;
    result = dx * dx + dy * dy + dz * dz;

    return result;
}

// Calculate angle between two vectors
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC3( angle )( _VEC3_TYPE a, _VEC3_TYPE b )
{
    _BASE_TYPE result = _LITERAL( 0.0 );

    _VEC3_TYPE cross = { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
    _BASE_TYPE len = _SQRT( cross.x * cross.x + cross.y * cross.y + cross.z * cross.z );
    _BASE_TYPE dot = ( a.x * b.x + a.y * b.y + a.z * b.z );
    result = _ATAN2( len, dot );

    return result;
}

// Negate provided vector (invert direction)
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( negate )( _VEC3_TYPE v )
{
    _VEC3_TYPE result = { -v.x, -v.y, -v.z };
    return result;
}

// Divide vector by vector
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( div )( _VEC3_TYPE a, _VEC3_TYPE b )
{
    _VEC3_TYPE result = { a.x / b.x, a.y / b.y, a.z / b.z };
    return result;
}

// Normalize provided vector
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( normalize )( _VEC3_TYPE v )
{
    _VEC3_TYPE result = { 0 };

    _BASE_TYPE len = _SQRT( v.x * v.x + v.y * v.y + v.z * v.z );
    if ( len > _LITERAL( 0.0 ) )
    {
        _BASE_TYPE ilen = _LITERAL( 1.0 ) / len;
        result.x = v.x * ilen;
        result.y = v.y * ilen;
        result.z = v.z * ilen;
    }

    return result;
}

//Calculate the projection of the vector a on to b
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( project )( _VEC3_TYPE a, _VEC3_TYPE b )
{
    _VEC3_TYPE result = { 0 };

    // a dot b . b dot b
    _BASE_TYPE adb = ( a.x * b.x + a.y * b.y + a.z * b.z );
    _BASE_TYPE bdb = ( b.x * b.x + b.y * b.y + b.z * b.z );

    _BASE_TYPE mag = adb / bdb;

    result.x = b.x * mag;
    result.y = b.y * mag;
    result.z = b.z * mag;

    return result;
}

//Calculate the rejection of the vector v1 on to v2
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( reject )( _VEC3_TYPE a, _VEC3_TYPE b )
{
    _VEC3_TYPE result = { 0 };

    _BASE_TYPE adb = ( a.x * b.x + a.y * b.y + a.z * b.z );
    _BASE_TYPE bdb = ( b.x * b.x + b.y * b.y + b.z * b.z );

    _BASE_TYPE mag = adb / bdb;

    result.x = a.x - ( b.x * mag );
    result.y = a.y - ( b.y * mag );
    result.z = a.z - ( b.z * mag );

    return result;
}

// Orthonormalize provided vectors
// Makes vectors normalized and orthogonal to each other
// Gram-Schmidt function implementation
_FUNC_SPEC void _FUNC_CONV _FUNC_VEC3( ortho_normalize )( _VEC3_TYPE *a, _VEC3_TYPE *b )
{
    _BASE_TYPE len = _LITERAL( 0.0 );
    _BASE_TYPE ilen = _LITERAL( 0.0 );

    // normalize( *a );
    _VEC3_TYPE v = *a;
    len = _SQRT( v.x * v.x + v.y * v.y + v.z * v.z );
    if ( len == _LITERAL( 0.0 ) ) len = _LITERAL( 1.0 );
    ilen = _LITERAL( 1.0 ) / len;
    a->x *= ilen;
    a->y *= ilen;
    a->z *= ilen;

    // cross( *a, *b )
    _VEC3_TYPE an = { a->y * b->z - a->z * b->y, a->z * b->x - a->x * b->z, a->x * b->y - a->y * b->x };

    // normalize( an );
    v = an;
    len = _SQRT( v.x * v.x + v.y * v.y + v.z * v.z );
    if ( len == _LITERAL( 0.0 ) ) len = _LITERAL( 1.0 );
    ilen = _LITERAL( 1.0 ) / len;
    an.x *= ilen;
    an.y *= ilen;
    an.z *= ilen;

    // cross( an, *a )
    _VEC3_TYPE bn = { an.y * a->z - an.z * a->y, an.z * a->x - an.x * a->z, an.x * a->y - an.y * a->x };

    *b = bn;
}

// Transforms a _VEC3_TYPE by a given Matrix
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( transform )( _VEC3_TYPE v, _MAT4_TYPE m )
{
    _VEC3_TYPE result = { 0 };

    _BASE_TYPE x = v.x;
    _BASE_TYPE y = v.y;
    _BASE_TYPE z = v.z;

    result.x = m.m00 * x + m.m01 * y + m.m02 * z + m.m03;
    result.y = m.m10 * x + m.m11 * y + m.m12 * z + m.m13;
    result.z = m.m20 * x + m.m21 * y + m.m22 * z + m.m23;

    return result;
}

// Transform a vector by quaternion rotation
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( rotate )( _VEC3_TYPE v, _QUAT_TYPE q )
{
    _VEC3_TYPE result = { 0 };

    const _BASE_TYPE two = _LITERAL( 2.0 );
    result.x = v.x * ( q.x * q.x + q.w * q.w - q.y * q.y - q.z * q.z ) + v.y * ( two * q.x * q.y - two * q.w * q.z ) + v.z * ( two * q.x * q.z + two * q.w * q.y );
    result.y = v.x * ( two * q.w * q.z + two * q.x * q.y ) + v.y * ( q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z ) + v.z * ( -two * q.w * q.x + two * q.y * q.z );
    result.z = v.x * ( -two * q.w * q.y + two * q.x * q.z ) + v.y * ( two * q.w * q.x + two * q.y * q.z ) + v.z * ( q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z );

    return result;
}

// Rotates a vector around an axis
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( rotate_around_axis )( _VEC3_TYPE v, _VEC3_TYPE axis, _BASE_TYPE angle )
{
    // Using Euler-Rodrigues Formula
    // Ref.: https://en.wikipedia.org/w/index.php?title=Euler%E2%80%93Rodrigues_formula

    _VEC3_TYPE result = v;

    // vec3_f32_normalize(axis);
    _BASE_TYPE len = _SQRT( axis.x * axis.x + axis.y * axis.y + axis.z * axis.z );
    if ( len == _LITERAL( 0.0 ) ) len = _LITERAL( 1.0 );
    _BASE_TYPE ilen = _LITERAL( 1.0 ) / len;
    axis.x *= ilen;
    axis.y *= ilen;
    axis.z *= ilen;

    angle /= _LITERAL( 2.0 );
    _BASE_TYPE a = _SIN( angle );
    _BASE_TYPE b = axis.x * a;
    _BASE_TYPE c = axis.y * a;
    _BASE_TYPE d = axis.z * a;
    a = _COS( angle );
    _VEC3_TYPE w = { b, c, d };

    // vec3_f32_cross( w, v )
    _VEC3_TYPE wv = { w.y * v.z - w.z * v.y, w.z * v.x - w.x * v.z, w.x * v.y - w.y * v.x };

    // vec3_f32_cross( w, wv )
    _VEC3_TYPE wwv = { w.y * wv.z - w.z * wv.y, w.z * wv.x - w.x * wv.z, w.x * wv.y - w.y * wv.x };

    // vec3_f32_scale( wv, 2 * a )
    a *= _LITERAL( 2.0 );
    wv.x *= a;
    wv.y *= a;
    wv.z *= a;

    // vec3_f32_scale( wwv, 2 )
    wwv.x *= _LITERAL( 2.0 );
    wwv.y *= _LITERAL( 2.0 );
    wwv.z *= _LITERAL( 2.0 );

    result.x += wv.x;
    result.y += wv.y;
    result.z += wv.z;

    result.x += wwv.x;
    result.y += wwv.y;
    result.z += wwv.z;

    return result;
}

// Move Vector towards target
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( move_towards )( _VEC3_TYPE v, _VEC3_TYPE target, _BASE_TYPE max )
{
    _VEC3_TYPE result = { 0 };

    _BASE_TYPE dx = target.x - v.x;
    _BASE_TYPE dy = target.y - v.y;
    _BASE_TYPE dz = target.z - v.z;
    _BASE_TYPE value = ( dx * dx ) + ( dy * dy ) + ( dz * dz );

    if ( ( value == _LITERAL( 0.0 ) ) || ( ( max >= _LITERAL( 0.0 ) ) && ( value <= max * max ) ) )
        return target;

    _BASE_TYPE dist = _SQRT( value );

    result.x = v.x + dx / dist * max;
    result.y = v.y + dy / dist * max;
    result.z = v.z + dz / dist * max;

    return result;
}

// Calculate linear interpolation between two vectors
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( lerp )( _VEC3_TYPE a, _VEC3_TYPE b, _BASE_TYPE t )
{
    _VEC3_TYPE result = { 0 };

    result.x = a.x + t * ( b.x - a.x );
    result.y = a.y + t * ( b.y - a.y );
    result.z = a.z + t * ( b.z - a.z );

    return result;
}

// Calculate cubic hermite interpolation between two vectors and their tangents
// as described in the GLTF 2.0 specification: https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html#interpolation-cubic
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( cubic_hermite )( _VEC3_TYPE a, _VEC3_TYPE tan_a, _VEC3_TYPE b, _VEC3_TYPE tan_b, _BASE_TYPE t )
{
    _VEC3_TYPE result = { 0 };

    _BASE_TYPE t2 = t * t;
    _BASE_TYPE t3 = t * t * t;

    const _BASE_TYPE one = _LITERAL( 1.0 );
    const _BASE_TYPE two = _LITERAL( 2.0 );
    const _BASE_TYPE three = _LITERAL( 3.0 );

    result.x = ( two * t3 - three * t2 + one ) * a.x + ( t3 - two * t2 + t ) * tan_a.x + ( -two * t3 + three * t2 ) * b.x + ( t3 - t2 ) * tan_b.x;
    result.y = ( two * t3 - three * t2 + one ) * a.y + ( t3 - two * t2 + t ) * tan_a.y + ( -two * t3 + three * t2 ) * b.y + ( t3 - t2 ) * tan_b.y;
    result.z = ( two * t3 - three * t2 + one ) * a.z + ( t3 - two * t2 + t ) * tan_a.z + ( -two * t3 + three * t2 ) * b.z + ( t3 - t2 ) * tan_b.z;

    return result;
}

// Calculate reflected vector to normal
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( reflect )( _VEC3_TYPE v, _VEC3_TYPE normal )
{
    _VEC3_TYPE result = { 0 };

    // I is the original vector
    // N is the normal of the incident plane
    // R = I - (2*N*(DotProduct[I, N]))

    _BASE_TYPE dot = ( v.x * normal.x + v.y * normal.y + v.z * normal.z );

    result.x = v.x - ( _LITERAL( 2.0 ) * normal.x ) * dot;
    result.y = v.y - ( _LITERAL( 2.0 ) * normal.y ) * dot;
    result.z = v.z - ( _LITERAL( 2.0 ) * normal.z ) * dot;

    return result;
}

// Get min value for each pair of components
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( min )( _VEC3_TYPE a, _VEC3_TYPE b )
{
    _VEC3_TYPE result = { 0 };

    result.x = _MIN( a.x, b.x );
    result.y = _MIN( a.y, b.y );
    result.z = _MIN( a.z, b.z );

    return result;
}

// Get max value for each pair of components
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( max )( _VEC3_TYPE a, _VEC3_TYPE b )
{
    _VEC3_TYPE result = { 0 };

    result.x = _MAX( a.x, b.x );
    result.y = _MAX( a.y, b.y );
    result.z = _MAX( a.z, b.z );

    return result;
}

// Compute barycenter coordinates (u, v, w) for point p with respect to triangle (a, b, c)
// NOTE: Assumes P is on the plane of the triangle
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( barycenter )( _VEC3_TYPE p, _VEC3_TYPE a, _VEC3_TYPE b, _VEC3_TYPE c )
{
    _VEC3_TYPE result = { 0 };

    _VEC3_TYPE v0 = { b.x - a.x, b.y - a.y, b.z - a.z };			// vec3_f32_sub(b, a)
    _VEC3_TYPE v1 = { c.x - a.x, c.y - a.y, c.z - a.z };   			// vec3_f32_sub(c, a)
    _VEC3_TYPE v2 = { p.x - a.x, p.y - a.y, p.z - a.z };   			// vec3_f32_sub(p, a)
    _BASE_TYPE d00 = ( v0.x * v0.x + v0.y * v0.y + v0.z * v0.z );    // vec3_f32_dot(v0, v0)
    _BASE_TYPE d01 = ( v0.x * v1.x + v0.y * v1.y + v0.z * v1.z );    // vec3_f32_dot(v0, v1)
    _BASE_TYPE d11 = ( v1.x * v1.x + v1.y * v1.y + v1.z * v1.z );    // vec3_f32_dot(v1, v1)
    _BASE_TYPE d20 = ( v2.x * v0.x + v2.y * v0.y + v2.z * v0.z );    // vec3_f32_dot(v2, v0)
    _BASE_TYPE d21 = ( v2.x * v1.x + v2.y * v1.y + v2.z * v1.z );    // vec3_f32_dot(v2, v1)

    _BASE_TYPE denom = d00 * d11 - d01 * d01;

    result.y = ( d11 * d20 - d01 * d21 ) / denom;
    result.z = ( d00 * d21 - d01 * d20 ) / denom;
    result.x = _LITERAL( 1.0 ) - ( result.z + result.y );

    return result;
}

// Projects a _VEC3_TYPE from screen space into object space
// NOTE: We are avoiding calling other raymath functions despite available
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( unproject )( _VEC3_TYPE source, _MAT4_TYPE proj, _MAT4_TYPE view )
{
    _VEC3_TYPE result = { 0 };

    // Calculate unprojected matrix (multiply view matrix by projection matrix) and invert it
    _MAT4_TYPE view_proj = {      // MatrixMultiply(view, projection);
        view.m00 * proj.m00 + view.m10 * proj.m01 + view.m20 * proj.m02 + view.m30 * proj.m03,
        view.m00 * proj.m10 + view.m10 * proj.m11 + view.m20 * proj.m12 + view.m30 * proj.m13,
        view.m00 * proj.m20 + view.m10 * proj.m21 + view.m20 * proj.m22 + view.m30 * proj.m23,
        view.m00 * proj.m30 + view.m10 * proj.m31 + view.m20 * proj.m32 + view.m30 * proj.m33,
        view.m01 * proj.m00 + view.m11 * proj.m01 + view.m21 * proj.m02 + view.m31 * proj.m03,
        view.m01 * proj.m10 + view.m11 * proj.m11 + view.m21 * proj.m12 + view.m31 * proj.m13,
        view.m01 * proj.m20 + view.m11 * proj.m21 + view.m21 * proj.m22 + view.m31 * proj.m23,
        view.m01 * proj.m30 + view.m11 * proj.m31 + view.m21 * proj.m32 + view.m31 * proj.m33,
        view.m02 * proj.m00 + view.m12 * proj.m01 + view.m22 * proj.m02 + view.m32 * proj.m03,
        view.m02 * proj.m10 + view.m12 * proj.m11 + view.m22 * proj.m12 + view.m32 * proj.m13,
        view.m02 * proj.m20 + view.m12 * proj.m21 + view.m22 * proj.m22 + view.m32 * proj.m23,
        view.m02 * proj.m30 + view.m12 * proj.m31 + view.m22 * proj.m32 + view.m32 * proj.m33,
        view.m03 * proj.m00 + view.m13 * proj.m01 + view.m23 * proj.m02 + view.m33 * proj.m03,
        view.m03 * proj.m10 + view.m13 * proj.m11 + view.m23 * proj.m12 + view.m33 * proj.m13,
        view.m03 * proj.m20 + view.m13 * proj.m21 + view.m23 * proj.m22 + view.m33 * proj.m23,
        view.m03 * proj.m30 + view.m13 * proj.m31 + view.m23 * proj.m32 + view.m33 * proj.m33
    };

    // Calculate inverted matrix -> MatrixInvert(view_proj);
    // Cache the matrix values (speed optimization)
    _BASE_TYPE a00 = view_proj.m00, a01 = view_proj.m10, a02 = view_proj.m20, a03 = view_proj.m30;
    _BASE_TYPE a10 = view_proj.m01, a11 = view_proj.m11, a12 = view_proj.m21, a13 = view_proj.m31;
    _BASE_TYPE a20 = view_proj.m02, a21 = view_proj.m12, a22 = view_proj.m22, a23 = view_proj.m32;
    _BASE_TYPE a30 = view_proj.m03, a31 = view_proj.m13, a32 = view_proj.m23, a33 = view_proj.m33;

    _BASE_TYPE b00 = a00 * a11 - a01 * a10;
    _BASE_TYPE b01 = a00 * a12 - a02 * a10;
    _BASE_TYPE b02 = a00 * a13 - a03 * a10;
    _BASE_TYPE b03 = a01 * a12 - a02 * a11;
    _BASE_TYPE b04 = a01 * a13 - a03 * a11;
    _BASE_TYPE b05 = a02 * a13 - a03 * a12;
    _BASE_TYPE b06 = a20 * a31 - a21 * a30;
    _BASE_TYPE b07 = a20 * a32 - a22 * a30;
    _BASE_TYPE b08 = a20 * a33 - a23 * a30;
    _BASE_TYPE b09 = a21 * a32 - a22 * a31;
    _BASE_TYPE b10 = a21 * a33 - a23 * a31;
    _BASE_TYPE b11 = a22 * a33 - a23 * a32;

    // Calculate the invert determinant (inlined to avoid double-caching)
    _BASE_TYPE idet = _LITERAL( 1.0 ) / ( b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06 );

    _MAT4_TYPE view_proj_inv = {
        ( a11 * b11 - a12 * b10 + a13 * b09 ) * idet,
        ( -a01 * b11 + a02 * b10 - a03 * b09 ) * idet,
        ( a31 * b05 - a32 * b04 + a33 * b03 ) * idet,
        ( -a21 * b05 + a22 * b04 - a23 * b03 ) * idet,
        ( -a10 * b11 + a12 * b08 - a13 * b07 ) * idet,
        ( a00 * b11 - a02 * b08 + a03 * b07 ) * idet,
        ( -a30 * b05 + a32 * b02 - a33 * b01 ) * idet,
        ( a20 * b05 - a22 * b02 + a23 * b01 ) * idet,
        ( a10 * b10 - a11 * b08 + a13 * b06 ) * idet,
        ( -a00 * b10 + a01 * b08 - a03 * b06 ) * idet,
        ( a30 * b04 - a31 * b02 + a33 * b00 ) * idet,
        ( -a20 * b04 + a21 * b02 - a23 * b00 ) * idet,
        ( -a10 * b09 + a11 * b07 - a12 * b06 ) * idet,
        ( a00 * b09 - a01 * b07 + a02 * b06 ) * idet,
        ( -a30 * b03 + a31 * b01 - a32 * b00 ) * idet,
        ( a20 * b03 - a21 * b01 + a22 * b00 ) * idet
    };

    // Create quaternion from source point
    _QUAT_TYPE quat = { source.x, source.y, source.z, _LITERAL( 1.0 ) };

    // Multiply quat point by unprojecte matrix
    _QUAT_TYPE qtransformed = {     // QuaternionTransform(quat, view_proj_inv)
        view_proj_inv.m00 * quat.x + view_proj_inv.m01 * quat.y + view_proj_inv.m02 * quat.z + view_proj_inv.m03 * quat.w,
        view_proj_inv.m10 * quat.x + view_proj_inv.m11 * quat.y + view_proj_inv.m12 * quat.z + view_proj_inv.m13 * quat.w,
        view_proj_inv.m20 * quat.x + view_proj_inv.m21 * quat.y + view_proj_inv.m22 * quat.z + view_proj_inv.m23 * quat.w,
        view_proj_inv.m30 * quat.x + view_proj_inv.m31 * quat.y + view_proj_inv.m32 * quat.z + view_proj_inv.m33 * quat.w };

    // Normalized world points in vectors
    result.x = qtransformed.x / qtransformed.w;
    result.y = qtransformed.y / qtransformed.w;
    result.z = qtransformed.z / qtransformed.w;

    return result;
}

// Invert the given vector
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( invert )( _VEC3_TYPE v )
{
    _VEC3_TYPE result = {
        _LITERAL( 1.0 ) / v.x,
        _LITERAL( 1.0 ) / v.y,
        _LITERAL( 1.0 ) / v.z
    };

    return result;
}

// Clamp the components of the vector between
// min and max values specified by the given vectors
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( clamp )( _VEC3_TYPE v, _VEC3_TYPE min, _VEC3_TYPE max )
{
    _VEC3_TYPE result = { 0 };

    result.x = _MIN( max.x, _MAX( min.x, v.x ) );
    result.y = _MIN( max.y, _MAX( min.y, v.y ) );
    result.z = _MIN( max.z, _MAX( min.z, v.z ) );

    return result;
}

_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( clamp_val )( _VEC3_TYPE v, _BASE_TYPE min, _BASE_TYPE max )
{
    _VEC3_TYPE result = { 0 };

    result.x = _MIN( max, _MAX( min, v.x ) );
    result.y = _MIN( max, _MAX( min, v.y ) );
    result.z = _MIN( max, _MAX( min, v.z ) );

    return result;
}

// Clamp the magnitude of the vector between two values
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( clamp_len )( _VEC3_TYPE v, _BASE_TYPE min, _BASE_TYPE max )
{
    _VEC3_TYPE result = v;

    _BASE_TYPE len = ( v.x * v.x ) + ( v.y * v.y ) + ( v.z * v.z );
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
        result.z = v.z * scale;
    }

    return result;
}

// Check whether two given vectors are almost equal
_FUNC_SPEC int _FUNC_CONV _FUNC_VEC3( equals )( _VEC3_TYPE p, _VEC3_TYPE q, _BASE_TYPE epsilon )
{
    int result =
        ( ( _ABS( p.x - q.x ) ) <= ( epsilon * _MAX( _LITERAL( 1.0 ), _MAX( _ABS( p.x ), _ABS( q.x ) ) ) ) ) &&
        ( ( _ABS( p.y - q.y ) ) <= ( epsilon * _MAX( _LITERAL( 1.0 ), _MAX( _ABS( p.y ), _ABS( q.y ) ) ) ) ) &&
        ( ( _ABS( p.z - q.z ) ) <= ( epsilon * _MAX( _LITERAL( 1.0 ), _MAX( _ABS( p.z ), _ABS( q.z ) ) ) ) );

    return result;
}

// Compute the direction of a refracted ray
// v: normalized direction of the incoming ray
// n: normalized normal vector of the interface of two optical media
// r: ratio of the refractive index of the medium from where the ray comes
//    to the refractive index of the medium on the other side of the surface
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_VEC3( refract )( _VEC3_TYPE v, _VEC3_TYPE n, _BASE_TYPE r )
{
    _VEC3_TYPE result = { 0 };

    _BASE_TYPE dot = v.x * n.x + v.y * n.y + v.z * n.z;
    _BASE_TYPE d = _LITERAL( 1.0 ) - r * r * ( _LITERAL( 1.0 ) - dot * dot );

    if ( d >= _LITERAL( 0.0 ) )
    {
        d = _SQRT( d );
        v.x = r * v.x - ( r * dot + d ) * n.x;
        v.y = r * v.y - ( r * dot + d ) * n.y;
        v.z = r * v.z - ( r * dot + d ) * n.z;

        result = v;
    }

    return result;
}

#endif

/*
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * VECTOR4
 * -----------------------------
 */

#ifdef LINEAR_ALGEBRA_VEC4_HEADER
#undef LINEAR_ALGEBRA_VEC4_HEADER

_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( zero )( void );
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( one )( void );
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( add )( _VEC4_TYPE a, _VEC4_TYPE b );
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( add_val )( _VEC4_TYPE v, _BASE_TYPE val );
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( sub )( _VEC4_TYPE a, _VEC4_TYPE b );
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( sub_val )( _VEC4_TYPE v, _BASE_TYPE val );
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC4( len )( _VEC4_TYPE v );
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC4( len_sq )( _VEC4_TYPE v );
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC4( dot )( _VEC4_TYPE a, _VEC4_TYPE b );
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC4( dist )( _VEC4_TYPE a, _VEC4_TYPE b );
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC4( dist_sq )( _VEC4_TYPE a, _VEC4_TYPE b );
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( scale )( _VEC4_TYPE v, _BASE_TYPE scale );
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( mul )( _VEC4_TYPE a, _VEC4_TYPE b );
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( negate )( _VEC4_TYPE v );
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( div )( _VEC4_TYPE a, _VEC4_TYPE b );
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( normalize )( _VEC4_TYPE v );
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( min )( _VEC4_TYPE a, _VEC4_TYPE b );
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( max )( _VEC4_TYPE a, _VEC4_TYPE b );
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( lerp )( _VEC4_TYPE a, _VEC4_TYPE b, _BASE_TYPE t );
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( move_towards )( _VEC4_TYPE v, _VEC4_TYPE target, _BASE_TYPE max );
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( invert )( _VEC4_TYPE v );
_FUNC_SPEC int        _FUNC_CONV _FUNC_VEC4( equals )( _VEC4_TYPE p, _VEC4_TYPE q, _BASE_TYPE epsilon );

#endif



#ifdef LINEAR_ALGEBRA_VEC4_IMPLEMENTATION
#undef LINEAR_ALGEBRA_VEC4_IMPLEMENTATION

_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( zero )( void )
{
    _VEC4_TYPE result = {
        _LITERAL( 0.0 ),
        _LITERAL( 0.0 ),
        _LITERAL( 0.0 ),
        _LITERAL( 0.0 )
    };

    return result;
}

_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( one )( void )
{
    _VEC4_TYPE result = {
        _LITERAL( 1.0 ),
        _LITERAL( 1.0 ),
        _LITERAL( 1.0 ),
        _LITERAL( 1.0 )
    };

    return result;
}

_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( add )( _VEC4_TYPE a, _VEC4_TYPE b )
{
    _VEC4_TYPE result = {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w
    };

    return result;
}

_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( add_val )( _VEC4_TYPE v, _BASE_TYPE val )
{
    _VEC4_TYPE result = {
        v.x + val,
        v.y + val,
        v.z + val,
        v.w + val
    };

    return result;
}

_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( sub )( _VEC4_TYPE a, _VEC4_TYPE b )
{
    _VEC4_TYPE result = {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
        a.w - b.w
    };
    
    return result;
}

_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( sub_val )( _VEC4_TYPE v, _BASE_TYPE val )
{
    _VEC4_TYPE result = {
        v.x - val,
        v.y - val,
        v.z - val,
        v.w - val
    };

    return result;
}

_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC4( len )( _VEC4_TYPE v )
{
    _BASE_TYPE result = _SQRT( ( v.x * v.x ) + ( v.y * v.y ) + ( v.z * v.z ) + ( v.w * v.w ) );
    return result;
}

_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC4( len_sq )( _VEC4_TYPE v )
{
    _BASE_TYPE result = ( v.x * v.x ) + ( v.y * v.y ) + ( v.z * v.z ) + ( v.w * v.w );
    return result;
}

_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC4( dot )( _VEC4_TYPE a, _VEC4_TYPE b )
{
    _BASE_TYPE result = ( a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w );
    return result;
}

// Calculate distance between two vectors
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC4( dist )( _VEC4_TYPE a, _VEC4_TYPE b )
{
    _BASE_TYPE result = _SQRT(
        ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) +
        ( a.z - b.z ) * ( a.z - b.z ) + ( a.w - b.w ) * ( a.w - b.w ) );
    return result;
}

// Calculate square distance between two vectors
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC4( dist_sq )( _VEC4_TYPE a, _VEC4_TYPE b )
{
    _BASE_TYPE result =
        ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) +
        ( a.z - b.z ) * ( a.z - b.z ) + ( a.w - b.w ) * ( a.w - b.w );
    return result;
}

_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( scale )( _VEC4_TYPE v, _BASE_TYPE scale )
{
    _VEC4_TYPE result = { v.x * scale, v.y * scale, v.z * scale, v.w * scale };
    return result;
}

// Multiply vector by vector
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( mul )( _VEC4_TYPE a, _VEC4_TYPE b )
{
    _VEC4_TYPE result = { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
    return result;
}

// Negate vector
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( negate )( _VEC4_TYPE v )
{
    _VEC4_TYPE result = { -v.x, -v.y, -v.z, -v.w };
    return result;
}

// Divide vector by vector
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( div )( _VEC4_TYPE a, _VEC4_TYPE b )
{
    _VEC4_TYPE result = { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
    return result;
}

// Normalize provided vector
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( normalize )( _VEC4_TYPE v )
{
    _VEC4_TYPE result = { 0 };
    _BASE_TYPE len = _SQRT( ( v.x * v.x ) + ( v.y * v.y ) + ( v.z * v.z ) + ( v.w * v.w ) );

    if ( len > _LITERAL( 0.0 ) )
    {
        _BASE_TYPE ilen = _LITERAL( 1.0 ) / len;
        result.x = v.x * ilen;
        result.y = v.y * ilen;
        result.z = v.z * ilen;
        result.w = v.w * ilen;
    }

    return result;
}

// Get min value for each pair of components
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( min )( _VEC4_TYPE a, _VEC4_TYPE b )
{
    _VEC4_TYPE result = { 0 };

    result.x = _MIN( a.x, b.x );
    result.y = _MIN( a.y, b.y );
    result.z = _MIN( a.z, b.z );
    result.w = _MIN( a.w, b.w );

    return result;
}

// Get max value for each pair of components
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( max )( _VEC4_TYPE a, _VEC4_TYPE b )
{
    _VEC4_TYPE result = { 0 };

    result.x = _MAX( a.x, b.x );
    result.y = _MAX( a.y, b.y );
    result.z = _MAX( a.z, b.z );
    result.w = _MAX( a.w, b.w );

    return result;
}

// Calculate linear interpolation between two vectors
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( lerp )( _VEC4_TYPE a, _VEC4_TYPE b, _BASE_TYPE t )
{
    _VEC4_TYPE result = { 0 };

    result.x = a.x + t * ( b.x - a.x );
    result.y = a.y + t * ( b.y - a.y );
    result.z = a.z + t * ( b.z - a.z );
    result.w = a.w + t * ( b.w - a.w );

    return result;
}

// Move Vector towards target
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( move_towards )( _VEC4_TYPE v, _VEC4_TYPE target, _BASE_TYPE max )
{
    _VEC4_TYPE result = { 0 };

    _BASE_TYPE dx = target.x - v.x;
    _BASE_TYPE dy = target.y - v.y;
    _BASE_TYPE dz = target.z - v.z;
    _BASE_TYPE dw = target.w - v.w;
    _BASE_TYPE value = ( dx * dx ) + ( dy * dy ) + ( dz * dz ) + ( dw * dw );

    if ( ( value == _LITERAL( 0.0 ) ) || ( ( max >= _LITERAL( 0.0 ) ) && ( value <= max * max ) ) )
        return target;

    _BASE_TYPE dist = _SQRT( value );

    result.x = v.x + dx / dist * max;
    result.y = v.y + dy / dist * max;
    result.z = v.z + dz / dist * max;
    result.w = v.w + dw / dist * max;

    return result;
}

// Invert the given vector
_FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( invert )( _VEC4_TYPE v )
{
    _VEC4_TYPE result = {
        _LITERAL( 1.0 ) / v.x,
        _LITERAL( 1.0 ) / v.y,
        _LITERAL( 1.0 ) / v.z,
        _LITERAL( 1.0 ) / v.w
    };

    return result;
}

// Check whether two given vectors are almost equal
_FUNC_SPEC int _FUNC_CONV _FUNC_VEC4( equals )( _VEC4_TYPE p, _VEC4_TYPE q, _BASE_TYPE epsilon )
{
    int result =
        ( ( _ABS( p.x - q.x ) ) <= ( epsilon * _MAX( _LITERAL( 1.0 ), _MAX( _ABS( p.x ), _ABS( q.x ) ) ) ) ) &&
        ( ( _ABS( p.y - q.y ) ) <= ( epsilon * _MAX( _LITERAL( 1.0 ), _MAX( _ABS( p.y ), _ABS( q.y ) ) ) ) ) &&
        ( ( _ABS( p.z - q.z ) ) <= ( epsilon * _MAX( _LITERAL( 1.0 ), _MAX( _ABS( p.z ), _ABS( q.z ) ) ) ) ) &&
        ( ( _ABS( p.w - q.w ) ) <= ( epsilon * _MAX( _LITERAL( 1.0 ), _MAX( _ABS( p.w ), _ABS( q.w ) ) ) ) );

    return result;
}

#endif

/*
 * =============================
 */

#endif