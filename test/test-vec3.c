#include "utest.h"
#include <vcp/vcp.h>

UTEST(vec3, zero)
{
    struct Vec3 v = vec3_zero();
    EXPECT_EQ(v.x, 0.0f);
    EXPECT_EQ(v.y, 0.0f);
    EXPECT_EQ(v.z, 0.0f);
}

UTEST(vec3, one)
{
    struct Vec3 v = vec3_one();
    EXPECT_EQ(v.x, 1.0f);
    EXPECT_EQ(v.y, 1.0f);
    EXPECT_EQ(v.z, 1.0f);
}

UTEST(vec3, add)
{
    struct Vec3 a = { 1.0f, 2.0f, 3.0f };
    struct Vec3 b = { 4.0f, 5.0f, 6.0f };
    struct Vec3 c = vec3_add(a, b);
    EXPECT_EQ(c.x, 5.0f);
    EXPECT_EQ(c.y, 7.0f);
    EXPECT_EQ(c.z, 9.0f);
}

UTEST(vec3, sub)
{
    struct Vec3 a = { 5.0f, 6.0f, 7.0f };
    struct Vec3 b = { 2.0f, 3.0f, 4.0f };
    struct Vec3 c = vec3_sub(a, b);
    EXPECT_EQ(c.x, 3.0f);
    EXPECT_EQ(c.y, 3.0f);
    EXPECT_EQ(c.z, 3.0f);
}

UTEST(vec3, scale)
{
    struct Vec3 v = { 2.0f, 3.0f, 4.0f };
    struct Vec3 r = vec3_scale(v, 2.0f);
    EXPECT_EQ(r.x, 4.0f);
    EXPECT_EQ(r.y, 6.0f);
    EXPECT_EQ(r.z, 8.0f);
}

UTEST(vec3, dot)
{
    struct Vec3 a = { 1.0f, 0.0f, 0.0f };
    struct Vec3 b = { 0.0f, 1.0f, 0.0f };
    EXPECT_EQ(vec3_dot(a, b), 0.0f);

    struct Vec3 c = { 1.0f, 0.0f, 0.0f };
    struct Vec3 d = { 1.0f, 0.0f, 0.0f };
    EXPECT_EQ(vec3_dot(c, d), 1.0f);
}

UTEST(vec3, cross)
{
    struct Vec3 a = { 1.0f, 0.0f, 0.0f };
    struct Vec3 b = { 0.0f, 1.0f, 0.0f };
    struct Vec3 r = vec3_cross(a, b);
    EXPECT_EQ(r.x, 0.0f);
    EXPECT_EQ(r.y, 0.0f);
    EXPECT_EQ(r.z, 1.0f);
}

UTEST(vec3, len)
{
    struct Vec3 v = { 1.0f, 2.0f, 2.0f };
    EXPECT_EQ(vec3_len(v), 3.0f);
}

UTEST(vec3, len_sq)
{
    struct Vec3 v = { 1.0f, 2.0f, 2.0f };
    EXPECT_EQ(vec3_len_sq(v), 9.0f);
}

UTEST(vec3, normalize)
{
    struct Vec3 v = { 3.0f, 0.0f, 0.0f };
    struct Vec3 r = vec3_normalize(v);
    EXPECT_EQ(r.x, 1.0f);
    EXPECT_EQ(r.y, 0.0f);
    EXPECT_EQ(r.z, 0.0f);
}

UTEST(vec3, negate)
{
    struct Vec3 v = { 1.0f, -2.0f, 3.0f };
    struct Vec3 r = vec3_negate(v);
    EXPECT_EQ(r.x, -1.0f);
    EXPECT_EQ(r.y, 2.0f);
    EXPECT_EQ(r.z, -3.0f);
}

UTEST(vec3, lerp)
{
    struct Vec3 a = { 0.0f, 0.0f, 0.0f };
    struct Vec3 b = { 10.0f, 20.0f, 30.0f };
    struct Vec3 r = vec3_lerp(a, b, 0.5f);
    EXPECT_EQ(r.x, 5.0f);
    EXPECT_EQ(r.y, 10.0f);
    EXPECT_EQ(r.z, 15.0f);
}

UTEST(vec3, reflect)
{
    struct Vec3 v = { 1.0f, -1.0f, 0.0f };
    struct Vec3 n = { 0.0f, 1.0f, 0.0f };
    struct Vec3 r = vec3_reflect(v, n);
    EXPECT_EQ(r.x, 1.0f);
    EXPECT_EQ(r.y, 1.0f);
    EXPECT_EQ(r.z, 0.0f);
}

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
