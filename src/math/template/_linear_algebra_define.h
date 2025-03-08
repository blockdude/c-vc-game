// TODO:
// * remove _FLOAT_TYPE (unused)
// * remove _BASE_SUFFIX (unused)
// * remove _FLOAT_SUFFIX (unused)
// * remove _LITERAL_HELPER and _LITERAL in favor of _STATIC_CAST
// * finish int type functions for vec3, vec4, quat, and mat4
// * seperate functions into their own file?

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

#undef _ZERO
#undef _ONE
#undef _TWO
#undef _THREE
#undef _FOUR

#undef _CONCAT
#undef _LITERAL_HELPER
#undef _LITERAL
#undef _STATIC_CAST
#undef _NAME_HELPER
#undef _FUNC_VEC2
#undef _FUNC_VEC3
#undef _FUNC_VEC4
#undef _FUNC_QUAT
#undef _FUNC_MAT4

#else /* LINEAR_ALGEBRA_CLEANUP */

// 32 BIT INTEGER TYPES
#if defined( LINEAR_ALGEBRA_INT )
#undef LINEAR_ALGEBRA_INT

#define _IS_IEC559 0

#define _VEC2_TYPE struct vec2i
#define _VEC3_TYPE struct vec3i
#define _VEC4_TYPE struct vec4i
#define _QUAT_TYPE struct quati
#define _MAT4_TYPE struct mat4i
#define _FMAT4_TYPE struct fmat4i
#define _BASE_TYPE int
#define _FLOAT_TYPE float

#define _VEC2_PREFIX vec2i
#define _VEC3_PREFIX vec3i
#define _VEC4_PREFIX vec4i
#define _MAT4_PREFIX mat4i
#define _QUAT_PREFIX quati
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

#define _ZERO 0
#define _ONE 1
#define _TWO 2
#define _THREE 3
#define _FOUR 4

#elif defined( LINEAR_ALGEBRA_I32 )
#undef LINEAR_ALGEBRA_I32

#define _IS_IEC559 0

#define _VEC2_TYPE struct vec2_i32
#define _VEC3_TYPE struct vec3_i32
#define _VEC4_TYPE struct vec4_i32
#define _QUAT_TYPE struct quat_i32
#define _MAT4_TYPE struct mat4_i32
#define _FMAT4_TYPE struct fmat4_i32
#define _BASE_TYPE i32
#define _FLOAT_TYPE f32

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

#define _ZERO 0
#define _ONE 1
#define _TWO 2
#define _THREE 3
#define _FOUR 4

#elif defined( LINEAR_ALGEBRA_I64 )
#undef LINEAR_ALGEBRA_I64

#define _IS_IEC559 0

#define _VEC2_TYPE struct vec2_i64
#define _VEC3_TYPE struct vec3_i64
#define _VEC4_TYPE struct vec4_i64
#define _QUAT_TYPE struct quat_i64
#define _MAT4_TYPE struct mat4_i64
#define _FMAT4_TYPE struct fmat4_i64
#define _BASE_TYPE i64
#define _FLOAT_TYPE f64

#define _VEC2_PREFIX vec2_i64
#define _VEC3_PREFIX vec3_i64
#define _VEC4_PREFIX vec4_i64
#define _MAT4_PREFIX mat4_i64
#define _QUAT_PREFIX quat_i64
#define _BASE_SUFFIX ll
#define _FLOAT_SUFFIX

#define _FEQ _la_f64_equals
#define _SIN sin
#define _COS cos
#define _TAN tan
#define _ASIN asin
#define _ACOS acos
#define _ATAN2 atan2
#define _SQRT _la_i64_sqrt
#define _ABS _la_i64_abs
#define _MIN _la_i64_min
#define _MAX _la_i64_max

#define _ZERO 0
#define _ONE 1
#define _TWO 2
#define _THREE 3
#define _FOUR 4

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

#define _ZERO 0.0f
#define _ONE 1.0f
#define _TWO 2.0f
#define _THREE 3.0f
#define _FOUR 4.0f

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
#define _BASE_TYPE f32
#define _FLOAT_TYPE f32

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

#define _ZERO 0.0f
#define _ONE 1.0f
#define _TWO 2.0f
#define _THREE 3.0f
#define _FOUR 4.0f

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
#define _BASE_TYPE f64
#define _FLOAT_TYPE f64

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

#define _ZERO 0.0
#define _ONE 1.0
#define _TWO 2.0
#define _THREE 3.0
#define _FOUR 4.0

#else
#error "Only F32 and F64 version are supported"
#endif /* LINEAR_ALGEBRA_(TYPE)*/

#define _CONCAT( _a, _b ) _a##_b

#define _LITERAL_HELPER( _v, _s ) _CONCAT( _v, _s )
#define _LITERAL( _v ) _LITERAL_HELPER( _v, _BASE_SUFFIX )
#define _STATIC_CAST( T, _e ) ( ( T ) ( _e ) )

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

static inline i32 _la_i32_abs( i32 a )
{
    return a < 0 ? -a : a;
}

static inline i64 _la_i64_abs( i64 a )
{
    return a < 0 ? -a : a;
}

static inline i32 _la_i32_min( i32 a, i32 b )
{
    return a < b ? a : b;
}

static inline i64 _la_i64_min( i64 a, i64 b )
{
    return a < b ? a : b;
}

static inline i32 _la_i32_max( i32 a, i32 b )
{
    return a > b ? a : b;
}

static inline i64 _la_i64_max( i64 a, i64 b )
{
    return a > b ? a : b;
}

static inline i32 _la_i32_sqrt( i32 a )
{
    assert( a >= 0 );
    return ( i32 ) sqrtf( ( float ) a );
}

static inline i64 _la_i64_sqrt( i64 a )
{
    assert( a >= 0 );
    return ( i64 ) sqrt( ( double ) a );
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

#else /* !LINEAR_ALGEBRA_IMPLEMENTATION */

#define _FUNC_SPEC
#define _FUNC_CONV

#endif /* LINEAR_ALGEBRA_IMPLEMENATION */

#endif /* LINEAR_ALGEBRA_CLEANUP */