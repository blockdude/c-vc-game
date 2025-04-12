#ifndef VCP_MATH_H
#define VCP_MATH_H

#include <math.h>
#include "../util/types.h"

#ifdef WIN32

#undef MIN
#undef MAX
#undef min
#undef max

#endif

#define EULER   2.71828182845904523536028747135266249
#define PI_2    1.57079632679489661923132169163975144
#define PI      3.14159265358979323846264338327950288
#define TAU     6.28318530717958647692528676655900576
#define EPSILON 0.0001

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define SIGN(v) (((v) > 0) - ((v) < 0))

#define CLAMP(v, mn, mx) MAX(mn, MIN(mx, v))

#define DEGTORAD(x) ((x) * (PI / 180.0))
#define RADTODEG(x) ((x) * (180.0 / PI))

#define LERP(a, b, t) ((a) + (t) * ((b) - (a)))
#define NORMALIZE(x, min, max) (((x) - (min)) / ((max) - (min)))

#define _MATH_FUNC_TEMPLATE_INT_DIVRND(T, _name) \
static inline T _name##_divrnd(T n, T d) { return ((n < 0) == (d < 0)) ? ((n + d / 2) / d) : ((n - d / 2) / d); }

_MATH_FUNC_TEMPLATE_INT_DIVRND(int, int);
_MATH_FUNC_TEMPLATE_INT_DIVRND(i32, int32);
_MATH_FUNC_TEMPLATE_INT_DIVRND(i64, int64);

#define _MATH_FUNC_TEMPLATE_INT_DIVFLR(T, _name) \
static inline T _name##_divflr(T n, T d) { return (n / d) - (n < 0); }

_MATH_FUNC_TEMPLATE_INT_DIVFLR(int, int);
_MATH_FUNC_TEMPLATE_INT_DIVFLR(i32, int32);
_MATH_FUNC_TEMPLATE_INT_DIVFLR(i64, int64);

#define _MATH_FUNC_TEMPLATE_FLOAT_EQUALS(T, _name, _abs_fn, _max_fn) \
static inline int _name##_equals(T a, T b, T epsilon) { return (_abs_fn(a - b)) <= (epsilon * _max_fn(1.0f, _max_fn(_abs_fn(a), _abs_fn(b)))); }

_MATH_FUNC_TEMPLATE_FLOAT_EQUALS(float, float, fabsf, fmaxf);
_MATH_FUNC_TEMPLATE_FLOAT_EQUALS(f32, float32, fabsf, fmaxf);
_MATH_FUNC_TEMPLATE_FLOAT_EQUALS(f64, float64, fabs, fmax);

#endif
