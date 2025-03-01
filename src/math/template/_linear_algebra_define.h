#ifdef LINEAR_ALGEBRA_CLEANUP
#undef LINEAR_ALGEBRA_CLEANUP

#undef _IS_IEC559

#undef _VEC2_TYPE
#undef _VEC3_TYPE
#undef _VEC4_TYPE
#undef _QUAT_TYPE
#undef _MAT4_TYPE
#undef _FMAT4_TYPE
#undef _BASE_TYPE
#undef _FLOAT_TYPE

#undef _FUNC_SPEC
#undef _FUNC_CONV

#undef _VEC2_PREFIX
#undef _VEC3_PREFIX
#undef _VEC4_PREFIX
#undef _MAT4_PREFIX
#undef _QUAT_PREFIX
#undef _BASE_SUFFIX
#undef _FLOAT_SUFFIX

#undef _FEQ
#undef _SIN
#undef _COS
#undef _TAN
#undef _ASIN
#undef _ACOS
#undef _ATAN2
#undef _SQRT
#undef _ABS
#undef _MIN
#undef _MAX

#undef _CONCAT
#undef _LITERAL_HELPER
#undef _LITERAL
#undef _B_LIT
#undef _F_LIT
#undef _NAME_HELPER
#undef _FUNC_VEC2
#undef _FUNC_VEC3
#undef _FUNC_VEC4
#undef _FUNC_QUAT
#undef _FUNC_MAT4

#else /* LINEAR_ALGEBRA_CLEANUP */

// 32 BIT INTEGER TYPES
#if defined( LINEAR_ALGEBRA_I32 )
#undef LINEAR_ALGEBRA_I32

#define _IS_IEC559 0

#define _VEC2_TYPE struct vec2_i32
#define _VEC3_TYPE struct vec3_i32
#define _VEC4_TYPE struct vec4_i32
#define _QUAT_TYPE struct quat_i32
#define _MAT4_TYPE struct mat4_i32
#define _FMAT4_TYPE struct fmat4_i32
#define _BASE_TYPE int32_t
#define _FLOAT_TYPE float

#define _VEC2_PREFIX vec2_i32
#define _VEC3_PREFIX vec3_i32
#define _VEC4_PREFIX vec4_i32
#define _MAT4_PREFIX mat4_i32
#define _QUAT_PREFIX quat_i32
#define _BASE_SUFFIX
#define _FLOAT_SUFFIX f

#define _FEQ _la_f32_equals
#define _SIN sinf
#define _COS cosf
#define _TAN tanf
#define _ASIN asinf
#define _ACOS acosf
#define _ATAN2 atan2f
#define _SQRT _la_i32_sqrt
#define _ABS _la_i32_abs
#define _MIN _la_i32_min
#define _MAX _la_i32_max

// FLOAT TYPES
#elif defined( LINEAR_ALGEBRA_FLT )
#undef LINEAR_ALGEBRA_FLT

#define _IS_IEC559 1

#define _VEC2_TYPE struct vec2
#define _VEC3_TYPE struct vec3
#define _VEC4_TYPE struct vec4
#define _QUAT_TYPE struct quat
#define _MAT4_TYPE struct mat4
#define _FMAT4_TYPE struct fmat4
#define _BASE_TYPE float
#define _FLOAT_TYPE float

#define _VEC2_PREFIX vec2
#define _VEC3_PREFIX vec3
#define _VEC4_PREFIX vec4
#define _MAT4_PREFIX mat4
#define _QUAT_PREFIX quat
#define _BASE_SUFFIX f
#define _FLOAT_SUFFIX f

#define _FEQ _la_f32_equals
#define _SIN sinf
#define _COS cosf
#define _TAN tanf
#define _ASIN asinf
#define _ACOS acosf
#define _ATAN2 atan2f
#define _SQRT sqrtf
#define _ABS fabsf
#define _MIN fminf
#define _MAX fminf

// 32 BIT FLOAT TYPES
#elif defined( LINEAR_ALGEBRA_F32 )
#undef LINEAR_ALGEBRA_F32

#define _IS_IEC559 1

#define _VEC2_TYPE struct vec2_f32
#define _VEC3_TYPE struct vec3_f32
#define _VEC4_TYPE struct vec4_f32
#define _QUAT_TYPE struct quat_f32
#define _MAT4_TYPE struct mat4_f32
#define _FMAT4_TYPE struct fmat4_f32
#define _BASE_TYPE float
#define _FLOAT_TYPE float

#define _VEC2_PREFIX vec2_f32
#define _VEC3_PREFIX vec3_f32
#define _VEC4_PREFIX vec4_f32
#define _MAT4_PREFIX mat4_f32
#define _QUAT_PREFIX quat_f32
#define _BASE_SUFFIX f
#define _FLOAT_SUFFIX f

#define _FEQ _la_f32_equals
#define _SIN sinf
#define _COS cosf
#define _TAN tanf
#define _ASIN asinf
#define _ACOS acosf
#define _ATAN2 atan2f
#define _SQRT sqrtf
#define _ABS fabsf
#define _MIN fminf
#define _MAX fminf

// 64 BIT FLOAT TYPES
#elif defined( LINEAR_ALGEBRA_F64 )
#undef LINEAR_ALGEBRA_F64

#define _IS_IEC559 1

