#if defined( LINEAR_ALGEBRA_CLEANUP )

#undef _MAT4_TYPE
#undef _VEC2_TYPE
#undef _BASE_TYPE
#undef _FUNC_SPEC
#undef _FUNC_PREFIX
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
#undef _NAME_HELPER
#undef _FUNC_NAME
#undef _LITERAL_HELPER
#undef _LITERAL
#undef _FLITERAL
#undef LINEAR_ALGEBRA_CLEANUP

#else

#include "../../util/types.h"
#include <math.h>

#if defined( LINEAR_ALGEBRA_I32 )

#define _MAT4_TYPE struct mat4_i32
#define _VEC2_TYPE struct vec2_i32
#define _BASE_TYPE int32_t
#define _FLOAT_TYPE float
#define _FUNC_SPEC static inline
#define _FUNC_PREFIX vec2_i32
#define _BASE_SUFFIX 
#define _FLOAT_SUFFIX f
#define _SIN sinf
#define _COS cosf
#define _TAN tanf
#define _ATAN2 atan2f
#define _SQRT sqrtf
#define _ABS fabsf
#undef LINEAR_ALGEBRA_I32

#elif defined( LINEAR_ALGEBRA_I64 )

#define _MAT4_TYPE struct mat4_i64
#define _VEC2_TYPE struct vec2_i64
#define _BASE_TYPE int64_t
#define _FLOAT_TYPE float
#define _FUNC_SPEC static inline
#define _FUNC_PREFIX vec2_i64
#define _BASE_SUFFIX ll
#define _FLOAT_SUFFIX f
#define _SIN sinf
#define _COS cosf
#define _TAN tanf
#define _ATAN2 atan2f
#define _SQRT sqrtf
#define _ABS fabsf
#undef LINEAR_ALGEBRA_I64

#else
#error "Only I32 and I64 version are supported"
#endif

#define _MAX( a, b ) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )
#define _MIN( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )

#define _CONCAT( _a, _b ) _a##_b

#define _NAME_HELPER( _prefix, _fn ) _CONCAT( _prefix, _##_fn )
#define _FUNC_NAME( _fn ) _NAME_HELPER( _FUNC_PREFIX, _fn )

#define _LITERAL_HELPER( _v, _s ) _CONCAT( _v, _s )
#define _LITERAL( _v ) _LITERAL_HELPER( _v, _BASE_SUFFIX )
#define _FLITERAL( _v ) _LITERAL_HELPER( _v, _FLOAT_SUFFIX )

// Vector2 with components value ( 0, 0 )
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( zero )( void )
{
    _VEC2_TYPE result = { _LITERAL( 0 ), _LITERAL( 0 ) };
    return result;
}

// Vector2 with components value ( 1, 1 )
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( one )( void )
{
    _VEC2_TYPE result = { _LITERAL( 1 ), _LITERAL( 1 ) };
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
_FUNC_SPEC _FLOAT_TYPE _FUNC_NAME( len )( _VEC2_TYPE v )
{
    _FLOAT_TYPE result = _SQRT( ( _FLOAT_TYPE ) ( ( v.x * v.x ) + ( v.y * v.y ) ) );
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
_FUNC_SPEC _FLOAT_TYPE _FUNC_NAME( dist )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _FLOAT_TYPE result = _SQRT( ( _FLOAT_TYPE ) ( ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) ) );
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
_FUNC_SPEC _FLOAT_TYPE _FUNC_NAME( angle )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    _FLOAT_TYPE result = _FLITERAL( 0.0 );

    _BASE_TYPE dot = a.x * b.x + a.y * b.y;
    _BASE_TYPE det = a.x * b.y - a.y * b.x;

    result = _ATAN2( ( _FLOAT_TYPE ) det, ( _FLOAT_TYPE ) dot );

    return result;
}

// Calculate angle defined by a two vectors line
// NOTE: Parameters need to be normalized
// Current implementation should be aligned with glm::angle
_FUNC_SPEC _FLOAT_TYPE _FUNC_NAME( line_angle )( _VEC2_TYPE start, _VEC2_TYPE end )
{
    _FLOAT_TYPE result = _FLITERAL( 0.0 );

    result = -_ATAN2( ( _FLOAT_TYPE ) ( end.y - start.y ), ( _FLOAT_TYPE ) ( end.x - start.x ) );

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

// Divide vector by scalar value
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( div_val )( _VEC2_TYPE a, _BASE_TYPE v )
{
    _VEC2_TYPE result = { a.x / v, a.y / v };
    return result;
}

// Transforms a TYPE by a given Matrix
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( transform )( _VEC2_TYPE v, _MAT4_TYPE m )
{
    _VEC2_TYPE result = { 0 };

    _BASE_TYPE x = v.x;
    _BASE_TYPE y = v.y;
    _BASE_TYPE z = _LITERAL( 0 );

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

    result.x = v.x - ( _LITERAL( 2 ) * normal.x ) * dot;
    result.y = v.y - ( _LITERAL( 2 ) * normal.y ) * dot;

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
_FUNC_SPEC _VEC2_TYPE _FUNC_NAME( rotate )( _VEC2_TYPE v, _FLOAT_TYPE angle )
{
    _VEC2_TYPE result = { 0 };

    _FLOAT_TYPE c = _COS( angle );
    _FLOAT_TYPE s = _SIN( angle );

    result.x = ( _BASE_TYPE ) ( v.x * c - v.y * s );
    result.y = ( _BASE_TYPE ) ( v.x * s + v.y * c );

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

// Check whether two given vectors are almost equal
_FUNC_SPEC int _FUNC_NAME( equals )( _VEC2_TYPE p, _VEC2_TYPE q )
{
    int result = (p.x == q.x) && (p.y == q.y);
    return result;
}

#endif