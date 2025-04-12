#ifndef TYPE_CAST_H
#define TYPE_CAST_H

#include "types.h"

#define _VEC2_FUNC_TEMPLATE_CAST(T, name) \
static inline struct vec2     name##_to_vec2    (T a) { const struct vec2     b = { (float)a.x, (float)a.y }; return b; } \
static inline struct vec2i    name##_to_vec2i   (T a) { const struct vec2i    b = {   (int)a.x,   (int)a.y }; return b; } \
static inline struct vec2_i32 name##_to_vec2_i32(T a) { const struct vec2_i32 b = {   (i32)a.x,   (i32)a.y }; return b; } \
static inline struct vec2_i64 name##_to_vec2_i64(T a) { const struct vec2_i64 b = {   (i64)a.x,   (i64)a.y }; return b; } \
static inline struct vec2_f32 name##_to_vec2_f32(T a) { const struct vec2_f32 b = {   (f32)a.x,   (f32)a.y }; return b; } \
static inline struct vec2_f64 name##_to_vec2_f64(T a) { const struct vec2_f64 b = {   (f64)a.x,   (f64)a.y }; return b; }

_VEC2_FUNC_TEMPLATE_CAST(struct vec2, vec2);
_VEC2_FUNC_TEMPLATE_CAST(struct vec2i, vec2i);
_VEC2_FUNC_TEMPLATE_CAST(struct vec2_i32, vec2_i32);
_VEC2_FUNC_TEMPLATE_CAST(struct vec2_i64, vec2_i64);
_VEC2_FUNC_TEMPLATE_CAST(struct vec2_f32, vec2_f32);
_VEC2_FUNC_TEMPLATE_CAST(struct vec2_f64, vec2_f64);

#define _VEC3_FUNC_TEMPLATE_CAST(T, name) \
static inline struct vec3     name##_to_vec3    (T a) { const struct vec3     b = { (float)a.x, (float)a.y, (float)a.z }; return b; } \
static inline struct vec3i    name##_to_vec3i   (T a) { const struct vec3i    b = {   (int)a.x,   (int)a.y,   (int)a.z }; return b; } \
static inline struct vec3_i32 name##_to_vec3_i32(T a) { const struct vec3_i32 b = {   (i32)a.x,   (i32)a.y,   (i32)a.z }; return b; } \
static inline struct vec3_i64 name##_to_vec3_i64(T a) { const struct vec3_i64 b = {   (i64)a.x,   (i64)a.y,   (i64)a.z }; return b; } \
static inline struct vec3_f32 name##_to_vec3_f32(T a) { const struct vec3_f32 b = {   (f32)a.x,   (f32)a.y,   (f32)a.z }; return b; } \
static inline struct vec3_f64 name##_to_vec3_f64(T a) { const struct vec3_f64 b = {   (f64)a.x,   (f64)a.y,   (f64)a.z }; return b; }

_VEC3_FUNC_TEMPLATE_CAST(struct vec3, vec3);
_VEC3_FUNC_TEMPLATE_CAST(struct vec3i, vec3i);
_VEC3_FUNC_TEMPLATE_CAST(struct vec3_i32, vec3_i32);
_VEC3_FUNC_TEMPLATE_CAST(struct vec3_i64, vec3_i64);
_VEC3_FUNC_TEMPLATE_CAST(struct vec3_f32, vec3_f32);
_VEC3_FUNC_TEMPLATE_CAST(struct vec3_f64, vec3_f64);