#define _VEC2_TYPE struct vec2_f64
#define _VEC3_TYPE struct vec3_f64
#define _VEC4_TYPE struct vec4_f64
#define _QUAT_TYPE struct quat_f64
#define _MAT4_TYPE struct mat4_f64
#define _FMAT4_TYPE struct fmat4_f64
#define _BASE_TYPE double
#define _FLOAT_TYPE double

#define _VEC2_PREFIX vec2_f64
#define _VEC3_PREFIX vec3_f64
#define _VEC4_PREFIX vec4_f64
#define _MAT4_PREFIX mat4_f64
#define _QUAT_PREFIX quat_f64
#define _BASE_SUFFIX
#define _FLOAT_SUFFIX

#define _FEQ _la_f64_equals
#define _SIN sin
#define _COS cos
#define _TAN tan
#define _ASIN asin
#define _ACOS acos
#define _ATAN2 atan2
#define _SQRT sqrt
#define _ABS fabs
#define _MIN fmin
#define _MAX fmin

#else
#error "Only F32 and F64 version are supported"
#endif /* LINEAR_ALGEBRA_(TYPE)*/

#define _CONCAT( _a, _b ) _a##_b

#define _LITERAL_HELPER( _v, _s ) _CONCAT( _v, _s )
#define _LITERAL( _v ) _LITERAL_HELPER( _v, _BASE_SUFFIX )

#define _STATIC_CAST( T, _e ) ( ( T ) ( _e ) )
#define _B_LIT( _v ) _STATIC_CAST( _BASE_TYPE, _v )
#define _F_LIT( _v ) _STATIC_CAST( _FLOAT_TYPE, _v )

#define _NAME_HELPER( _prefix, _fn ) _CONCAT( _prefix, _##_fn )
#define _FUNC_VEC2( _fn ) _NAME_HELPER( _VEC2_PREFIX, _fn )
#define _FUNC_VEC3( _fn ) _NAME_HELPER( _VEC3_PREFIX, _fn )
#define _FUNC_VEC4( _fn ) _NAME_HELPER( _VEC4_PREFIX, _fn )
#define _FUNC_QUAT( _fn ) _NAME_HELPER( _QUAT_PREFIX, _fn )
#define _FUNC_MAT4( _fn ) _NAME_HELPER( _MAT4_PREFIX, _fn )

#ifdef LINEAR_ALGEBRA_IMPLEMENTATION

// define all implementations if none are defined
#if \
!defined( LINEAR_ALGEBRA_VEC2_IMPLEMENTATION ) && \
!defined( LINEAR_ALGEBRA_VEC3_IMPLEMENTATION ) && \
!defined( LINEAR_ALGEBRA_VEC4_IMPLEMENTATION ) && \
!defined( LINEAR_ALGEBRA_QUAT_IMPLEMENTATION ) && \
!defined( LINEAR_ALGEBRA_MAT4_IMPLEMENTATION )
#define LINEAR_ALGEBRA_VEC2_IMPLEMENTATION
#define LINEAR_ALGEBRA_VEC3_IMPLEMENTATION
#define LINEAR_ALGEBRA_VEC4_IMPLEMENTATION
#define LINEAR_ALGEBRA_QUAT_IMPLEMENTATION
#define LINEAR_ALGEBRA_MAT4_IMPLEMENTATION
#endif /* LINEAR_ALGEBRA_(TYPE)_IMPLENTATION */

#include <stdint.h>
#include <assert.h>
#include <math.h>

#define _FUNC_SPEC
#define _FUNC_CONV

#ifndef _LINEAR_ALGEBRA_INTERNAL
#define _LINEAR_ALGEBRA_INTERNAL

static inline int32_t _la_i32_abs( int32_t a )
{
    return a < 0 ? -a : a;
}

static inline int64_t _la_i64_abs( int64_t a )
{
    return a < 0 ? -a : a;
}

static inline int32_t _la_i32_min( int32_t a, int32_t b )
{
    return a < b ? a : b;
}

static inline int64_t _la_i64_min( int64_t a, int64_t b )
{
    return a < b ? a : b;
}

static inline int32_t _la_i32_max( int32_t a, int32_t b )
{
    return a > b ? a : b;
}

static inline int64_t _la_i64_max( int64_t a, int64_t b )
{
    return a > b ? a : b;
}

static inline int32_t _la_i32_sqrt( int32_t a )
{
    assert( a >= 0 );
    return ( int32_t ) sqrtf( ( float ) a );
}

static inline int64_t _la_i64_sqrt( int64_t a )
{
    assert( a >= 0 );
    return ( int64_t ) sqrt( ( double ) a );
}

static inline int _la_f32_equals( float a, float b, float epsilon )
{
    int result = ( fabsf( a - b ) ) <= ( epsilon * fmaxf( 1.0f, fmaxf( fabsf( a ), fabsf( b ) ) ) );
    return result;
}

static inline int _la_f64_equals( double a, double b, double epsilon )
{
    int result = ( fabs( a - b ) ) <= ( epsilon * fmax( 1.0, fmax( fabs( a ), fabs( b ) ) ) );
    return result;
}

#endif /* _LINEAR_ALGEBRA_INTERNAL */

#else /* LINEAR_ALGEBRA_IMPLEMENTATION */

#define _FUNC_SPEC
#define _FUNC_CONV

#endif /* LINEAR_ALGEBRA_IMPLEMENATION */

#endif /* LINEAR_ALGEBRA_CLEANUP */