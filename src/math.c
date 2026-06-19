#include <vcp/vcp.h>
#define LINEAR_ALGEBRA_IMPLEMENTATION

#define LINEAR_ALGEBRA_INT
#include <vcp/_internal/linear_algebra_template.h>
#undef LINEAR_ALGEBRA_INT

#define LINEAR_ALGEBRA_I32
#include <vcp/_internal/linear_algebra_template.h>
#undef LINEAR_ALGEBRA_I32

#define LINEAR_ALGEBRA_I64
#include <vcp/_internal/linear_algebra_template.h>
#undef LINEAR_ALGEBRA_I64

#define LINEAR_ALGEBRA_FLT
#include <vcp/_internal/linear_algebra_template.h>
#undef LINEAR_ALGEBRA_FLT

#define LINEAR_ALGEBRA_F32
#include <vcp/_internal/linear_algebra_template.h>
#undef LINEAR_ALGEBRA_F32

#define LINEAR_ALGEBRA_F64
#include <vcp/_internal/linear_algebra_template.h>
#undef LINEAR_ALGEBRA_F64