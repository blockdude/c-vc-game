#define __CONCAT__( _a, _b ) _a##_b

#define __DECL_HELPER__( _prefix, _fn ) __CONCAT__( _prefix, _##_fn )
#define __DECL__( _fn ) __DECL_HELPER__( __FUNC_PREFIX__, _fn )

#define __LITERAL_HELPER__( _v, _s ) __CONCAT__( _v, _s )
#define __LITERAL__( _v ) __LITERAL_HELPER__( _v, __BASE_SUFFIX__ )

// Vector2 with components value LIT( 0.0 )
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( zero )( void )
{
    __VEC2_TYPE__ result = { __LITERAL__( 0.0 ), __LITERAL__( 0.0 ) };
    return result;
}

// Vector2 with components value LIT( 1.0 )
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( one )( void )
{
    __VEC2_TYPE__ result = { __LITERAL__( 1.0 ), __LITERAL__( 1.0 ) };
    return result;
}

// Add two vectors (a + b)
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( add )( __VEC2_TYPE__ a, __VEC2_TYPE__ b )
{
    __VEC2_TYPE__ result = { a.x + b.x, a.y + b.y };
    return result;
}

// Add a value to a vector
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( add_val )( __VEC2_TYPE__ v, __BASE_TYPE__ val )
{
    __VEC2_TYPE__ result = { v.x + val, v.y + val };
    return result;
}

// Subtract two vectors (a - b)
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( sub )( __VEC2_TYPE__ a, __VEC2_TYPE__ b )
{
    __VEC2_TYPE__ result = { a.x - b.x, a.y - b.y };
    return result;
}

// Subtract a value from a vector
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( sub_val )( __VEC2_TYPE__ v, __BASE_TYPE__ val )
{
    __VEC2_TYPE__ result = { v.x - val, v.y - val };
    return result;
}

// Calculate the length of a vector
__FUNC_SPEC__ __BASE_TYPE__ __DECL__( len )( __VEC2_TYPE__ v )
{
    __BASE_TYPE__ result = __SQRT__( ( v.x * v.x ) + ( v.y * v.y ) );
    return result;
}

// Calculate the squared length of a vector
__FUNC_SPEC__ __BASE_TYPE__ __DECL__( len_sq )( __VEC2_TYPE__ v )
{
    __BASE_TYPE__ result = ( v.x * v.x ) + ( v.y * v.y );
    return result;
}

// Calculate two vectors dot product
__FUNC_SPEC__ __BASE_TYPE__ __DECL__( dot )( __VEC2_TYPE__ a, __VEC2_TYPE__ b )
{
    __BASE_TYPE__ result = ( a.x * b.x ) + ( a.y * b.y );
    return result;
}

// Calculate distance between two vectors
__FUNC_SPEC__ __BASE_TYPE__ __DECL__( dist )( __VEC2_TYPE__ a, __VEC2_TYPE__ b )
{
    __BASE_TYPE__ result = __SQRT__( ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) );
    return result;
}

// Calculate squared distance between two vectors
__FUNC_SPEC__ __BASE_TYPE__ __DECL__( dist_sq )( __VEC2_TYPE__ a, __VEC2_TYPE__ b )
{
    __BASE_TYPE__ result = ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y );
    return result;
}

// Calculate angle between two vectors
// NOTE: Angle is calculated from origin point (0, 0)
__FUNC_SPEC__ __BASE_TYPE__ __DECL__( angle )( __VEC2_TYPE__ a, __VEC2_TYPE__ b )
{
    __BASE_TYPE__ result = __LITERAL__( 0.0 );

    __BASE_TYPE__ dot = a.x * b.x + a.y * b.y;
    __BASE_TYPE__ det = a.x * b.y - a.y * b.x;

    result = __ATAN2__( det, dot );

    return result;
}

// Calculate angle defined by a two vectors line
// NOTE: Parameters need to be normalized
// Current implementation should be aligned with glm::angle
__FUNC_SPEC__ __BASE_TYPE__ __DECL__( line_angle )( __VEC2_TYPE__ start, __VEC2_TYPE__ end )
{
    __BASE_TYPE__ result = __LITERAL__( 0.0 );

    result = -__ATAN2__( end.y - start.y, end.x - start.x );

    return result;
}

