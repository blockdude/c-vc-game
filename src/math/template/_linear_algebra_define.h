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

#define _FEQ _f32_equals
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

#define _FEQ _f32_equals
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

#define _FEQ _f32_equals
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

#define _FEQ _f64_equals
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

#endif /* LINEAR_ALGEBRA_CLEANUP */