#define _VEC4_FUNC_TEMPLATE_CAST(T, name) \
static inline struct vec4     name##_to_vec4    (T a) { const struct vec4     b = { (float)a.x, (float)a.y, (float)a.z, (float)a.w }; return b; } \
static inline struct vec4i    name##_to_vec4i   (T a) { const struct vec4i    b = {   (int)a.x,   (int)a.y,   (int)a.z,   (int)a.w }; return b; } \
static inline struct vec4_i32 name##_to_vec4_i32(T a) { const struct vec4_i32 b = {   (i32)a.x,   (i32)a.y,   (i32)a.z,   (i32)a.w }; return b; } \
static inline struct vec4_i64 name##_to_vec4_i64(T a) { const struct vec4_i64 b = {   (i64)a.x,   (i64)a.y,   (i64)a.z,   (i64)a.w }; return b; } \
static inline struct vec4_f32 name##_to_vec4_f32(T a) { const struct vec4_f32 b = {   (f32)a.x,   (f32)a.y,   (f32)a.z,   (f32)a.w }; return b; } \
static inline struct vec4_f64 name##_to_vec4_f64(T a) { const struct vec4_f64 b = {   (f64)a.x,   (f64)a.y,   (f64)a.z,   (f64)a.w }; return b; }

_VEC4_FUNC_TEMPLATE_CAST(struct vec4, vec4);
_VEC4_FUNC_TEMPLATE_CAST(struct vec4i, vec4i);
_VEC4_FUNC_TEMPLATE_CAST(struct vec4_i32, vec4_i32);
_VEC4_FUNC_TEMPLATE_CAST(struct vec4_i64, vec4_i64);
_VEC4_FUNC_TEMPLATE_CAST(struct vec4_f32, vec4_f32);
_VEC4_FUNC_TEMPLATE_CAST(struct vec4_f64, vec4_f64);

#define _QUAT_FUNC_TEMPLATE_CAST(T, name) \
static inline struct quat     name##_to_quat    (T a) { const struct quat     b = { (float)a.x, (float)a.y, (float)a.z, (float)a.w }; return b; } \
static inline struct quati    name##_to_quati   (T a) { const struct quati    b = {   (int)a.x,   (int)a.y,   (int)a.z,   (int)a.w }; return b; } \
static inline struct quat_i32 name##_to_quat_i32(T a) { const struct quat_i32 b = {   (i32)a.x,   (i32)a.y,   (i32)a.z,   (i32)a.w }; return b; } \
static inline struct quat_i64 name##_to_quat_i64(T a) { const struct quat_i64 b = {   (i64)a.x,   (i64)a.y,   (i64)a.z,   (i64)a.w }; return b; } \
static inline struct quat_f32 name##_to_quat_f32(T a) { const struct quat_f32 b = {   (f32)a.x,   (f32)a.y,   (f32)a.z,   (f32)a.w }; return b; } \
static inline struct quat_f64 name##_to_quat_f64(T a) { const struct quat_f64 b = {   (f64)a.x,   (f64)a.y,   (f64)a.z,   (f64)a.w }; return b; }

_QUAT_FUNC_TEMPLATE_CAST(struct quat, quat);
_QUAT_FUNC_TEMPLATE_CAST(struct quati, quati);
_QUAT_FUNC_TEMPLATE_CAST(struct quat_i32, quat_i32);
_QUAT_FUNC_TEMPLATE_CAST(struct quat_i64, quat_i64);
_QUAT_FUNC_TEMPLATE_CAST(struct quat_f32, quat_f32);
_QUAT_FUNC_TEMPLATE_CAST(struct quat_f64, quat_f64);