// Scale vector (multiply by value)
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( scale )( __VEC2_TYPE__ v, __BASE_TYPE__ scale )
{
    __VEC2_TYPE__ result = { v.x * scale, v.y * scale };
    return result;
}

// Multiply vector by vector
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( mul )( __VEC2_TYPE__ a, __VEC2_TYPE__ b )
{
    __VEC2_TYPE__ result = { a.x * b.x, a.y * b.y };
    return result;
}

// Negate vector
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( negate )( __VEC2_TYPE__ v )
{
    __VEC2_TYPE__ result = { -v.x, -v.y };
    return result;
}

// Divide vector by vector
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( div )( __VEC2_TYPE__ a, __VEC2_TYPE__ b )
{
    __VEC2_TYPE__ result = { a.x / b.x, a.y / b.y };

    return result;
}

// Normalize provided vector
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( normalize )( __VEC2_TYPE__ v )
{
    __VEC2_TYPE__ result = { 0 };

    __BASE_TYPE__ len = __SQRT__( ( v.x * v.x ) + ( v.y * v.y ) );
    if ( len > 0 )
    {
        __BASE_TYPE__ ilen = __LITERAL__( 1.0 ) / len;
        result.x = v.x * ilen;
        result.y = v.y * ilen;
    }

    return result;
}

// Transforms a TYPE by a given Matrix
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( transform )( __VEC2_TYPE__ v, struct mat4_f32 m )
{
    __VEC2_TYPE__ result = { 0 };

    __BASE_TYPE__ x = v.x;
    __BASE_TYPE__ y = v.y;
    __BASE_TYPE__ z = __LITERAL__( 0.0 );

    result.x = m.m00 * x + m.m01 * y + m.m02 * z + m.m03;
    result.y = m.m10 * x + m.m11 * y + m.m12 * z + m.m13;

    return result;
}

// Calculate linear interpolation between two vectors
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( lerp )( __VEC2_TYPE__ a, __VEC2_TYPE__ b, __BASE_TYPE__ t )
{
    __VEC2_TYPE__ result = { 0 };

    result.x = a.x + t * ( b.x - a.x );
    result.y = a.y + t * ( b.y - a.y );

    return result;
}

// Calculate reflected vector to normal
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( reflect )( __VEC2_TYPE__ v, __VEC2_TYPE__ normal )
{
    __VEC2_TYPE__ result = { 0 };

    __BASE_TYPE__ dot = ( v.x * normal.x + v.y * normal.y );

    result.x = v.x - ( __LITERAL__( 2.0 ) * normal.x ) * dot;
    result.y = v.y - ( __LITERAL__( 2.0 ) * normal.y ) * dot;

    return result;
}

// Get min value for each pair of components
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( min )( __VEC2_TYPE__ a, __VEC2_TYPE__ b )
{
    __VEC2_TYPE__ result = { 0 };

    result.x = __MIN__( a.x, b.x );
    result.y = __MIN__( a.y, b.y );

    return result;
}

// Get max value for each pair of components
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( max )( __VEC2_TYPE__ a, __VEC2_TYPE__ b )
{
    __VEC2_TYPE__ result = { 0 };

    result.x = __MAX__( a.x, b.x );
    result.y = __MAX__( a.y, b.y );

    return result;
}

// Rotate vector by angle
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( rotate )( __VEC2_TYPE__ v, __BASE_TYPE__ angle )
{
    __VEC2_TYPE__ result = { 0 };

    __BASE_TYPE__ c = __COS__( angle );
    __BASE_TYPE__ s = __SIN__( angle );

    result.x = v.x * c - v.y * s;
    result.y = v.x * s + v.y * c;

    return result;
}

