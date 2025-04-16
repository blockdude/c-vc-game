#ifndef VCP_QUAT_H
#define VCP_QUAT_H

#define LINEAR_ALGEBRA_QUAT_HEADER

#ifdef __cplusplus
extern "C" {
#endif

#define LINEAR_ALGEBRA_INT
#include "template/_linear_algebra_template.h"
#undef LINEAR_ALGEBRA_INT

#define LINEAR_ALGEBRA_I32
#include "template/_linear_algebra_template.h"
#undef LINEAR_ALGEBRA_I32

#define LINEAR_ALGEBRA_I64
#include "template/_linear_algebra_template.h"
#undef LINEAR_ALGEBRA_I64

#define LINEAR_ALGEBRA_FLT
#include "template/_linear_algebra_template.h"
#undef LINEAR_ALGEBRA_FLT

#define LINEAR_ALGEBRA_F32
#include "template/_linear_algebra_template.h"
#undef LINEAR_ALGEBRA_F32

#define LINEAR_ALGEBRA_F64
#include "template/_linear_algebra_template.h"
#undef LINEAR_ALGEBRA_F64

#ifdef __cplusplus
}
#endif

#undef LINEAR_ALGEBRA_QUAT_HEADER

#endif