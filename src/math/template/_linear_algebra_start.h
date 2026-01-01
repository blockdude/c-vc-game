// TODO:
// * try and figure out better macro names that won't collide and maybe don't start with underscore?

// LINEAR_ALGEBRA_TYPE_INFORMATION
#if defined(LINEAR_ALGEBRA_INT) || defined(LINEAR_ALGEBRA_I32) || defined(LINEAR_ALGEBRA_I64)
#define _IS_IEC559 0
#elif defined(LINEAR_ALGEBRA_FLT) || defined(LINEAR_ALGEBRA_F32) || defined(LINEAR_ALGEBRA_F64)
#define _IS_IEC559 1
#endif

// LINEAR_ALGEBRA_TYPES_AND_FIXES
#if defined(LINEAR_ALGEBRA_INT)
#define _VEC2_NAME vec2i
#define _VEC3_NAME vec3i
#define _VEC4_NAME vec4i
#define _QUAT_NAME quati
#define _MAT4_NAME mat4i
#define _FMAT4_NAME fmat4i
#define _BASE_TYPE int
#elif defined(LINEAR_ALGEBRA_I32)
#define _VEC2_NAME vec2_i32
#define _VEC3_NAME vec3_i32
#define _VEC4_NAME vec4_i32
#define _QUAT_NAME quat_i32
#define _MAT4_NAME mat4_i32
#define _FMAT4_NAME fmat4_i32
#define _BASE_TYPE i32
#elif defined(LINEAR_ALGEBRA_I64)
#define _VEC2_NAME vec2_i64
#define _VEC3_NAME vec3_i64
#define _VEC4_NAME vec4_i64
#define _QUAT_NAME quat_i64
#define _MAT4_NAME mat4_i64
#define _FMAT4_NAME fmat4_i64
#define _BASE_TYPE i64
#elif defined(LINEAR_ALGEBRA_FLT)
#define _VEC2_NAME vec2
#define _VEC3_NAME vec3
#define _VEC4_NAME vec4
#define _QUAT_NAME quat
#define _MAT4_NAME mat4
#define _FMAT4_NAME fmat4
#define _BASE_TYPE float
#elif defined(LINEAR_ALGEBRA_F32)
#define _VEC2_NAME vec2_f32
#define _VEC3_NAME vec3_f32
#define _VEC4_NAME vec4_f32
#define _QUAT_NAME quat_f32
#define _MAT4_NAME mat4_f32
#define _FMAT4_NAME fmat4_f32
#define _BASE_TYPE f32
#elif defined(LINEAR_ALGEBRA_F64)
#define _VEC2_NAME vec2_f64
#define _VEC3_NAME vec3_f64
#define _VEC4_NAME vec4_f64
#define _QUAT_NAME quat_f64
#define _MAT4_NAME mat4_f64
#define _FMAT4_NAME fmat4_f64
#define _BASE_TYPE f64
#endif

// LINEAR_ALGEBRA_MATH
#if defined(LINEAR_ALGEBRA_INT) || defined(LINEAR_ALGEBRA_I32)
#define _SQRT _la_i32_sqrt
#define _ABS _la_i32_abs
#define _MIN _la_i32_min
#define _MAX _la_i32_max
#elif defined(LINEAR_ALGEBRA_I64)
#define _SQRT _la_i64_sqrt
#define _ABS _la_i64_abs
#define _MIN _la_i64_min
#define _MAX _la_i64_max
#elif defined(LINEAR_ALGEBRA_FLT) || defined(LINEAR_ALGEBRA_F32)
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
#elif defined(LINEAR_ALGEBRA_F64)
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
#endif

