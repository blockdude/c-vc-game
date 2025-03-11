#include "../../util/types.h"
#include "_linear_algebra_start.h"

/*
 * =============================
 * -----------------------------
 * VECTOR 2
 * -----------------------------
 */

#if defined( LINEAR_ALGEBRA_VEC2_IMPLEMENTATION ) || defined( LINEAR_ALGEBRA_VEC2_HEADER )

//                        | function  | return type | parameters
//                        | ---       | :---:       | ---
//extern _VEC2_DECL_FUNC(     zero,       _VEC2_TYPE,   void                                             );
//extern _VEC2_DECL_FUNC(     one,        _VEC2_TYPE,   void                                             );
//extern _VEC2_DECL_FUNC(     add,        _VEC2_TYPE,   _VEC2_TYPE a, _VEC2_TYPE b                       );
//extern _VEC2_DECL_FUNC(     add_val,    _VEC2_TYPE,   _VEC2_TYPE v, _BASE_TYPE val                     );
//extern _VEC2_DECL_FUNC(     sub,        _VEC2_TYPE,   _VEC2_TYPE a, _VEC2_TYPE b                       );
//extern _VEC2_DECL_FUNC(     sub_val,    _VEC2_TYPE,   _VEC2_TYPE v, _BASE_TYPE val                     );
//extern _VEC2_DECL_FUNC(     len,        _BASE_TYPE,   _VEC2_TYPE v                                     );
//extern _VEC2_DECL_FUNC(     len_sq,     _BASE_TYPE,   _VEC2_TYPE v                                     );
//extern _VEC2_DECL_FUNC(     dot,        _BASE_TYPE,   _VEC2_TYPE a, _VEC2_TYPE b                       );
//extern _VEC2_DECL_FUNC(     dist,       _BASE_TYPE,   _VEC2_TYPE a, _VEC2_TYPE b                       );
//extern _VEC2_DECL_FUNC(     dist_sq,    _BASE_TYPE,   _VEC2_TYPE a, _VEC2_TYPE b                       );
//extern _VEC2_DECL_FUNC(     scale,      _VEC2_TYPE,   _VEC2_TYPE v, _BASE_TYPE scale                   );
//extern _VEC2_DECL_FUNC(     mul,        _VEC2_TYPE,   _VEC2_TYPE a, _VEC2_TYPE b                       );
//extern _VEC2_DECL_FUNC(     negate,     _VEC2_TYPE,   _VEC2_TYPE v                                     );
//extern _VEC2_DECL_FUNC(     div,        _VEC2_TYPE,   _VEC2_TYPE a, _VEC2_TYPE b                       );
//extern _VEC2_DECL_FUNC(     transform,  _VEC2_TYPE,   _VEC2_TYPE v, _MAT4_TYPE m                       );
//extern _VEC2_DECL_FUNC(     lerp,       _VEC2_TYPE,   _VEC2_TYPE a, _VEC2_TYPE b, _BASE_TYPE t         );
//extern _VEC2_DECL_FUNC(     reflect,    _VEC2_TYPE,   _VEC2_TYPE v, _VEC2_TYPE normal                  );
//extern _VEC2_DECL_FUNC(     min,        _VEC2_TYPE,   _VEC2_TYPE a, _VEC2_TYPE b                       );
//extern _VEC2_DECL_FUNC(     max,        _VEC2_TYPE,   _VEC2_TYPE a, _VEC2_TYPE b                       );
//extern _VEC2_DECL_FUNC(     clamp,      _VEC2_TYPE,   _VEC2_TYPE v, _VEC2_TYPE min, _VEC2_TYPE max     );
//extern _VEC2_DECL_FUNC(     clamp_val,  _VEC2_TYPE,   _VEC2_TYPE v, _BASE_TYPE min, _BASE_TYPE max     );

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
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( scale )( _VEC2_TYPE v, _BASE_TYPE scale );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( mul )( _VEC2_TYPE a, _VEC2_TYPE b );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( negate )( _VEC2_TYPE v );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( div )( _VEC2_TYPE a, _VEC2_TYPE b );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( transform )( _VEC2_TYPE v, _MAT4_TYPE m );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( lerp )( _VEC2_TYPE a, _VEC2_TYPE b, _BASE_TYPE t );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( reflect )( _VEC2_TYPE v, _VEC2_TYPE normal );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( min )( _VEC2_TYPE a, _VEC2_TYPE b );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( max )( _VEC2_TYPE a, _VEC2_TYPE b );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( clamp )( _VEC2_TYPE v, _VEC2_TYPE min, _VEC2_TYPE max );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( clamp_val )( _VEC2_TYPE v, _BASE_TYPE min, _BASE_TYPE max );

#if _IS_IEC559
extern _FUNC_SPEC int        _FUNC_CONV _FUNC_VEC2( equals )( _VEC2_TYPE p, _VEC2_TYPE q, _BASE_TYPE epsilon );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC2( angle )( _VEC2_TYPE a, _VEC2_TYPE b );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC2( line_angle )( _VEC2_TYPE start, _VEC2_TYPE end );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( normalize )( _VEC2_TYPE v );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( rotate )( _VEC2_TYPE v, _BASE_TYPE angle );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( move_towards )( _VEC2_TYPE v, _VEC2_TYPE target, _BASE_TYPE max );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( invert )( _VEC2_TYPE v );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( clamp_len )( _VEC2_TYPE v, _BASE_TYPE min, _BASE_TYPE max );
extern _FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( refract )( _VEC2_TYPE v, _VEC2_TYPE n, _BASE_TYPE r );
#else /* _IS_IEC559 */
extern _FUNC_SPEC int        _FUNC_CONV _FUNC_VEC2( equals )( _VEC2_TYPE p, _VEC2_TYPE q );
#endif /* _IS_IEC559 */

#endif /* LINEAR_ALGEBRA_VEC2_IMPLEMENATAION || HEADER */

#ifdef LINEAR_ALGEBRA_VEC2_IMPLEMENTATION

// Vector2 with components value LIT( 0.0 )
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( zero )( void )
{
    _VEC2_TYPE result = {
        _STATIC_CAST( _BASE_TYPE, 0 ),
        _STATIC_CAST( _BASE_TYPE, 0 )
    };

    return result;
}