#define _MAT4_FUNC_TEMPLATE_CAST(T, name) \
static inline struct mat4     name##_to_mat4    (T a) { const struct mat4     b = { (float)a.m00, (float)a.m01, (float)a.m02, (float)a.m03, (float)a.m10, (float)a.m11, (float)a.m12, (float)a.m13, (float)a.m20, (float)a.m21, (float)a.m22, (float)a.m23, (float)a.m30, (float)a.m31, (float)a.m32, (float)a.m33 }; return b; } \
static inline struct mat4i    name##_to_mat4i   (T a) { const struct mat4i    b = {   (int)a.m00,   (int)a.m01,   (int)a.m02,   (int)a.m03,   (int)a.m10,   (int)a.m11,   (int)a.m12,   (int)a.m13,   (int)a.m20,   (int)a.m21,   (int)a.m22,   (int)a.m23,   (int)a.m30,   (int)a.m31,   (int)a.m32,   (int)a.m33 }; return b; } \
static inline struct mat4_i32 name##_to_mat4_i32(T a) { const struct mat4_i32 b = {   (i32)a.m00,   (i32)a.m01,   (i32)a.m02,   (i32)a.m03,   (i32)a.m10,   (i32)a.m11,   (i32)a.m12,   (i32)a.m13,   (i32)a.m20,   (i32)a.m21,   (i32)a.m22,   (i32)a.m23,   (i32)a.m30,   (i32)a.m31,   (i32)a.m32,   (i32)a.m33 }; return b; } \
static inline struct mat4_i64 name##_to_mat4_i64(T a) { const struct mat4_i64 b = {   (i64)a.m00,   (i64)a.m01,   (i64)a.m02,   (i64)a.m03,   (i64)a.m10,   (i64)a.m11,   (i64)a.m12,   (i64)a.m13,   (i64)a.m20,   (i64)a.m21,   (i64)a.m22,   (i64)a.m23,   (i64)a.m30,   (i64)a.m31,   (i64)a.m32,   (i64)a.m33 }; return b; } \
static inline struct mat4_f32 name##_to_mat4_f32(T a) { const struct mat4_f32 b = {   (f32)a.m00,   (f32)a.m01,   (f32)a.m02,   (f32)a.m03,   (f32)a.m10,   (f32)a.m11,   (f32)a.m12,   (f32)a.m13,   (f32)a.m20,   (f32)a.m21,   (f32)a.m22,   (f32)a.m23,   (f32)a.m30,   (f32)a.m31,   (f32)a.m32,   (f32)a.m33 }; return b; } \
static inline struct mat4_f64 name##_to_mat4_f64(T a) { const struct mat4_f64 b = {   (f64)a.m00,   (f64)a.m01,   (f64)a.m02,   (f64)a.m03,   (f64)a.m10,   (f64)a.m11,   (f64)a.m12,   (f64)a.m13,   (f64)a.m20,   (f64)a.m21,   (f64)a.m22,   (f64)a.m23,   (f64)a.m30,   (f64)a.m31,   (f64)a.m32,   (f64)a.m33 }; return b; }

_MAT4_FUNC_TEMPLATE_CAST(struct mat4, mat4);
_MAT4_FUNC_TEMPLATE_CAST(struct mat4i, mat4i);
_MAT4_FUNC_TEMPLATE_CAST(struct mat4_i32, mat4_i32);
_MAT4_FUNC_TEMPLATE_CAST(struct mat4_i64, mat4_i64);
_MAT4_FUNC_TEMPLATE_CAST(struct mat4_f32, mat4_f32);
_MAT4_FUNC_TEMPLATE_CAST(struct mat4_f64, mat4_f64);