// IF NO SPECIFIC IMPLEMENTATION IS DEFINED THEN DEFINE ALL OF THEM
#ifdef LINEAR_ALGEBRA_IMPLEMENTATION
#if \
!defined(LINEAR_ALGEBRA_VEC2_IMPLEMENTATION) && \
!defined(LINEAR_ALGEBRA_VEC3_IMPLEMENTATION) && \
!defined(LINEAR_ALGEBRA_VEC4_IMPLEMENTATION) && \
!defined(LINEAR_ALGEBRA_QUAT_IMPLEMENTATION) && \
!defined(LINEAR_ALGEBRA_MAT4_IMPLEMENTATION)
#define LINEAR_ALGEBRA_VEC2_IMPLEMENTATION
#define LINEAR_ALGEBRA_VEC3_IMPLEMENTATION
#define LINEAR_ALGEBRA_VEC4_IMPLEMENTATION
#define LINEAR_ALGEBRA_QUAT_IMPLEMENTATION
#define LINEAR_ALGEBRA_MAT4_IMPLEMENTATION
#endif
#endif

#define _VEC2_TYPE struct _VEC2_NAME
#define _VEC3_TYPE struct _VEC3_NAME
#define _VEC4_TYPE struct _VEC4_NAME
#define _QUAT_TYPE struct _QUAT_NAME
#define _MAT4_TYPE struct _MAT4_NAME
#define _FMAT4_TYPE struct _FMAT4_NAME
#define _CONCAT(_a, _b) _a##_b
#define _STATIC_CAST(T, _e) ((T)(_e))
#define _NAME_HELPER(_prefix, _fn) _CONCAT(_prefix, _##_fn)
#define _FUNC_VEC2(_fn) _NAME_HELPER(_VEC2_NAME, _fn)
#define _FUNC_VEC3(_fn) _NAME_HELPER(_VEC3_NAME, _fn)
#define _FUNC_VEC4(_fn) _NAME_HELPER(_VEC4_NAME, _fn)
#define _FUNC_QUAT(_fn) _NAME_HELPER(_QUAT_NAME, _fn)
#define _FUNC_MAT4(_fn) _NAME_HELPER(_MAT4_NAME, _fn)
#define _FUNC_FMAT4(_fn) _NAME_HELPER(_FMAT4_NAME, _fn)
#define _FUNC_SPEC
#define _FUNC_CONV

#define _FUNC_DECL(...) __VA_ARGS__
#ifdef LINEAR_ALGEBRA_IMPLEMENTATION
#define _FUNC_IMPL(...) __VA_ARGS__
#else
#define _FUNC_IMPL(...)
#endif

#define _RESTRICTION_NONE(...) __VA_ARGS__
#if _IS_IEC559
#define _RESTRICTION_FLOAT(...) __VA_ARGS__
#define _RESTRICTION_INT(...)
#else
#define _RESTRICTION_FLOAT(...)
#define _RESTRICTION_INT(...) __VA_ARGS__
#endif

#if defined(LINEAR_ALGEBRA_VEC2_HEADER) || defined(LINEAR_ALGEBRA_VEC2_IMPLEMENTATION)
#define _VEC2_FUNC_DECL(...)                  _FUNC_DECL(_RESTRICTION_NONE(__VA_ARGS__))
#define _VEC2_FUNC_IMPL(...)                  _FUNC_IMPL(_RESTRICTION_NONE(__VA_ARGS__))
#define _VEC2_FUNC_DECL_FLOAT_RESTRICTED(...) _FUNC_DECL(_RESTRICTION_FLOAT(__VA_ARGS__))
#define _VEC2_FUNC_IMPL_FLOAT_RESTRICTED(...) _FUNC_IMPL(_RESTRICTION_FLOAT(__VA_ARGS__))
#define _VEC2_FUNC_DECL_INT_RESTRICTED(...)   _FUNC_DECL(_RESTRICTION_INT(__VA_ARGS__))
#define _VEC2_FUNC_IMPL_INT_RESTRICTED(...)   _FUNC_IMPL(_RESTRICTION_INT(__VA_ARGS__))
#else
#define _VEC2_FUNC_DECL(...)
#define _VEC2_FUNC_IMPL(...)
#define _VEC2_FUNC_DECL_FLOAT_RESTRICTED(...)
#define _VEC2_FUNC_IMPL_FLOAT_RESTRICTED(...)
#define _VEC2_FUNC_DECL_INT_RESTRICTED(...)
#define _VEC2_FUNC_IMPL_INT_RESTRICTED(...)
#endif

