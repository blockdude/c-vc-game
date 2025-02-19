#ifndef VCP_VEC3_H
#define VCP_VEC3_H

#include "int32/vec3_i32.h"
#include "int64/vec3_i64.h"
#include "float32/vec3_f32.h"
#include "float64/vec3_f64.h"

/*
 * =============================
 * -----------------------------
 * DEFAULT
 * -----------------------------
 */

#define vec3_zero vec3_f32_zero
#define vec3_one vec3_f32_one
#define vec3_add vec3_f32_add
#define vec3_add_val vec3_f32_add_val
#define vec3_sub vec3_f32_sub
#define vec3_sub_val vec3_f32_sub_val
#define vec3_scale vec3_f32_scale
#define vec3_mul vec3_f32_mul
#define vec3_cross vec3_f32_cross
#define vec3_perpendicular vec3_f32_perpendicular
#define vec3_center vec3_f32_center
#define vec3_len vec3_f32_len
#define vec3_len_sq vec3_f32_len_sq
#define vec3_dot vec3_f32_dot
#define vec3_dist vec3_f32_dist
#define vec3_dist_sq vec3_f32_dist_sq
#define vec3_angle vec3_f32_angle
#define vec3_negate vec3_f32_negate
#define vec3_div vec3_f32_div
#define vec3_normalize vec3_f32_normalize
#define vec3_project vec3_f32_project
#define vec3_reject vec3_f32_reject
#define vec3_ortho_normalize vec3_f32_ortho_normalize
#define vec3_transform vec3_f32_transform
#define vec3_rotate vec3_f32_rotate
#define vec3_rotate_around_axis vec3_f32_rotate_around_axis
#define vec3_move_towards vec3_f32_move_towards
#define vec3_lerp vec3_f32_lerp
#define vec3_cubic_hermite vec3_f32_cubic_hermite
#define vec3_reflect vec3_f32_reflect
#define vec3_min vec3_f32_min
#define vec3_max vec3_f32_max
#define vec3_barycenter vec3_f32_barycenter
#define vec3_unproject vec3_f32_unproject
#define vec3_invert vec3_f32_invert
#define vec3_clamp vec3_f32_clamp
#define vec3_clamp_val vec3_f32_clamp_val
#define vec3_clamp_len vec3_f32_clamp_len
#define vec3_equals vec3_f32_equals
#define vec3_refract vec3_f32_refract

/*
 * =============================
 */

#endif