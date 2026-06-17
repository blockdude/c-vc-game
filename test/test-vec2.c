#include "utest.h"
#include <vcp/vcp.h>

UTEST(vec2, zero)
{
    struct Vec2 v = vec2_zero();
    EXPECT_EQ(v.x, 0.0f);
    EXPECT_EQ(v.y, 0.0f);
}

UTEST(vec2, one)
{
    struct Vec2 v = vec2_one();
    EXPECT_EQ(v.x, 1.0f);
    EXPECT_EQ(v.y, 1.0f);
}

UTEST(vec2, add)
{
    struct Vec2 a = { 1.0f, 2.0f };
    struct Vec2 b = { 3.0f, 4.0f };
    struct Vec2 c = vec2_add(a, b);
    EXPECT_EQ(c.x, 4.0f);
    EXPECT_EQ(c.y, 6.0f);
}

UTEST(vec2, sub)
{
    struct Vec2 a = { 5.0f, 6.0f };
    struct Vec2 b = { 2.0f, 3.0f };
    struct Vec2 c = vec2_sub(a, b);
    EXPECT_EQ(c.x, 3.0f);
    EXPECT_EQ(c.y, 3.0f);
}

UTEST(vec2, scale)
{
    struct Vec2 v = { 2.0f, 3.0f };
    struct Vec2 r = vec2_scale(v, 2.0f);
    EXPECT_EQ(r.x, 4.0f);
    EXPECT_EQ(r.y, 6.0f);
}

UTEST(vec2, dot)
{
    struct Vec2 a = { 1.0f, 0.0f };
    struct Vec2 b = { 0.0f, 1.0f };
    EXPECT_EQ(vec2_dot(a, b), 0.0f);

    struct Vec2 c = { 1.0f, 0.0f };
    struct Vec2 d = { 1.0f, 0.0f };
    EXPECT_EQ(vec2_dot(c, d), 1.0f);
}

UTEST(vec2, len)
{
    struct Vec2 v = { 3.0f, 4.0f };
    EXPECT_EQ(vec2_len(v), 5.0f);
}

UTEST(vec2, len_sq)
{
    struct Vec2 v = { 3.0f, 4.0f };
    EXPECT_EQ(vec2_len_sq(v), 25.0f);
}

UTEST(vec2, normalize)
{
    struct Vec2 v = { 3.0f, 0.0f };
    struct Vec2 r = vec2_normalize(v);
    EXPECT_EQ(r.x, 1.0f);
    EXPECT_EQ(r.y, 0.0f);
}

UTEST(vec2, negate)
{
    struct Vec2 v = { 1.0f, -2.0f };
    struct Vec2 r = vec2_negate(v);
    EXPECT_EQ(r.x, -1.0f);
    EXPECT_EQ(r.y, 2.0f);
}

UTEST(vec2, lerp)
{
    struct Vec2 a = { 0.0f, 0.0f };
    struct Vec2 b = { 10.0f, 20.0f };
    struct Vec2 r = vec2_lerp(a, b, 0.5);
    EXPECT_EQ(r.x, 5.0f);
    EXPECT_EQ(r.y, 10.0f);
}

UTEST(vec2, cross)
{
    struct Vec2 a = { 1.0f, 0.0f };
    struct Vec2 b = { 0.0f, 1.0f };
    float r = vec2_cross(a, b);
    EXPECT_EQ(r, 1.0f);
}

UTEST(vec2, dist)
{
    struct Vec2 a = { 0.0f, 0.0f };
    struct Vec2 b = { 3.0f, 4.0f };
    EXPECT_EQ(vec2_dist(a, b), 5.0f);
}

UTEST(vec2, reflect)
{
    struct Vec2 v = { 1.0f, -1.0f };
    struct Vec2 n = { 0.0f, 1.0f };
    struct Vec2 r = vec2_reflect(v, n);
    EXPECT_EQ(r.x, 1.0f);
    EXPECT_EQ(r.y, 1.0f);
}

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