// Vector2 with components value LIT( 1.0 )
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( one )( void )
{
    _VEC2_TYPE result = {
        _STATIC_CAST( _BASE_TYPE, 1 ),
        _STATIC_CAST( _BASE_TYPE, 1 )
    };

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

// Transforms a TYPE by a given Matrix
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( transform )( _VEC2_TYPE v, _MAT4_TYPE m )
{
    _VEC2_TYPE result = { 0 };

    _BASE_TYPE x = v.x;
    _BASE_TYPE y = v.y;
    _BASE_TYPE z = _STATIC_CAST( _BASE_TYPE, 0 );

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

    result.x = v.x - ( _STATIC_CAST( _BASE_TYPE, 2 ) * normal.x ) * dot;
    result.y = v.y - ( _STATIC_CAST( _BASE_TYPE, 2 ) * normal.y ) * dot;

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

#if _IS_IEC559 /* ONLY FUNCTIONS THAT USE FLOATING POINT IEEE754 (I don't know why c++ calls it iec559 but ill do the same) */

// Check whether two given vectors are almost equal
_FUNC_SPEC int _FUNC_CONV _FUNC_VEC2( equals )( _VEC2_TYPE p, _VEC2_TYPE q, _BASE_TYPE epsilon )
{
    static_assert( _IS_IEC559 == true, "equals must use floating point vectors" );

    int result =
        ( ( _ABS( p.x - q.x ) ) <= ( epsilon * _MAX( _STATIC_CAST( _BASE_TYPE, 1 ), _MAX( _ABS( p.x ), _ABS( q.x ) ) ) ) ) &&
        ( ( _ABS( p.y - q.y ) ) <= ( epsilon * _MAX( _STATIC_CAST( _BASE_TYPE, 1 ), _MAX( _ABS( p.y ), _ABS( q.y ) ) ) ) );

    return result;
}

// Calculate angle between two vectors
// NOTE: Angle is calculated from origin point (0, 0)
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC2( angle )( _VEC2_TYPE a, _VEC2_TYPE b )
{
    static_assert( _IS_IEC559 == true, "angle must use floating point vectors" );

    _BASE_TYPE result = _STATIC_CAST( _BASE_TYPE, 0 );

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
    static_assert( _IS_IEC559 == true, "line_angle must use floating point vectors" );

    _BASE_TYPE result = _STATIC_CAST( _BASE_TYPE, 0 );

    result = -_ATAN2( end.y - start.y, end.x - start.x );

    return result;
}

// Normalize provided vector
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( normalize )( _VEC2_TYPE v )
{
    static_assert( _IS_IEC559 == true, "normalize must use floating point vectors" );

    _VEC2_TYPE result = { 0 };

    _BASE_TYPE len = _SQRT( ( v.x * v.x ) + ( v.y * v.y ) );
    if ( len > _STATIC_CAST( _BASE_TYPE, 0 ) )
    {
        _BASE_TYPE ilen = _STATIC_CAST( _BASE_TYPE, 1 ) / len;
        result.x = v.x * ilen;
        result.y = v.y * ilen;
    }

    return result;
}

// Rotate vector by angle
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( rotate )( _VEC2_TYPE v, _BASE_TYPE angle )
{
    static_assert( _IS_IEC559 == true, "rotate must use floating point vectors" );

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
    static_assert( _IS_IEC559 == true, "move_towards must use floating point vectors" );

    _VEC2_TYPE result = { 0 };

    _BASE_TYPE dx = target.x - v.x;
    _BASE_TYPE dy = target.y - v.y;
    _BASE_TYPE value = ( dx * dx ) + ( dy * dy );

    if ( ( value == _STATIC_CAST( _BASE_TYPE, 0 ) ) || ( ( max >= _STATIC_CAST( _BASE_TYPE, 0 ) ) && ( value <= max * max ) ) )
        return target;

    _BASE_TYPE dist = _SQRT( value );

    result.x = v.x + dx / dist * max;
    result.y = v.y + dy / dist * max;

    return result;
}

// Invert the given vector
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( invert )( _VEC2_TYPE v )
{
    static_assert( _IS_IEC559 == true, "invert must use floating point vectors" );

    _VEC2_TYPE result = { _STATIC_CAST( _BASE_TYPE, 1 ) / v.x, _STATIC_CAST( _BASE_TYPE, 1 ) / v.y };
    return result;
}


// Clamp the magnitude of the vector between two min and max values
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( clamp_len )( _VEC2_TYPE v, _BASE_TYPE min, _BASE_TYPE max )
{
    static_assert( _IS_IEC559 == true, "clamp_len must use floating point vectors" );

    _VEC2_TYPE result = v;

    _BASE_TYPE len = ( v.x * v.x ) + ( v.y * v.y );
    if ( len > _STATIC_CAST( _BASE_TYPE, 0 ) )
    {
        len = _SQRT( len );

        _BASE_TYPE scale = _STATIC_CAST( _BASE_TYPE, 1 );    // By default, 1 as the neutral element.
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

// Compute the direction of a refracted ray
// v: normalized direction of the incoming ray
// n: normalized normal vector of the interface of two optical media
// r: ratio of the refractive index of the medium from where the ray comes
//    to the refractive index of the medium on the other side of the surface
_FUNC_SPEC _VEC2_TYPE _FUNC_CONV _FUNC_VEC2( refract )( _VEC2_TYPE v, _VEC2_TYPE n, _BASE_TYPE r )
{
    static_assert( _IS_IEC559 == true, "refract must use floating point vectors" );

    _VEC2_TYPE result = { 0 };

    _BASE_TYPE dot = v.x * n.x + v.y * n.y;
    _BASE_TYPE d = _STATIC_CAST( _BASE_TYPE, 1 ) - r * r * ( _STATIC_CAST( _BASE_TYPE, 1 ) - dot * dot );

    if ( d >= _STATIC_CAST( _BASE_TYPE, 0 ) )
    {
        d = _SQRT( d );
        v.x = r * v.x - ( r * dot + d ) * n.x;
        v.y = r * v.y - ( r * dot + d ) * n.y;

        result = v;
    }

    return result;
}

#else /* _IS_IEC559 */

// Check whether two given vectors are equal
_FUNC_SPEC int _FUNC_CONV _FUNC_VEC2( equals )( _VEC2_TYPE p, _VEC2_TYPE q )
{
    int result =
        ( p.x == q.x ) &&
        ( p.y == q.y );

    return result;
}

#endif /* _IS_IEC559 */
#endif /* LINEAR_ALGEBRA_VEC2_IMPLEMENTATION*/

/*
 * -----------------------------
 * VECTOR 2
 * -----------------------------
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * VECTOR 3
 * -----------------------------
 */

#if defined( LINEAR_ALGEBRA_VEC3_IMPLEMENTATION ) || defined( LINEAR_ALGEBRA_VEC3_HEADER )
#if _IS_IEC559

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

#endif /* _IS_IEC559 */
#endif /* LINEAR_ALGEBRA_VEC3_IMPLEMENTATION || HEADER */

#ifdef LINEAR_ALGEBRA_VEC3_IMPLEMENTATION
#if _IS_IEC559

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

#endif /* _IS_IEC559 */
#endif /* LINEAR_ALGEBRA_VEC3_IMPLEMENTATION */

/*
 * -----------------------------
 * VECTOR 3
 * -----------------------------
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * VECTOR 4
 * -----------------------------
 */

#if defined( LINEAR_ALGEBRA_VEC4_IMPLEMENTATION ) || defined( LINEAR_ALGEBRA_VEC4_HEADER )
#if _IS_IEC559

extern _FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( zero )( void );
extern _FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( one )( void );
extern _FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( add )( _VEC4_TYPE a, _VEC4_TYPE b );
extern _FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( add_val )( _VEC4_TYPE v, _BASE_TYPE val );
extern _FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( sub )( _VEC4_TYPE a, _VEC4_TYPE b );
extern _FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( sub_val )( _VEC4_TYPE v, _BASE_TYPE val );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC4( len )( _VEC4_TYPE v );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC4( len_sq )( _VEC4_TYPE v );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC4( dot )( _VEC4_TYPE a, _VEC4_TYPE b );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC4( dist )( _VEC4_TYPE a, _VEC4_TYPE b );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_VEC4( dist_sq )( _VEC4_TYPE a, _VEC4_TYPE b );
extern _FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( scale )( _VEC4_TYPE v, _BASE_TYPE scale );
extern _FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( mul )( _VEC4_TYPE a, _VEC4_TYPE b );
extern _FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( negate )( _VEC4_TYPE v );
extern _FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( div )( _VEC4_TYPE a, _VEC4_TYPE b );
extern _FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( normalize )( _VEC4_TYPE v );
extern _FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( min )( _VEC4_TYPE a, _VEC4_TYPE b );
extern _FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( max )( _VEC4_TYPE a, _VEC4_TYPE b );
extern _FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( lerp )( _VEC4_TYPE a, _VEC4_TYPE b, _BASE_TYPE t );
extern _FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( move_towards )( _VEC4_TYPE v, _VEC4_TYPE target, _BASE_TYPE max );
extern _FUNC_SPEC _VEC4_TYPE _FUNC_CONV _FUNC_VEC4( invert )( _VEC4_TYPE v );
extern _FUNC_SPEC int        _FUNC_CONV _FUNC_VEC4( equals )( _VEC4_TYPE p, _VEC4_TYPE q, _BASE_TYPE epsilon );

#endif /* _IS_IEC559 */
#endif /* LINEAR_ALGEBRA_VEC4_IMPLEMENTATION || HEADER */

#ifdef LINEAR_ALGEBRA_VEC4_IMPLEMENTATION
#if _IS_IEC559

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

#endif /* _IS_IEC559 */
#endif /* LINEAR_ALGEBRA_VEC4_IMPLEMENTATION */

/*
 * -----------------------------
 * VECTOR 4
 * -----------------------------
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * QUATERNION
 * -----------------------------
 */

#if defined( LINEAR_ALGEBRA_QUAT_IMPLEMENTATION ) || defined( LINEAR_ALGEBRA_QUAT_HEADER )
#if _IS_IEC559

_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( add )( _QUAT_TYPE p, _QUAT_TYPE q );
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( add_val )( _QUAT_TYPE q, _BASE_TYPE val );
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( sub )( _QUAT_TYPE p, _QUAT_TYPE q );
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( sub_val )( _QUAT_TYPE q, _BASE_TYPE val );
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( identity )( void );
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_QUAT( len )( _QUAT_TYPE q );
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( normalize )( _QUAT_TYPE q );
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( invert )( _QUAT_TYPE q );
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( mul )( _QUAT_TYPE p, _QUAT_TYPE q );
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( scale )( _QUAT_TYPE q, _BASE_TYPE s );
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( div )( _QUAT_TYPE p, _QUAT_TYPE q );
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( lerp )( _QUAT_TYPE p, _QUAT_TYPE q, _BASE_TYPE t );
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( nlerp )( _QUAT_TYPE p, _QUAT_TYPE q, _BASE_TYPE t );
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( slerp )( _QUAT_TYPE p, _QUAT_TYPE q, _BASE_TYPE t, _BASE_TYPE epsilon );
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( cubic_hermite_spline )( _QUAT_TYPE p, _QUAT_TYPE out_tan_p, _QUAT_TYPE q, _QUAT_TYPE in_tan_q, _BASE_TYPE t );
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( from_vec3 )( _VEC3_TYPE p, _VEC3_TYPE q );
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( from_mat4 )( _MAT4_TYPE m );
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_QUAT( to_mat4 )( _QUAT_TYPE q );
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( from_axis_angle )( _VEC3_TYPE axis, _BASE_TYPE angle );
_FUNC_SPEC void       _FUNC_CONV _FUNC_QUAT( to_axis_angle )( _QUAT_TYPE q, _BASE_TYPE epsilon, _VEC3_TYPE *out_axis, _BASE_TYPE *out_angle );
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( from_euler )( _BASE_TYPE pitch, _BASE_TYPE yaw, _BASE_TYPE roll );
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_QUAT( to_euler )( _QUAT_TYPE q );
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( transform )( _QUAT_TYPE q, _MAT4_TYPE m );
_FUNC_SPEC int        _FUNC_CONV _FUNC_QUAT( equals )( _QUAT_TYPE p, _QUAT_TYPE q, _BASE_TYPE epsilon );

#endif /* _IS_IEC559 */
#endif /* LINEAR_ALGEBRA_QUAT_IMPLEMENTATION || HEADER */

#ifdef LINEAR_ALGEBRA_QUAT_IMPLEMENTATION
#if _IS_IEC559

// Add two quaternions
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( add )( _QUAT_TYPE p, _QUAT_TYPE q )
{
    _QUAT_TYPE result = { p.x + q.x, p.y + q.y, p.z + q.z, p.w + q.w };
    return result;
}

// Add quaternion and _BASE_TYPE value
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( add_val )( _QUAT_TYPE q, _BASE_TYPE val )
{
    _QUAT_TYPE result = { q.x + val, q.y + val, q.z + val, q.w + val };
    return result;
}

// Subtract two quaternions
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( sub )( _QUAT_TYPE p, _QUAT_TYPE q )
{
    _QUAT_TYPE result = { p.x - q.x, p.y - q.y, p.z - q.z, p.w - q.w };
    return result;
}

// Subtract quaternion and _BASE_TYPE value
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( sub_val )( _QUAT_TYPE q, _BASE_TYPE val )
{
    _QUAT_TYPE result = { q.x - val, q.y - val, q.z - val, q.w - val };
    return result;
}

// Get identity quaternion
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( identity )( void )
{
    _QUAT_TYPE result = {
        _LITERAL( 0.0 ),
        _LITERAL( 0.0 ),
        _LITERAL( 0.0 ),
        _LITERAL( 1.0 )
    };

    return result;
}

// Computes the length of a quaternion
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_QUAT( len )( _QUAT_TYPE q )
{
    _BASE_TYPE result = _SQRT( q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w );
    return result;
}

// Normalize provided quaternion
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( normalize )( _QUAT_TYPE q )
{
    _QUAT_TYPE result = { 0 };

    _BASE_TYPE len = _SQRT( q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w );
    if ( len == _LITERAL( 0.0 ) ) len = _LITERAL( 1.0 );
    _BASE_TYPE ilen = _LITERAL( 1.0 ) / len;

    result.x = q.x * ilen;
    result.y = q.y * ilen;
    result.z = q.z * ilen;
    result.w = q.w * ilen;

    return result;
}

// Invert provided quaternion
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( invert )( _QUAT_TYPE q )
{
    _QUAT_TYPE result = q;

    _BASE_TYPE len = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;

    if ( len != _LITERAL( 0.0 ) )
    {
        _BASE_TYPE ilen = _LITERAL( 1.0 ) / len;

        result.x *= -ilen;
        result.y *= -ilen;
        result.z *= -ilen;
        result.w *= ilen;
    }

    return result;
}

// Calculate two quaternion multiplication
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( mul )( _QUAT_TYPE p, _QUAT_TYPE q )
{
    _QUAT_TYPE result = { 0 };

    _BASE_TYPE qax = p.x, qay = p.y, qaz = p.z, qaw = p.w;
    _BASE_TYPE qbx = q.x, qby = q.y, qbz = q.z, qbw = q.w;

    result.x = qax * qbw + qaw * qbx + qay * qbz - qaz * qby;
    result.y = qay * qbw + qaw * qby + qaz * qbx - qax * qbz;
    result.z = qaz * qbw + qaw * qbz + qax * qby - qay * qbx;
    result.w = qaw * qbw - qax * qbx - qay * qby - qaz * qbz;

    return result;
}

// Scale quaternion by _BASE_TYPE value
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( scale )( _QUAT_TYPE q, _BASE_TYPE s )
{
    _QUAT_TYPE result = { 0 };

    result.x = q.x * s;
    result.y = q.y * s;
    result.z = q.z * s;
    result.w = q.w * s;

    return result;
}

// Divide two quaternions
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( div )( _QUAT_TYPE p, _QUAT_TYPE q )
{
    _QUAT_TYPE result = { p.x / q.x, p.y / q.y, p.z / q.z, p.w / q.w };
    return result;
}

// Calculate linear interpolation between two quaternions
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( lerp )( _QUAT_TYPE p, _QUAT_TYPE q, _BASE_TYPE t )
{
    _QUAT_TYPE result = { 0 };

    result.x = p.x + t * ( q.x - p.x );
    result.y = p.y + t * ( q.y - p.y );
    result.z = p.z + t * ( q.z - p.z );
    result.w = p.w + t * ( q.w - p.w );

    return result;
}

// Calculate slerp-optimized interpolation between two quaternions
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( nlerp )( _QUAT_TYPE p, _QUAT_TYPE q, _BASE_TYPE t )
{
    _QUAT_TYPE result = { 0 };

    // _QUAT_TYPELerp(p, q, t)
    result.x = p.x + t * ( q.x - p.x );
    result.y = p.y + t * ( q.y - p.y );
    result.z = p.z + t * ( q.z - p.z );
    result.w = p.w + t * ( q.w - p.w );

    // quat_f32_Normalize(n);
    _QUAT_TYPE n = result;
    _BASE_TYPE len = _SQRT( n.x * n.x + n.y * n.y + n.z * n.z + n.w * n.w );
    if ( len == _LITERAL( 0.0 ) ) len = _LITERAL( 1.0 );
    _BASE_TYPE ilen = _LITERAL( 1.0 ) / len;

    result.x = n.x * ilen;
    result.y = n.y * ilen;
    result.z = n.z * ilen;
    result.w = n.w * ilen;

    return result;
}

// Calculates spherical linear interpolation between two quaternions
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( slerp )( _QUAT_TYPE p, _QUAT_TYPE q, _BASE_TYPE t, _BASE_TYPE epsilon )
{
    _QUAT_TYPE result = { 0 };

    _BASE_TYPE cos_half_theta = p.x * q.x + p.y * q.y + p.z * q.z + p.w * q.w;

    if ( cos_half_theta < _LITERAL( 0.0 ) )
    {
        q.x = -q.x; q.y = -q.y; q.z = -q.z; q.w = -q.w;
        cos_half_theta = -cos_half_theta;
    }

    if ( _ABS( cos_half_theta ) >= _LITERAL( 1.0 ) ) result = p;
    else if ( cos_half_theta > _LITERAL( 0.95 ) ) result = _FUNC_QUAT( nlerp )( p, q, t );
    else
    {
        _BASE_TYPE half_theta = _ACOS( cos_half_theta );
        _BASE_TYPE sin_half_theta = _SQRT( _LITERAL( 1.0 ) - cos_half_theta * cos_half_theta );

        if ( _ABS( sin_half_theta ) < epsilon )
        {
            result.x = ( p.x * _LITERAL( 0.5 ) + q.x * _LITERAL( 0.5 ) );
            result.y = ( p.y * _LITERAL( 0.5 ) + q.y * _LITERAL( 0.5 ) );
            result.z = ( p.z * _LITERAL( 0.5 ) + q.z * _LITERAL( 0.5 ) );
            result.w = ( p.w * _LITERAL( 0.5 ) + q.w * _LITERAL( 0.5 ) );
        }
        else
        {
            _BASE_TYPE ratio_a = _SIN( ( _LITERAL( 1.0 ) - t ) * half_theta ) / sin_half_theta;
            _BASE_TYPE ratio_b = _SIN( t * half_theta ) / sin_half_theta;

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
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( cubic_hermite_spline )( _QUAT_TYPE p, _QUAT_TYPE out_tan_p, _QUAT_TYPE q, _QUAT_TYPE in_tan_q, _BASE_TYPE t )
{
    _BASE_TYPE t2 = t * t;
    _BASE_TYPE t3 = t2 * t;
    _BASE_TYPE h00 = _LITERAL( 2.0 ) * t3 - _LITERAL( 3.0 ) * t2 + _LITERAL( 1.0 );
    _BASE_TYPE h10 = t3 - _LITERAL( 2.0 ) * t2 + t;
    _BASE_TYPE h01 = _LITERAL( -2.0 ) * t3 + _LITERAL( 3.0 ) * t2;
    _BASE_TYPE h11 = t3 - t2;

    _QUAT_TYPE p0 = _FUNC_QUAT( scale )( p, h00 );
    _QUAT_TYPE m0 = _FUNC_QUAT( scale )( out_tan_p, h10 );
    _QUAT_TYPE p1 = _FUNC_QUAT( scale )( q, h01 );
    _QUAT_TYPE m1 = _FUNC_QUAT( scale )( in_tan_q, h11 );

    _QUAT_TYPE result = { 0 };

    result = _FUNC_QUAT( add )( p0, m0 );
    result = _FUNC_QUAT( add )( result, p1 );
    result = _FUNC_QUAT( add )( result, m1 );
    result = _FUNC_QUAT( normalize )( result );

    return result;
}

// Calculate quaternion based on the rotation from vector a to vector b
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( from_vec3 )( _VEC3_TYPE p, _VEC3_TYPE q )
{
    _QUAT_TYPE result = { 0 };

    _BASE_TYPE dot = ( p.x * q.x + p.y * q.y + p.z * q.z );    // vec3_DotProduct(p, q) | cos2theta
    _VEC3_TYPE cross = { p.y * q.z - p.z * q.y, p.z * q.x - p.x * q.z, p.x * q.y - p.y * q.x }; // Vecbr3CrossProduct(p, q)

    result.x = cross.x;
    result.y = cross.y;
    result.z = cross.z;
    result.w = _LITERAL( 1.0 ) + dot;

    // _QUAT_TYPENormalize(n);
    // NOTE: Normalize q essentially nlerp the original and identity q 0.5
    _QUAT_TYPE n = result;
    _BASE_TYPE len = _SQRT( n.x * n.x + n.y * n.y + n.z * n.z + n.w * n.w );
    if ( len == _LITERAL( 0.0 ) ) len = _LITERAL( 1.0 );
    _BASE_TYPE ilen = _LITERAL( 1.0 ) / len;

    result.x = n.x * ilen;
    result.y = n.y * ilen;
    result.z = n.z * ilen;
    result.w = n.w * ilen;

    return result;
}

// Get a quaternion for a given rotation matrix
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( from_mat4 )( _MAT4_TYPE m )
{
    _QUAT_TYPE result = { 0 };

    _BASE_TYPE four_w_sq_sub_one = m.m00 + m.m11 + m.m22;
    _BASE_TYPE four_x_sq_sub_one = m.m00 - m.m11 - m.m22;
    _BASE_TYPE four_y_sq_sub_one = m.m11 - m.m00 - m.m22;
    _BASE_TYPE four_z_sq_sub_one = m.m22 - m.m00 - m.m11;

    int biggest_idx = 0;
    _BASE_TYPE four_biggest_sq_sub_one = four_w_sq_sub_one;

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

    _BASE_TYPE biggest_val = _SQRT( four_biggest_sq_sub_one + _LITERAL( 1.0 ) ) * _LITERAL( 0.5 );
    _BASE_TYPE mult = _LITERAL( 0.25 ) / biggest_val;

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
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_QUAT( to_mat4 )( _QUAT_TYPE q )
{
    _MAT4_TYPE result = {
        _LITERAL( 1.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 1.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 1.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 1.0 )
    }; // MatrixIdentity()

    _BASE_TYPE a2 = q.x * q.x;
    _BASE_TYPE b2 = q.y * q.y;
    _BASE_TYPE c2 = q.z * q.z;
    _BASE_TYPE ac = q.x * q.z;
    _BASE_TYPE ab = q.x * q.y;
    _BASE_TYPE bc = q.y * q.z;
    _BASE_TYPE ad = q.w * q.x;
    _BASE_TYPE bd = q.w * q.y;
    _BASE_TYPE cd = q.w * q.z;

    result.m00 = _LITERAL( 1.0 ) - _LITERAL( 2.0 ) * ( b2 + c2 );
    result.m10 = _LITERAL( 2.0 ) * ( ab + cd );
    result.m20 = _LITERAL( 2.0 ) * ( ac - bd );

    result.m01 = _LITERAL( 2.0 ) * ( ab - cd );
    result.m11 = _LITERAL( 1.0 ) - _LITERAL( 2.0 ) * ( a2 + c2 );
    result.m21 = _LITERAL( 2.0 ) * ( bc + ad );

    result.m02 = _LITERAL( 2.0 ) * ( ac + bd );
    result.m12 = _LITERAL( 2.0 ) * ( bc - ad );
    result.m22 = _LITERAL( 1.0 ) - _LITERAL( 2.0 ) * ( a2 + b2 );

    return result;
}

// Get rotation quaternion for an angle and axis
// NOTE: Angle must be provided in radians
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( from_axis_angle )( _VEC3_TYPE axis, _BASE_TYPE angle )
{
    _QUAT_TYPE result = {
        _LITERAL( 0.0 ),
        _LITERAL( 0.0 ),
        _LITERAL( 0.0 ),
        _LITERAL( 1.0 )
    };

    _BASE_TYPE axislen = _SQRT( axis.x * axis.x + axis.y * axis.y + axis.z * axis.z );

    if ( axislen != _LITERAL( 0.0 ) )
    {
        angle *= _LITERAL( 0.5 );

        _BASE_TYPE len = _LITERAL( 0.0 );
        _BASE_TYPE ilen = _LITERAL( 0.0 );

        // Vector3Normalize( axis )
        len = axislen;
        if ( len == _LITERAL( 0.0 ) ) len = _LITERAL( 1.0 );
        ilen = _LITERAL( 1.0 ) / len;
        axis.x *= ilen;
        axis.y *= ilen;
        axis.z *= ilen;

        _BASE_TYPE s = _SIN( angle );
        _BASE_TYPE c = _COS( angle );

        result.x = axis.x * s;
        result.y = axis.y * s;
        result.z = axis.z * s;
        result.w = c;

        // _QUAT_TYPENormalize( q );
        _QUAT_TYPE q = result;
        len = _SQRT( q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w );
        if ( len == _LITERAL( 0.0 ) ) len = _LITERAL( 1.0 );
        ilen = _LITERAL( 1.0 ) / len;
        result.x = q.x * ilen;
        result.y = q.y * ilen;
        result.z = q.z * ilen;
        result.w = q.w * ilen;
    }

    return result;
}

// Get the rotation angle and axis for a given quaternion
_FUNC_SPEC void _FUNC_CONV _FUNC_QUAT( to_axis_angle )( _QUAT_TYPE q, _BASE_TYPE epsilon, _VEC3_TYPE *out_axis, _BASE_TYPE *out_angle )
{
    if ( _ABS( q.w ) > _LITERAL( 1.0 ) )
    {
        // _QUAT_TYPENormalize( q );
        _BASE_TYPE len = _SQRT( q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w );
        if ( len == _LITERAL( 0.0 ) ) len = _LITERAL( 1.0 );
        _BASE_TYPE ilen = _LITERAL( 1.0 ) / len;

        q.x = q.x * ilen;
        q.y = q.y * ilen;
        q.z = q.z * ilen;
        q.w = q.w * ilen;
    }

    _VEC3_TYPE res_axis = { _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ) };
    _BASE_TYPE res_angle = _LITERAL( 2.0 ) * _ACOS( q.w );
    _BASE_TYPE den = _SQRT( _LITERAL( 1.0 ) - q.w * q.w );

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
        res_axis.x = _LITERAL( 1.0 );
    }

    *out_axis = res_axis;
    *out_angle = res_angle;
}

// Get the quaternion equivalent to Euler angles
// NOTE: Rotation order is ZYX
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( from_euler )( _BASE_TYPE pitch, _BASE_TYPE yaw, _BASE_TYPE roll )
{
    _QUAT_TYPE result = { 0 };

    _BASE_TYPE x0 = _COS( pitch * _LITERAL( 0.5 ) );
    _BASE_TYPE x1 = _SIN( pitch * _LITERAL( 0.5 ) );
    _BASE_TYPE y0 = _COS( yaw * _LITERAL( 0.5 ) );
    _BASE_TYPE y1 = _SIN( yaw * _LITERAL( 0.5 ) );
    _BASE_TYPE z0 = _COS( roll * _LITERAL( 0.5 ) );
    _BASE_TYPE z1 = _SIN( roll * _LITERAL( 0.5 ) );

    result.x = x1 * y0 * z0 - x0 * y1 * z1;
    result.y = x0 * y1 * z0 + x1 * y0 * z1;
    result.z = x0 * y0 * z1 - x1 * y1 * z0;
    result.w = x0 * y0 * z0 + x1 * y1 * z1;

    return result;
}

// Get the Euler angles equivalent to quaternion (roll, pitch, yaw)
// NOTE: Angles are returned in a Vector3 struct in radians
_FUNC_SPEC _VEC3_TYPE _FUNC_CONV _FUNC_QUAT( to_euler )( _QUAT_TYPE q )
{
    _VEC3_TYPE result = { 0 };

    // Roll ( x-axis rotation )
    _BASE_TYPE x0 = _LITERAL( 2.0 ) * ( q.w * q.x + q.y * q.z );
    _BASE_TYPE x1 = _LITERAL( 1.0 ) - _LITERAL( 2.0 ) * ( q.x * q.x + q.y * q.y );
    result.x = _ATAN2( x0, x1 );

    // Pitch ( y-axis rotation )
    _BASE_TYPE y0 = _LITERAL( 2.0 ) * ( q.w * q.y - q.z * q.x );
    y0 = y0 > _LITERAL( 1.0 ) ? _LITERAL( 1.0 ) : y0;
    y0 = y0 < _LITERAL( -1.0 ) ? _LITERAL( -1.0 ) : y0;
    result.y = _ASIN( y0 );

    // Yaw ( z-axis rotation )
    _BASE_TYPE z0 = _LITERAL( 2.0 ) * ( q.w * q.z + q.x * q.y );
    _BASE_TYPE z1 = _LITERAL( 1.0 ) - _LITERAL( 2.0 ) * ( q.y * q.y + q.z * q.z );
    result.z = _ATAN2( z0, z1 );

    return result;
}

// Transform a quaternion given a transformation matrix
_FUNC_SPEC _QUAT_TYPE _FUNC_CONV _FUNC_QUAT( transform )( _QUAT_TYPE q, _MAT4_TYPE m )
{
    _QUAT_TYPE result = { 0 };

    result.x = m.m00 * q.x + m.m01 * q.y + m.m02 * q.z + m.m03 * q.w;
    result.y = m.m10 * q.x + m.m11 * q.y + m.m12 * q.z + m.m13 * q.w;
    result.z = m.m20 * q.x + m.m21 * q.y + m.m22 * q.z + m.m23 * q.w;
    result.w = m.m30 * q.x + m.m31 * q.y + m.m32 * q.z + m.m33 * q.w;

    return result;
}

// Check whether two given quaternions are almost equal
_FUNC_SPEC int _FUNC_CONV _FUNC_QUAT( equals )( _QUAT_TYPE p, _QUAT_TYPE q, _BASE_TYPE epsilon )
{
    int result =
        ( ( ( _ABS( p.x - q.x ) ) <= ( epsilon * _MAX( _LITERAL( 1.0 ), _MAX( _ABS( p.x ), _ABS( q.x ) ) ) ) ) &&
          ( ( _ABS( p.y - q.y ) ) <= ( epsilon * _MAX( _LITERAL( 1.0 ), _MAX( _ABS( p.y ), _ABS( q.y ) ) ) ) ) &&
          ( ( _ABS( p.z - q.z ) ) <= ( epsilon * _MAX( _LITERAL( 1.0 ), _MAX( _ABS( p.z ), _ABS( q.z ) ) ) ) ) &&
          ( ( _ABS( p.w - q.w ) ) <= ( epsilon * _MAX( _LITERAL( 1.0 ), _MAX( _ABS( p.w ), _ABS( q.w ) ) ) ) ) ) ||

        ( ( ( _ABS( p.x + q.x ) ) <= ( epsilon * _MAX( _LITERAL( 1.0 ), _MAX( _ABS( p.x ), _ABS( q.x ) ) ) ) ) &&
          ( ( _ABS( p.y + q.y ) ) <= ( epsilon * _MAX( _LITERAL( 1.0 ), _MAX( _ABS( p.y ), _ABS( q.y ) ) ) ) ) &&
          ( ( _ABS( p.z + q.z ) ) <= ( epsilon * _MAX( _LITERAL( 1.0 ), _MAX( _ABS( p.z ), _ABS( q.z ) ) ) ) ) &&
          ( ( _ABS( p.w + q.w ) ) <= ( epsilon * _MAX( _LITERAL( 1.0 ), _MAX( _ABS( p.w ), _ABS( q.w ) ) ) ) ) );

    return result;
}

#endif /* _IS_IEC559 */
#endif /* LINEAR_ALGEBRA_QUAT_IMPLEMENTATION */

/*
 * -----------------------------
 * QUATERNION
 * -----------------------------
 * =============================
 */



/*
 * =============================
 * -----------------------------
 * MATRIX 4X4
 * -----------------------------
 */

#if defined( LINEAR_ALGEBRA_MAT4_IMPLEMENTATION ) || defined( LINEAR_ALGEBRA_MAT4_HEADER )
#if _IS_IEC559

extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_MAT4( det )( _MAT4_TYPE m );
extern _FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_MAT4( trace )( _MAT4_TYPE m );
extern _FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( transpose )( _MAT4_TYPE m );
extern _FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( invert )( _MAT4_TYPE m );
extern _FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( identity )( void );
extern _FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( add )( _MAT4_TYPE a, _MAT4_TYPE b );
extern _FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( sub )( _MAT4_TYPE a, _MAT4_TYPE b );
extern _FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( mul )( _MAT4_TYPE a, _MAT4_TYPE b );
extern _FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( translate )( _VEC3_TYPE v );
extern _FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( rotate )( _VEC3_TYPE axis, _BASE_TYPE angle );
extern _FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( rotate_x )( _BASE_TYPE angle );
extern _FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( rotate_y )( _BASE_TYPE angle );
extern _FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( rotate_z )( _BASE_TYPE angle );
extern _FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( rotate_xyz )( _VEC3_TYPE angle );
extern _FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( rotate_zyx )( _VEC3_TYPE angle );
extern _FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( scale )( _VEC3_TYPE v );
extern _FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( frustum )( _BASE_TYPE left, _BASE_TYPE right, _BASE_TYPE bottom, _BASE_TYPE top, _BASE_TYPE near, _BASE_TYPE far );
extern _FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( perspective )( _BASE_TYPE fovy, _BASE_TYPE aspect, _BASE_TYPE near, _BASE_TYPE far );
extern _FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( ortho )( _BASE_TYPE left, _BASE_TYPE right, _BASE_TYPE bottom, _BASE_TYPE top, _BASE_TYPE near, _BASE_TYPE far );
extern _FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( lookat )( _VEC3_TYPE eye, _VEC3_TYPE target, _VEC3_TYPE up );
extern _FUNC_SPEC void       _FUNC_CONV _FUNC_MAT4( decompose )( _MAT4_TYPE m, _VEC3_TYPE *translation, _QUAT_TYPE *rotation, _VEC3_TYPE *scale );
extern _FUNC_SPEC _FMAT4_TYPE _FUNC_CONV _FUNC_MAT4( flatten )( _MAT4_TYPE m );

#endif /* _IS_IEC559 */
#endif /* LINEAR_ALGEBRA_MAT4_IMPLEMENTATION || HEADER */

#ifdef LINEAR_ALGEBRA_MAT4_IMPLEMENTATION
#if _IS_IEC559

// Compute matrix determinant
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_MAT4( det )( _MAT4_TYPE m )
{
    _BASE_TYPE result = _LITERAL( 0.0 );

    // Cache the matrix values (speed optimization)
    _BASE_TYPE a00 = m.m00, a01 = m.m10, a02 = m.m20, a03 = m.m30;
    _BASE_TYPE a10 = m.m01, a11 = m.m11, a12 = m.m21, a13 = m.m31;
    _BASE_TYPE a20 = m.m02, a21 = m.m12, a22 = m.m22, a23 = m.m32;
    _BASE_TYPE a30 = m.m03, a31 = m.m13, a32 = m.m23, a33 = m.m33;

    result =
        a30 * a21 * a12 * a03 - a20 * a31 * a12 * a03 - a30 * a11 * a22 * a03 + a10 * a31 * a22 * a03 +
        a20 * a11 * a32 * a03 - a10 * a21 * a32 * a03 - a30 * a21 * a02 * a13 + a20 * a31 * a02 * a13 +
        a30 * a01 * a22 * a13 - a00 * a31 * a22 * a13 - a20 * a01 * a32 * a13 + a00 * a21 * a32 * a13 +
        a30 * a11 * a02 * a23 - a10 * a31 * a02 * a23 - a30 * a01 * a12 * a23 + a00 * a31 * a12 * a23 +
        a10 * a01 * a32 * a23 - a00 * a11 * a32 * a23 - a20 * a11 * a02 * a33 + a10 * a21 * a02 * a33 +
        a20 * a01 * a12 * a33 - a00 * a21 * a12 * a33 - a10 * a01 * a22 * a33 + a00 * a11 * a22 * a33;

    return result;
}

// Get the trace of the matrix (sum of the values along the diagonal)
_FUNC_SPEC _BASE_TYPE _FUNC_CONV _FUNC_MAT4( trace )( _MAT4_TYPE m )
{
    _BASE_TYPE result = ( m.m00 + m.m11 + m.m22 + m.m33 );
    return result;
}

// Transposes provided matrix
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( transpose )( _MAT4_TYPE m )
{
    _MAT4_TYPE result = { 0 };

    result.m00 = m.m00;
    result.m10 = m.m01;
    result.m20 = m.m02;
    result.m30 = m.m03;
    result.m01 = m.m10;
    result.m11 = m.m11;
    result.m21 = m.m12;
    result.m31 = m.m13;
    result.m02 = m.m20;
    result.m12 = m.m21;
    result.m22 = m.m22;
    result.m32 = m.m23;
    result.m03 = m.m30;
    result.m13 = m.m31;
    result.m23 = m.m32;
    result.m33 = m.m33;

    return result;
}

// Invert provided matrix
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( invert )( _MAT4_TYPE m )
{
    _MAT4_TYPE result = { 0 };

    // Cache the matrix values (speed optimization)
    _BASE_TYPE a00 = m.m00, a01 = m.m10, a02 = m.m20, a03 = m.m30;
    _BASE_TYPE a10 = m.m01, a11 = m.m11, a12 = m.m21, a13 = m.m31;
    _BASE_TYPE a20 = m.m02, a21 = m.m12, a22 = m.m22, a23 = m.m32;
    _BASE_TYPE a30 = m.m03, a31 = m.m13, a32 = m.m23, a33 = m.m33;

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

    result.m00 = ( a11 * b11 - a12 * b10 + a13 * b09 ) * idet;
    result.m10 = ( -a01 * b11 + a02 * b10 - a03 * b09 ) * idet;
    result.m20 = ( a31 * b05 - a32 * b04 + a33 * b03 ) * idet;
    result.m30 = ( -a21 * b05 + a22 * b04 - a23 * b03 ) * idet;
    result.m01 = ( -a10 * b11 + a12 * b08 - a13 * b07 ) * idet;
    result.m11 = ( a00 * b11 - a02 * b08 + a03 * b07 ) * idet;
    result.m21 = ( -a30 * b05 + a32 * b02 - a33 * b01 ) * idet;
    result.m31 = ( a20 * b05 - a22 * b02 + a23 * b01 ) * idet;
    result.m02 = ( a10 * b10 - a11 * b08 + a13 * b06 ) * idet;
    result.m12 = ( -a00 * b10 + a01 * b08 - a03 * b06 ) * idet;
    result.m22 = ( a30 * b04 - a31 * b02 + a33 * b00 ) * idet;
    result.m32 = ( -a20 * b04 + a21 * b02 - a23 * b00 ) * idet;
    result.m03 = ( -a10 * b09 + a11 * b07 - a12 * b06 ) * idet;
    result.m13 = ( a00 * b09 - a01 * b07 + a02 * b06 ) * idet;
    result.m23 = ( -a30 * b03 + a31 * b01 - a32 * b00 ) * idet;
    result.m33 = ( a20 * b03 - a21 * b01 + a22 * b00 ) * idet;

    return result;
}

// Get identity matrix
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( identity )( void )
{
    _MAT4_TYPE result = {
        _LITERAL( 1.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 1.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 1.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 1.0 )
    };

    return result;
}

// Add two matrices
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( add )( _MAT4_TYPE a, _MAT4_TYPE b )
{
    _MAT4_TYPE result = { 0 };

    result.m00 = a.m00 + b.m00;
    result.m10 = a.m10 + b.m10;
    result.m20 = a.m20 + b.m20;
    result.m30 = a.m30 + b.m30;
    result.m01 = a.m01 + b.m01;
    result.m11 = a.m11 + b.m11;
    result.m21 = a.m21 + b.m21;
    result.m31 = a.m31 + b.m31;
    result.m02 = a.m02 + b.m02;
    result.m12 = a.m12 + b.m12;
    result.m22 = a.m22 + b.m22;
    result.m32 = a.m32 + b.m32;
    result.m03 = a.m03 + b.m03;
    result.m13 = a.m13 + b.m13;
    result.m23 = a.m23 + b.m23;
    result.m33 = a.m33 + b.m33;

    return result;
}

// Subtract two matrices (left - right)
// a - left matrix
// b - right matrix
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( sub )( _MAT4_TYPE a, _MAT4_TYPE b )
{
    _MAT4_TYPE result = { 0 };

    result.m00 = a.m00 - b.m00;
    result.m10 = a.m10 - b.m10;
    result.m20 = a.m20 - b.m20;
    result.m30 = a.m30 - b.m30;
    result.m01 = a.m01 - b.m01;
    result.m11 = a.m11 - b.m11;
    result.m21 = a.m21 - b.m21;
    result.m31 = a.m31 - b.m31;
    result.m02 = a.m02 - b.m02;
    result.m12 = a.m12 - b.m12;
    result.m22 = a.m22 - b.m22;
    result.m32 = a.m32 - b.m32;
    result.m03 = a.m03 - b.m03;
    result.m13 = a.m13 - b.m13;
    result.m23 = a.m23 - b.m23;
    result.m33 = a.m33 - b.m33;

    return result;
}

// Get two matrix multiplication
// NOTE: When multiplying matrices... the order matters!
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( mul )( _MAT4_TYPE a, _MAT4_TYPE b )
{
    _MAT4_TYPE result = { 0 };

    result.m00 = a.m00 * b.m00 + a.m10 * b.m01 + a.m20 * b.m02 + a.m30 * b.m03;
    result.m10 = a.m00 * b.m10 + a.m10 * b.m11 + a.m20 * b.m12 + a.m30 * b.m13;
    result.m20 = a.m00 * b.m20 + a.m10 * b.m21 + a.m20 * b.m22 + a.m30 * b.m23;
    result.m30 = a.m00 * b.m30 + a.m10 * b.m31 + a.m20 * b.m32 + a.m30 * b.m33;
    result.m01 = a.m01 * b.m00 + a.m11 * b.m01 + a.m21 * b.m02 + a.m31 * b.m03;
    result.m11 = a.m01 * b.m10 + a.m11 * b.m11 + a.m21 * b.m12 + a.m31 * b.m13;
    result.m21 = a.m01 * b.m20 + a.m11 * b.m21 + a.m21 * b.m22 + a.m31 * b.m23;
    result.m31 = a.m01 * b.m30 + a.m11 * b.m31 + a.m21 * b.m32 + a.m31 * b.m33;
    result.m02 = a.m02 * b.m00 + a.m12 * b.m01 + a.m22 * b.m02 + a.m32 * b.m03;
    result.m12 = a.m02 * b.m10 + a.m12 * b.m11 + a.m22 * b.m12 + a.m32 * b.m13;
    result.m22 = a.m02 * b.m20 + a.m12 * b.m21 + a.m22 * b.m22 + a.m32 * b.m23;
    result.m32 = a.m02 * b.m30 + a.m12 * b.m31 + a.m22 * b.m32 + a.m32 * b.m33;
    result.m03 = a.m03 * b.m00 + a.m13 * b.m01 + a.m23 * b.m02 + a.m33 * b.m03;
    result.m13 = a.m03 * b.m10 + a.m13 * b.m11 + a.m23 * b.m12 + a.m33 * b.m13;
    result.m23 = a.m03 * b.m20 + a.m13 * b.m21 + a.m23 * b.m22 + a.m33 * b.m23;
    result.m33 = a.m03 * b.m30 + a.m13 * b.m31 + a.m23 * b.m32 + a.m33 * b.m33;

    return result;
}

// Get translation matrix
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( translate )( _VEC3_TYPE v )
{
    _MAT4_TYPE result = {
        _LITERAL( 1.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ), v.x,
        _LITERAL( 0.0 ), _LITERAL( 1.0 ), _LITERAL( 0.0 ), v.y,
        _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 1.0 ), v.z,
        _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 1.0 )
    };

    return result;
}

// Create rotation matrix from axis and angle
// NOTE: Angle should be provided in radians
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( rotate )( _VEC3_TYPE axis, _BASE_TYPE angle )
{
    _MAT4_TYPE result = { 0 };

    _BASE_TYPE x = axis.x, y = axis.y, z = axis.z;
    _BASE_TYPE len = x * x + y * y + z * z;

    if ( ( len != _LITERAL( 1.0 ) ) && ( len != _LITERAL( 0.0 ) ) )
    {
        _BASE_TYPE ilen = _LITERAL( 1.0 ) / _SQRT( len );
        x *= ilen;
        y *= ilen;
        z *= ilen;
    }

    _BASE_TYPE s = _SIN( angle );
    _BASE_TYPE c = _COS( angle );
    _BASE_TYPE t = _LITERAL( 1.0 ) - c;

    result.m00 = x * x * t + c;
    result.m10 = y * x * t + z * s;
    result.m20 = z * x * t - y * s;
    result.m30 = _LITERAL( 0.0 );

    result.m01 = x * y * t - z * s;
    result.m11 = y * y * t + c;
    result.m21 = z * y * t + x * s;
    result.m31 = _LITERAL( 0.0 );

    result.m02 = x * z * t + y * s;
    result.m12 = y * z * t - x * s;
    result.m22 = z * z * t + c;
    result.m32 = _LITERAL( 0.0 );

    result.m03 = _LITERAL( 0.0 );
    result.m13 = _LITERAL( 0.0 );
    result.m23 = _LITERAL( 0.0 );
    result.m33 = _LITERAL( 1.0 );

    return result;
}

// Get x-rotation matrix
// NOTE: Angle must be provided in radians
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( rotate_x )( _BASE_TYPE angle )
{
    _MAT4_TYPE result = {
        _LITERAL( 1.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 1.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 1.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 1.0 )
    }; // MatrixIdentity()

    _BASE_TYPE c = _COS( angle );
    _BASE_TYPE s = _SIN( angle );

    result.m11 = c;
    result.m21 = s;
    result.m12 = -s;
    result.m22 = c;

    return result;
}

// Get y-rotation matrix
// NOTE: Angle must be provided in radians
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( rotate_y )( _BASE_TYPE angle )
{
    _MAT4_TYPE result = {
        _LITERAL( 1.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 1.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 1.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 1.0 )
    }; // MatrixIdentity()

    _BASE_TYPE c = _COS( angle );
    _BASE_TYPE s = _SIN( angle );

    result.m00 = c;
    result.m20 = -s;
    result.m02 = s;
    result.m22 = c;

    return result;
}

// Get z-rotation matrix
// NOTE: Angle must be provided in radians
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( rotate_z )( _BASE_TYPE angle )
{
    _MAT4_TYPE result = {
        _LITERAL( 1.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 1.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 1.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 1.0 )
    }; // MatrixIdentity()

    _BASE_TYPE c = _COS( angle );
    _BASE_TYPE s = _SIN( angle );

    result.m00 = c;
    result.m10 = s;
    result.m01 = -s;
    result.m11 = c;

    return result;
}


// Get xyz-rotation matrix
// NOTE: Angle must be provided in radians
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( rotate_xyz )( _VEC3_TYPE angle )
{
    _MAT4_TYPE result = {
        _LITERAL( 1.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 1.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 1.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 1.0 )
    }; // MatrixIdentity()

    _BASE_TYPE cosz = _COS( -angle.z );
    _BASE_TYPE sinz = _SIN( -angle.z );
    _BASE_TYPE cosy = _COS( -angle.y );
    _BASE_TYPE siny = _SIN( -angle.y );
    _BASE_TYPE cosx = _COS( -angle.x );
    _BASE_TYPE sinx = _SIN( -angle.x );

    result.m00 = cosz * cosy;
    result.m10 = ( cosz * siny * sinx ) - ( sinz * cosx );
    result.m20 = ( cosz * siny * cosx ) + ( sinz * sinx );

    result.m01 = sinz * cosy;
    result.m11 = ( sinz * siny * sinx ) + ( cosz * cosx );
    result.m21 = ( sinz * siny * cosx ) - ( cosz * sinx );

    result.m02 = -siny;
    result.m12 = cosy * sinx;
    result.m22 = cosy * cosx;

    return result;
}

// Get zyx-rotation matrix
// NOTE: Angle must be provided in radians
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( rotate_zyx )( _VEC3_TYPE angle )
{
    _MAT4_TYPE result = { 0 };

    _BASE_TYPE cosz = _COS( angle.z );
    _BASE_TYPE sinz = _SIN( angle.z );
    _BASE_TYPE cosy = _COS( angle.y );
    _BASE_TYPE siny = _SIN( angle.y );
    _BASE_TYPE cosx = _COS( angle.x );
    _BASE_TYPE sinx = _SIN( angle.x );

    result.m00 = cosz * cosy;
    result.m01 = cosz * siny * sinx - cosx * sinz;
    result.m02 = sinz * sinx + cosz * cosx * siny;
    result.m03 = _LITERAL( 0.0 );

    result.m10 = cosy * sinz;
    result.m11 = cosz * cosx + sinz * siny * sinx;
    result.m12 = cosx * sinz * siny - cosz * sinx;
    result.m13 = _LITERAL( 0.0 );

    result.m20 = -siny;
    result.m21 = cosy * sinx;
    result.m22 = cosy * cosx;
    result.m23 = _LITERAL( 0.0 );

    result.m30 = _LITERAL( 0.0 );
    result.m31 = _LITERAL( 0.0 );
    result.m32 = _LITERAL( 0.0 );
    result.m33 = _LITERAL( 1.0 );

    return result;
}

// Get scaling matrix
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( scale )( _VEC3_TYPE v )
{
    _MAT4_TYPE result = {
        v.x,             _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), v.y,             _LITERAL( 0.0 ), _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 0.0 ), v.z,             _LITERAL( 0.0 ),
        _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 0.0 ), _LITERAL( 1.0 )
    };

    return result;
}

// Get perspective projection matrix
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( frustum )( _BASE_TYPE left, _BASE_TYPE right, _BASE_TYPE bottom, _BASE_TYPE top, _BASE_TYPE near, _BASE_TYPE far )
{
    _MAT4_TYPE result = { 0 };

    _BASE_TYPE rl = right - left;
    _BASE_TYPE tb = top - bottom;
    _BASE_TYPE fn = far - near;

    result.m00 = ( near * _LITERAL( 2.0 ) ) / rl;
    result.m10 = _LITERAL( 0.0 );
    result.m20 = _LITERAL( 0.0 );
    result.m30 = _LITERAL( 0.0 );

    result.m01 = _LITERAL( 0.0 );
    result.m11 = ( near * _LITERAL( 2.0 ) ) / tb;
    result.m21 = _LITERAL( 0.0 );
    result.m31 = _LITERAL( 0.0 );

    result.m02 = ( right + left ) / rl;
    result.m12 = ( top + bottom ) / tb;
    result.m22 = -( far + near ) / fn;
    result.m32 = _LITERAL( -1.0 );

    result.m03 = _LITERAL( 0.0 );
    result.m13 = _LITERAL( 0.0 );
    result.m23 = -( far * near * _LITERAL( 2.0 ) ) / fn;
    result.m33 = _LITERAL( 0.0 );

    return result;
}

// Get perspective projection matrix
// NOTE: Fovy angle must be provided in radians
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( perspective )( _BASE_TYPE fovy, _BASE_TYPE aspect, _BASE_TYPE near, _BASE_TYPE far )
{
    _MAT4_TYPE result = { 0 };

    _BASE_TYPE top = near * _TAN( fovy * _LITERAL( 0.5 ) );
    _BASE_TYPE bottom = -top;
    _BASE_TYPE right = top * aspect;
    _BASE_TYPE left = -right;

    // MatrixFrustum( -right, right, -top, top, near, far );
    _BASE_TYPE rl = right - left;
    _BASE_TYPE tb = top - bottom;
    _BASE_TYPE fn = far - near;

    result.m00 = ( near * _LITERAL( 2.0 ) ) / rl;
    result.m11 = ( near * _LITERAL( 2.0 ) ) / tb;
    result.m02 = ( right + left ) / rl;
    result.m12 = ( top + bottom ) / tb;
    result.m22 = -( far + near ) / fn;
    result.m32 = _LITERAL( -1.0 );
    result.m23 = -( far * near * _LITERAL( 2.0 ) ) / fn;

    return result;
}

// Get orthographic projection matrix
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( ortho )( _BASE_TYPE left, _BASE_TYPE right, _BASE_TYPE bottom, _BASE_TYPE top, _BASE_TYPE near, _BASE_TYPE far )
{
    _MAT4_TYPE result = { 0 };

    _BASE_TYPE rl = right - left;
    _BASE_TYPE tb = top - bottom;
    _BASE_TYPE fn = far - near;

    result.m00 = _LITERAL( 2.0 ) / rl;
    result.m10 = _LITERAL( 0.0 );
    result.m20 = _LITERAL( 0.0 );
    result.m30 = _LITERAL( 0.0 );
    result.m01 = _LITERAL( 0.0 );
    result.m11 = _LITERAL( 2.0 ) / tb;
    result.m21 = _LITERAL( 0.0 );
    result.m31 = _LITERAL( 0.0 );
    result.m02 = _LITERAL( 0.0 );
    result.m12 = _LITERAL( 0.0 );
    result.m22 = _LITERAL( -2.0 ) / fn;
    result.m32 = _LITERAL( 0.0 );
    result.m03 = -( left + right ) / rl;
    result.m13 = -( top + bottom ) / tb;
    result.m23 = -( far + near ) / fn;
    result.m33 = _LITERAL( 1.0 );

    return result;
}

// Get camera look-at matrix (view matrix)
_FUNC_SPEC _MAT4_TYPE _FUNC_CONV _FUNC_MAT4( lookat )( _VEC3_TYPE eye, _VEC3_TYPE target, _VEC3_TYPE up )
{
    _MAT4_TYPE result = { 0 };

    _BASE_TYPE len = _LITERAL( 0.0 );
    _BASE_TYPE ilen = _LITERAL( 0.0 );

    // Vector3Subtract( eye, target )
    _VEC3_TYPE vz = { eye.x - target.x, eye.y - target.y, eye.z - target.z };

    // Vector3Normalize( vz )
    _VEC3_TYPE v = vz;
    len = _SQRT( v.x * v.x + v.y * v.y + v.z * v.z );
    if ( len == _LITERAL( 0.0 ) ) len = _LITERAL( 1.0 );
    ilen = _LITERAL( 1.0 ) / len;
    vz.x *= ilen;
    vz.y *= ilen;
    vz.z *= ilen;

    // Vector3CrossProduct( up, vz )
    _VEC3_TYPE vx = { up.y * vz.z - up.z * vz.y, up.z * vz.x - up.x * vz.z, up.x * vz.y - up.y * vz.x };

    // Vector3Normalize( x )
    v = vx;
    len = _SQRT( v.x * v.x + v.y * v.y + v.z * v.z );
    if ( len == _LITERAL( 0.0 ) ) len = _LITERAL( 1.0 );
    ilen = _LITERAL( 1.0 ) / len;
    vx.x *= ilen;
    vx.y *= ilen;
    vx.z *= ilen;

    // Vector3CrossProduct( vz, vx )
    _VEC3_TYPE vy = { vz.y * vx.z - vz.z * vx.y, vz.z * vx.x - vz.x * vx.z, vz.x * vx.y - vz.y * vx.x };

    result.m00 = vx.x;
    result.m10 = vy.x;
    result.m20 = vz.x;
    result.m30 = _LITERAL( 0.0 );
    result.m01 = vx.y;
    result.m11 = vy.y;
    result.m21 = vz.y;
    result.m31 = _LITERAL( 0.0 );
    result.m02 = vx.z;
    result.m12 = vy.z;
    result.m22 = vz.z;
    result.m32 = _LITERAL( 0.0 );
    result.m03 = -( vx.x * eye.x + vx.y * eye.y + vx.z * eye.z );   // Vector3DotProduct( vx, eye )
    result.m13 = -( vy.x * eye.x + vy.y * eye.y + vy.z * eye.z );   // Vector3DotProduct( vy, eye )
    result.m23 = -( vz.x * eye.x + vz.y * eye.y + vz.z * eye.z );   // Vector3DotProduct( vz, eye )
    result.m33 = _LITERAL( 1.0 );

    return result;
}

// Decompose a transformation matrix into its rotational, translational and scaling components
_FUNC_SPEC void _FUNC_CONV _FUNC_MAT4( decompose )( _MAT4_TYPE m, _VEC3_TYPE *translation, _QUAT_TYPE *rotation, _VEC3_TYPE *scale )
{
    // Extract translation.
    translation->x = m.m03;
    translation->y = m.m13;
    translation->z = m.m23;

    // Extract upper-left for determinant computation
    const _BASE_TYPE a = m.m00;
    const _BASE_TYPE b = m.m01;
    const _BASE_TYPE c = m.m02;
    const _BASE_TYPE d = m.m10;
    const _BASE_TYPE e = m.m11;
    const _BASE_TYPE f = m.m12;
    const _BASE_TYPE g = m.m20;
    const _BASE_TYPE h = m.m21;
    const _BASE_TYPE i = m.m22;
    const _BASE_TYPE A = e * i - f * h;
    const _BASE_TYPE B = f * g - d * i;
    const _BASE_TYPE C = d * h - e * g;

    // Extract scale
    const _BASE_TYPE det = a * A + b * B + c * C;
    _VEC3_TYPE abc = { a, b, c };
    _VEC3_TYPE def = { d, e, f };
    _VEC3_TYPE ghi = { g, h, i };

    _BASE_TYPE scalex = _FUNC_VEC3( len )( abc );
    _BASE_TYPE scaley = _FUNC_VEC3( len )( def );
    _BASE_TYPE scalez = _FUNC_VEC3( len )( ghi );
    _VEC3_TYPE s = { scalex, scaley, scalez };

    if ( det < _LITERAL( 0.0 ) ) s = _FUNC_VEC3( negate )( s );

    *scale = s;

    // Remove scale from the matrix if it is not close to zero
    _MAT4_TYPE clone = m;
    if ( !_FEQ( det, _LITERAL( 0.0 ), _LITERAL( 0.0001 ) ) )
    {
        clone.m00 /= s.x;
        clone.m11 /= s.y;
        clone.m22 /= s.z;

        // Extract rotation
        *rotation = _FUNC_QUAT( from_mat4 )( clone );
    }
    else
    {
        // Set to identity if close to zero
        *rotation = _FUNC_QUAT( identity )();
    }
}

// Get _BASE_TYPE array of matrix data. convert matrix to a flat array
_FUNC_SPEC _FMAT4_TYPE _FUNC_CONV _FUNC_MAT4( flatten )( _MAT4_TYPE m )
{
    _FMAT4_TYPE result = { 0 };

    result.m[ 0 ] = m.m00;
    result.m[ 1 ] = m.m10;
    result.m[ 2 ] = m.m20;
    result.m[ 3 ] = m.m30;

    result.m[ 4 ] = m.m01;
    result.m[ 5 ] = m.m11;
    result.m[ 6 ] = m.m21;
    result.m[ 7 ] = m.m31;

    result.m[ 8 ] = m.m02;
    result.m[ 9 ] = m.m12;
    result.m[ 10 ] = m.m22;
    result.m[ 11 ] = m.m32;

    result.m[ 12 ] = m.m03;
    result.m[ 13 ] = m.m13;
    result.m[ 14 ] = m.m23;
    result.m[ 15 ] = m.m33;

    return result;
}

#endif /* _IS_IEC559 */
#endif /* LINEAR_ALGEBRA_MAT4_IMPLEMENTATION */

/*
 * -----------------------------
 * MATRIX 4X4
 * -----------------------------
 * =============================
 */



// cleanup defined macros
#include "_linear_algebra_end.h"