#if defined(LINEAR_ALGEBRA_VEC3_HEADER) || defined(LINEAR_ALGEBRA_VEC3_IMPLEMENTATION)
#define _VEC3_FUNC_DECL(...)                  _FUNC_DECL(_RESTRICTION_NONE(__VA_ARGS__))
#define _VEC3_FUNC_IMPL(...)                  _FUNC_IMPL(_RESTRICTION_NONE(__VA_ARGS__))
#define _VEC3_FUNC_DECL_FLOAT_RESTRICTED(...) _FUNC_DECL(_RESTRICTION_FLOAT(__VA_ARGS__))
#define _VEC3_FUNC_IMPL_FLOAT_RESTRICTED(...) _FUNC_IMPL(_RESTRICTION_FLOAT(__VA_ARGS__))
#define _VEC3_FUNC_DECL_INT_RESTRICTED(...)   _FUNC_DECL(_RESTRICTION_INT(__VA_ARGS__))
#define _VEC3_FUNC_IMPL_INT_RESTRICTED(...)   _FUNC_IMPL(_RESTRICTION_INT(__VA_ARGS__))
#else
#define _VEC3_FUNC_DECL(...)
#define _VEC3_FUNC_IMPL(...)
#define _VEC3_FUNC_DECL_FLOAT_RESTRICTED(...)
#define _VEC3_FUNC_IMPL_FLOAT_RESTRICTED(...)
#define _VEC3_FUNC_DECL_INT_RESTRICTED(...)
#define _VEC3_FUNC_IMPL_INT_RESTRICTED(...)
#endif

#if defined(LINEAR_ALGEBRA_VEC4_HEADER) || defined(LINEAR_ALGEBRA_VEC4_IMPLEMENTATION)
#define _VEC4_FUNC_DECL(...)                  _FUNC_DECL(_RESTRICTION_NONE(__VA_ARGS__))
#define _VEC4_FUNC_IMPL(...)                  _FUNC_IMPL(_RESTRICTION_NONE(__VA_ARGS__))
#define _VEC4_FUNC_DECL_FLOAT_RESTRICTED(...) _FUNC_DECL(_RESTRICTION_FLOAT(__VA_ARGS__))
#define _VEC4_FUNC_IMPL_FLOAT_RESTRICTED(...) _FUNC_IMPL(_RESTRICTION_FLOAT(__VA_ARGS__))
#define _VEC4_FUNC_DECL_INT_RESTRICTED(...)   _FUNC_DECL(_RESTRICTION_INT(__VA_ARGS__))
#define _VEC4_FUNC_IMPL_INT_RESTRICTED(...)   _FUNC_IMPL(_RESTRICTION_INT(__VA_ARGS__))
#else
#define _VEC4_FUNC_DECL(...)
#define _VEC4_FUNC_IMPL(...)
#define _VEC4_FUNC_DECL_FLOAT_RESTRICTED(...)
#define _VEC4_FUNC_IMPL_FLOAT_RESTRICTED(...)
#define _VEC4_FUNC_DECL_INT_RESTRICTED(...)
#define _VEC4_FUNC_IMPL_INT_RESTRICTED(...)
#endif

#if defined(LINEAR_ALGEBRA_QUAT_HEADER) || defined(LINEAR_ALGEBRA_QUAT_IMPLEMENTATION)
#define _QUAT_FUNC_DECL(...)                  _FUNC_DECL(_RESTRICTION_NONE(__VA_ARGS__))
#define _QUAT_FUNC_IMPL(...)                  _FUNC_IMPL(_RESTRICTION_NONE(__VA_ARGS__))
#define _QUAT_FUNC_DECL_FLOAT_RESTRICTED(...) _FUNC_DECL(_RESTRICTION_FLOAT(__VA_ARGS__))
#define _QUAT_FUNC_IMPL_FLOAT_RESTRICTED(...) _FUNC_IMPL(_RESTRICTION_FLOAT(__VA_ARGS__))
#define _QUAT_FUNC_DECL_INT_RESTRICTED(...)   _FUNC_DECL(_RESTRICTION_INT(__VA_ARGS__))
#define _QUAT_FUNC_IMPL_INT_RESTRICTED(...)   _FUNC_IMPL(_RESTRICTION_INT(__VA_ARGS__))
#else
#define _QUAT_FUNC_DECL(...)
#define _QUAT_FUNC_IMPL(...)
#define _QUAT_FUNC_DECL_FLOAT_RESTRICTED(...)
#define _QUAT_FUNC_IMPL_FLOAT_RESTRICTED(...)
#define _QUAT_FUNC_DECL_INT_RESTRICTED(...)
#define _QUAT_FUNC_IMPL_INT_RESTRICTED(...)
#endif

