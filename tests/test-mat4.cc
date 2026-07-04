#include "utest.h"
#include <vcp/vcp.h>

UTEST(mat4, identity)
{
    struct Mat4 m = mat4_identity();
    EXPECT_EQ(m.m00, 1.0f); EXPECT_EQ(m.m01, 0.0f); EXPECT_EQ(m.m02, 0.0f); EXPECT_EQ(m.m03, 0.0f);
    EXPECT_EQ(m.m10, 0.0f); EXPECT_EQ(m.m11, 1.0f); EXPECT_EQ(m.m12, 0.0f); EXPECT_EQ(m.m13, 0.0f);
    EXPECT_EQ(m.m20, 0.0f); EXPECT_EQ(m.m21, 0.0f); EXPECT_EQ(m.m22, 1.0f); EXPECT_EQ(m.m23, 0.0f);
    EXPECT_EQ(m.m30, 0.0f); EXPECT_EQ(m.m31, 0.0f); EXPECT_EQ(m.m32, 0.0f); EXPECT_EQ(m.m33, 1.0f);
}

UTEST(mat4, mul_identity)
{
    struct Mat4 a = mat4_identity();
    struct Mat4 b = mat4_identity();
    struct Mat4 c = mat4_mul(a, b);
    EXPECT_EQ(c.m00, 1.0f); EXPECT_EQ(c.m01, 0.0f); EXPECT_EQ(c.m02, 0.0f); EXPECT_EQ(c.m03, 0.0f);
    EXPECT_EQ(c.m10, 0.0f); EXPECT_EQ(c.m11, 1.0f); EXPECT_EQ(c.m12, 0.0f); EXPECT_EQ(c.m13, 0.0f);
    EXPECT_EQ(c.m20, 0.0f); EXPECT_EQ(c.m21, 0.0f); EXPECT_EQ(c.m22, 1.0f); EXPECT_EQ(c.m23, 0.0f);
    EXPECT_EQ(c.m30, 0.0f); EXPECT_EQ(c.m31, 0.0f); EXPECT_EQ(c.m32, 0.0f); EXPECT_EQ(c.m33, 1.0f);
}

UTEST(mat4, translate)
{
    struct Mat4 m = mat4_translate((struct Vec3){ 2.0f, 3.0f, 4.0f });
    EXPECT_EQ(m.m03, 2.0f);
    EXPECT_EQ(m.m13, 3.0f);
    EXPECT_EQ(m.m23, 4.0f);
}

UTEST(mat4, scale)
{
    struct Mat4 m = mat4_scale((struct Vec3){ 2.0f, 3.0f, 4.0f });
    EXPECT_EQ(m.m00, 2.0f);
    EXPECT_EQ(m.m11, 3.0f);
    EXPECT_EQ(m.m22, 4.0f);
    EXPECT_EQ(m.m33, 1.0f);
}

UTEST(mat4, transpose)
{
    struct Mat4 m = {
        .m00 = 1.0f, .m01 = 2.0f, .m02 = 3.0f, .m03 = 4.0f,
        .m10 = 5.0f, .m11 = 6.0f, .m12 = 7.0f, .m13 = 8.0f,
        .m20 = 9.0f, .m21 = 10.0f, .m22 = 11.0f, .m23 = 12.0f,
        .m30 = 13.0f, .m31 = 14.0f, .m32 = 15.0f, .m33 = 16.0f,
    };
    struct Mat4 t = mat4_transpose(m);
    EXPECT_EQ(t.m00, 1.0f); EXPECT_EQ(t.m01, 5.0f); EXPECT_EQ(t.m02, 9.0f);  EXPECT_EQ(t.m03, 13.0f);
    EXPECT_EQ(t.m10, 2.0f); EXPECT_EQ(t.m11, 6.0f); EXPECT_EQ(t.m12, 10.0f); EXPECT_EQ(t.m13, 14.0f);
    EXPECT_EQ(t.m20, 3.0f); EXPECT_EQ(t.m21, 7.0f); EXPECT_EQ(t.m22, 11.0f); EXPECT_EQ(t.m23, 15.0f);
    EXPECT_EQ(t.m30, 4.0f); EXPECT_EQ(t.m31, 8.0f); EXPECT_EQ(t.m32, 12.0f); EXPECT_EQ(t.m33, 16.0f);
}

UTEST(mat4, determinant)
{
    struct Mat4 m = mat4_identity();
    EXPECT_EQ(mat4_det(m), 1.0f);
}

UTEST(mat4, inverse_identity)
{
    struct Mat4 m = mat4_invert(mat4_identity());
    EXPECT_EQ(m.m00, 1.0f); EXPECT_EQ(m.m01, 0.0f); EXPECT_EQ(m.m02, 0.0f); EXPECT_EQ(m.m03, 0.0f);
    EXPECT_EQ(m.m10, 0.0f); EXPECT_EQ(m.m11, 1.0f); EXPECT_EQ(m.m12, 0.0f); EXPECT_EQ(m.m13, 0.0f);
    EXPECT_EQ(m.m20, 0.0f); EXPECT_EQ(m.m21, 0.0f); EXPECT_EQ(m.m22, 1.0f); EXPECT_EQ(m.m23, 0.0f);
    EXPECT_EQ(m.m30, 0.0f); EXPECT_EQ(m.m31, 0.0f); EXPECT_EQ(m.m32, 0.0f); EXPECT_EQ(m.m33, 1.0f);
}

UTEST(mat4, rotate_x)
{
    struct Mat4 m = mat4_rotate_x(0.0f);
    EXPECT_EQ(m.m00, 1.0f); EXPECT_EQ(m.m11, 1.0f); EXPECT_EQ(m.m22, 1.0f); EXPECT_EQ(m.m33, 1.0f);
}

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