// Move Vector towards target
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( move_towards )( __VEC2_TYPE__ v, __VEC2_TYPE__ target, __BASE_TYPE__ max )
{
    __VEC2_TYPE__ result = { 0 };

    __BASE_TYPE__ dx = target.x - v.x;
    __BASE_TYPE__ dy = target.y - v.y;
    __BASE_TYPE__ value = ( dx * dx ) + ( dy * dy );

    if ( ( value == 0 ) || ( ( max >= 0 ) && ( value <= max * max ) ) )
        return target;

    __BASE_TYPE__ dist = __SQRT__( value );

    result.x = v.x + dx / dist * max;
    result.y = v.y + dy / dist * max;

    return result;
}

// Invert the given vector
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( invert )( __VEC2_TYPE__ v )
{
    __VEC2_TYPE__ result = { __LITERAL__( 1.0 ) / v.x, __LITERAL__( 1.0 ) / v.y };
    return result;
}

// Clamp the components of the vector between
// min and max values specified by the given vectors
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( clamp )( __VEC2_TYPE__ v, __VEC2_TYPE__ min, __VEC2_TYPE__ max )
{
    __VEC2_TYPE__ result = { 0 };

    result.x = __MIN__( max.x, __MAX__( min.x, v.x ) );
    result.y = __MIN__( max.y, __MAX__( min.y, v.y ) );

    return result;
}

// Clamp the components of the vector between
// min and max values
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( clamp_val )( __VEC2_TYPE__ v, __BASE_TYPE__ min, __BASE_TYPE__ max )
{
    __VEC2_TYPE__ result = { 0 };

    result.x = __MIN__( max, __MAX__( min, v.x ) );
    result.y = __MIN__( max, __MAX__( min, v.y ) );

    return result;
}

// Clamp the magnitude of the vector between two min and max values
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( clamp_len )( __VEC2_TYPE__ v, __BASE_TYPE__ min, __BASE_TYPE__ max )
{
    __VEC2_TYPE__ result = v;

    __BASE_TYPE__ len = ( v.x * v.x ) + ( v.y * v.y );
    if ( len > __LITERAL__( 0.0 ) )
    {
        len = __SQRT__( len );

        __BASE_TYPE__ scale = __LITERAL__( 1.0 );    // By default, 1 as the neutral element.
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
__FUNC_SPEC__ int __DECL__( equals )( __VEC2_TYPE__ p, __VEC2_TYPE__ q, __BASE_TYPE__ epsilon )
{
    int result =
        ( ( __ABS__( p.x - q.x ) ) <= ( epsilon * __MAX__( __LITERAL__( 1.0 ), __MAX__( __ABS__( p.x ), __ABS__( q.x ) ) ) ) ) &&
        ( ( __ABS__( p.y - q.y ) ) <= ( epsilon * __MAX__( __LITERAL__( 1.0 ), __MAX__( __ABS__( p.y ), __ABS__( q.y ) ) ) ) );

    return result;
}

// Compute the direction of a refracted ray
// v: normalized direction of the incoming ray
// n: normalized normal vector of the interface of two optical media
// r: ratio of the refractive index of the medium from where the ray comes
//    to the refractive index of the medium on the other side of the surface
__FUNC_SPEC__ __VEC2_TYPE__ __DECL__( refract )( __VEC2_TYPE__ v, __VEC2_TYPE__ n, __BASE_TYPE__ r )
{
    __VEC2_TYPE__ result = { 0 };

    __BASE_TYPE__ dot = v.x * n.x + v.y * n.y;
    __BASE_TYPE__ d = __LITERAL__( 1.0 ) - r * r * ( __LITERAL__( 1.0 ) - dot * dot );

    if ( d >= __LITERAL__( 0.0 ) )
    {
        d = __SQRT__( d );
        v.x = r * v.x - ( r * dot + d ) * n.x;
        v.y = r * v.y - ( r * dot + d ) * n.y;

        result = v;
    }

    return result;
}

#undef __VEC2_TYPE__
#undef __BASE_TYPE__
#undef __FUNC_SPEC__
#undef __FUNC_PREFIX__
#undef __BASE_SUFFIX__
#undef __SIN__
#undef __COS__
#undef __TAN__
#undef __ATAN2__
#undef __SQRT__
#undef __ABS__
#undef __MIN__
#undef __MAX__