#if defined(LINEAR_ALGEBRA_MAT4_HEADER) || defined(LINEAR_ALGEBRA_MAT4_IMPLEMENTATION)
#define _MAT4_FUNC_DECL(...)                  _FUNC_DECL(_RESTRICTION_NONE(__VA_ARGS__))
#define _MAT4_FUNC_IMPL(...)                  _FUNC_IMPL(_RESTRICTION_NONE(__VA_ARGS__))
#define _MAT4_FUNC_DECL_FLOAT_RESTRICTED(...) _FUNC_DECL(_RESTRICTION_FLOAT(__VA_ARGS__))
#define _MAT4_FUNC_IMPL_FLOAT_RESTRICTED(...) _FUNC_IMPL(_RESTRICTION_FLOAT(__VA_ARGS__))
#define _MAT4_FUNC_DECL_INT_RESTRICTED(...)   _FUNC_DECL(_RESTRICTION_INT(__VA_ARGS__))
#define _MAT4_FUNC_IMPL_INT_RESTRICTED(...)   _FUNC_IMPL(_RESTRICTION_INT(__VA_ARGS__))
#else
#define _MAT4_FUNC_DECL(...)
#define _MAT4_FUNC_IMPL(...)
#define _MAT4_FUNC_DECL_FLOAT_RESTRICTED(...)
#define _MAT4_FUNC_IMPL_FLOAT_RESTRICTED(...)
#define _MAT4_FUNC_DECL_INT_RESTRICTED(...)
#define _MAT4_FUNC_IMPL_INT_RESTRICTED(...)
#endif

// INTERNAL STATIC FUNCTIONS FOR IMPLEMENTATION
#ifdef LINEAR_ALGEBRA_IMPLEMENTATION
#ifndef _LINEAR_ALGEBRA_INTERNAL
#define _LINEAR_ALGEBRA_INTERNAL

#include <stdint.h>
#include <assert.h>
#include <math.h>

static inline i32 _la_i32_abs(i32 a)
{
    return a < 0 ? -a : a;
}

static inline i64 _la_i64_abs(i64 a)
{
    return a < 0 ? -a : a;
}

static inline i32 _la_i32_min(i32 a, i32 b)
{
    return a < b ? a : b;
}

static inline i64 _la_i64_min(i64 a, i64 b)
{
    return a < b ? a : b;
}

static inline i32 _la_i32_max(i32 a, i32 b)
{
    return a > b ? a : b;
}

static inline i64 _la_i64_max(i64 a, i64 b)
{
    return a > b ? a : b;
}

static inline i32 _la_i32_sqrt(i32 a)
{
    assert(a >= 0);
    return (i32) sqrtf((float) a);
}

static inline i64 _la_i64_sqrt(i64 a)
{
    assert(a >= 0);
    return (i64) sqrt((double) a);
}

static inline int _la_f32_equals(f32 a, f32 b, f32 epsilon)
{
    int result = (fabsf(a - b)) <= (epsilon * fmaxf(1.0f, fmaxf(fabsf(a), fabsf(b))));
    return result;
}

static inline int _la_f64_equals(f64 a, f64 b, f64 epsilon)
{
    int result = (fabs(a - b)) <= (epsilon * fmax(1.0, fmax(fabs(a), fabs(b))));
    return result;
}

#endif /* _LINEAR_ALGEBRA_INTERNAL */
#endif /* LINEAR_ALGEBRA_IMPLEMENATION */