#define _FMAT4_FUNC_TEMPLATE_CAST(T, name) \
static inline struct fmat4     name##_to_fmat4    (T a) { const struct fmat4     b = { (float)a.m[ 0 ], (float)a.m[ 1 ], (float)a.m[ 2 ], (float)a.m[ 3 ], (float)a.m[ 4 ], (float)a.m[ 5 ], (float)a.m[ 6 ], (float)a.m[ 7 ], (float)a.m[ 8 ], (float)a.m[ 9 ], (float)a.m[ 10 ], (float)a.m[ 11 ], (float)a.m[ 12 ], (float)a.m[ 13 ], (float)a.m[ 14 ], (float)a.m[ 15 ] }; return b; } \
static inline struct fmat4i    name##_to_fmat4i   (T a) { const struct fmat4i    b = {   (int)a.m[ 0 ],   (int)a.m[ 1 ],   (int)a.m[ 2 ],   (int)a.m[ 3 ],   (int)a.m[ 4 ],   (int)a.m[ 5 ],   (int)a.m[ 6 ],   (int)a.m[ 7 ],   (int)a.m[ 8 ],   (int)a.m[ 9 ],   (int)a.m[ 10 ],   (int)a.m[ 11 ],   (int)a.m[ 12 ],   (int)a.m[ 13 ],   (int)a.m[ 14 ],   (int)a.m[ 15 ] }; return b; } \
static inline struct fmat4_i32 name##_to_fmat4_i32(T a) { const struct fmat4_i32 b = {   (i32)a.m[ 0 ],   (i32)a.m[ 1 ],   (i32)a.m[ 2 ],   (i32)a.m[ 3 ],   (i32)a.m[ 4 ],   (i32)a.m[ 5 ],   (i32)a.m[ 6 ],   (i32)a.m[ 7 ],   (i32)a.m[ 8 ],   (i32)a.m[ 9 ],   (i32)a.m[ 10 ],   (i32)a.m[ 11 ],   (i32)a.m[ 12 ],   (i32)a.m[ 13 ],   (i32)a.m[ 14 ],   (i32)a.m[ 15 ] }; return b; } \
static inline struct fmat4_i64 name##_to_fmat4_i64(T a) { const struct fmat4_i64 b = {   (i64)a.m[ 0 ],   (i64)a.m[ 1 ],   (i64)a.m[ 2 ],   (i64)a.m[ 3 ],   (i64)a.m[ 4 ],   (i64)a.m[ 5 ],   (i64)a.m[ 6 ],   (i64)a.m[ 7 ],   (i64)a.m[ 8 ],   (i64)a.m[ 9 ],   (i64)a.m[ 10 ],   (i64)a.m[ 11 ],   (i64)a.m[ 12 ],   (i64)a.m[ 13 ],   (i64)a.m[ 14 ],   (i64)a.m[ 15 ] }; return b; } \
static inline struct fmat4_f32 name##_to_fmat4_f32(T a) { const struct fmat4_f32 b = {   (f32)a.m[ 0 ],   (f32)a.m[ 1 ],   (f32)a.m[ 2 ],   (f32)a.m[ 3 ],   (f32)a.m[ 4 ],   (f32)a.m[ 5 ],   (f32)a.m[ 6 ],   (f32)a.m[ 7 ],   (f32)a.m[ 8 ],   (f32)a.m[ 9 ],   (f32)a.m[ 10 ],   (f32)a.m[ 11 ],   (f32)a.m[ 12 ],   (f32)a.m[ 13 ],   (f32)a.m[ 14 ],   (f32)a.m[ 15 ] }; return b; } \
static inline struct fmat4_f64 name##_to_fmat4_f64(T a) { const struct fmat4_f64 b = {   (f64)a.m[ 0 ],   (f64)a.m[ 1 ],   (f64)a.m[ 2 ],   (f64)a.m[ 3 ],   (f64)a.m[ 4 ],   (f64)a.m[ 5 ],   (f64)a.m[ 6 ],   (f64)a.m[ 7 ],   (f64)a.m[ 8 ],   (f64)a.m[ 9 ],   (f64)a.m[ 10 ],   (f64)a.m[ 11 ],   (f64)a.m[ 12 ],   (f64)a.m[ 13 ],   (f64)a.m[ 14 ],   (f64)a.m[ 15 ] }; return b; }

_FMAT4_FUNC_TEMPLATE_CAST(struct fmat4, fmat4);
_FMAT4_FUNC_TEMPLATE_CAST(struct fmat4i, fmat4i);
_FMAT4_FUNC_TEMPLATE_CAST(struct fmat4_i32, fmat4_i32);
_FMAT4_FUNC_TEMPLATE_CAST(struct fmat4_i64, fmat4_i64);
_FMAT4_FUNC_TEMPLATE_CAST(struct fmat4_f32, fmat4_f32);
_FMAT4_FUNC_TEMPLATE_CAST(struct fmat4_f64, fmat4_f64);

#endif
