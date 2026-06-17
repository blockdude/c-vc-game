#include "utest.h"
#include <vcp/vcp.h>

UTEST(quat, identity)
{
    struct Quat q = quat_identity();
    EXPECT_EQ(q.x, 0.0f);
    EXPECT_EQ(q.y, 0.0f);
    EXPECT_EQ(q.z, 0.0f);
    EXPECT_EQ(q.w, 1.0f);
}

UTEST(quat, mul_identity)
{
    struct Quat a = quat_identity();
    struct Quat b = quat_identity();
    struct Quat c = quat_mul(a, b);
    EXPECT_EQ(c.x, 0.0f);
    EXPECT_EQ(c.y, 0.0f);
    EXPECT_EQ(c.z, 0.0f);
    EXPECT_EQ(c.w, 1.0f);
}

UTEST(quat, from_axis_angle_180)
{
    struct Quat q = quat_from_axis_angle((struct Vec3){ 0.0f, 1.0f, 0.0f }, PI);
    EXPECT_TRUE(fabsf(q.x - 0.0f) < 0.0001f);
    EXPECT_TRUE(fabsf(q.y - 1.0f) < 0.0001f);
    EXPECT_TRUE(fabsf(q.z - 0.0f) < 0.0001f);
    EXPECT_TRUE(fabsf(q.w - 0.0f) < 0.0001f);
}

UTEST(quat, rotate_vec3)
{
    struct Vec3 v = { 1.0f, 0.0f, 0.0f };
    struct Quat q = quat_from_axis_angle((struct Vec3){ 0.0f, 0.0f, 1.0f }, PI / 2.0f);
    struct Vec3 r = vec3_rotate(v, q);
    EXPECT_TRUE(fabsf(r.x - 0.0f) < 0.0001f);
    EXPECT_TRUE(fabsf(r.y - 1.0f) < 0.0001f);
    EXPECT_TRUE(fabsf(r.z - 0.0f) < 0.0001f);
}

UTEST(quat, invert)
{
    struct Quat q = quat_from_axis_angle((struct Vec3){ 0.0f, 1.0f, 0.0f }, PI / 4.0f);
    struct Quat inv = quat_invert(q);
    struct Quat result = quat_mul(q, inv);
    EXPECT_TRUE(fabsf(result.x - 0.0f) < 0.0001f);
    EXPECT_TRUE(fabsf(result.y - 0.0f) < 0.0001f);
    EXPECT_TRUE(fabsf(result.z - 0.0f) < 0.0001f);
    EXPECT_TRUE(fabsf(result.w - 1.0f) < 0.0001f);
}

UTEST(quat, from_euler)
{
    struct Quat q = quat_from_euler(0.0f, 0.0f, 0.0f);
    EXPECT_TRUE(fabsf(q.x - 0.0f) < 0.0001f);
    EXPECT_TRUE(fabsf(q.y - 0.0f) < 0.0001f);
    EXPECT_TRUE(fabsf(q.z - 0.0f) < 0.0001f);
    EXPECT_TRUE(fabsf(q.w - 1.0f) < 0.0001f);
}

UTEST(quat, normalize)
{
    struct Quat q = { 2.0f, 0.0f, 0.0f, 0.0f };
    struct Quat n = quat_normalize(q);
    EXPECT_EQ(n.x, 1.0f);
    EXPECT_EQ(n.y, 0.0f);
    EXPECT_EQ(n.z, 0.0f);
    EXPECT_EQ(n.w, 0.0f);
}

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
