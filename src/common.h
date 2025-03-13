#ifndef VCP_COMMON_H
#define VCP_COMMON_H

#include <stdint.h>

/*
 * =============================
 * -----------------------------
 * STANDARD TYPEDEFS
 * -----------------------------
 */

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

/*
 * =============================
 */

#define VCP_MAX_STRING_LEN 128
#define VCP_DECLSPEC
#define VCP_CALLCONV
#define VCP_UNUSED_VAR(_v) ((void)(_v))
#define VCP_CLITERAL(T) (T)

#endif