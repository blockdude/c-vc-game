#include "utest.h"
#include <vcp/vcp.h>

UTEST(timestep, create_zero_rate)
{
    struct Timestep ts = timestep_create(0.0);
    EXPECT_EQ(ts.target_rate, 0.0);
    EXPECT_EQ(ts.target_delta, 0.0);
}

UTEST(timestep, create_60fps)
{
    struct Timestep ts = timestep_create(60.0);
    EXPECT_EQ(ts.target_rate, 60.0);
    EXPECT_TRUE(fabsf((float)ts.target_delta - 1.0f / 60.0f) < 0.0001f);
}

UTEST(timestep, create_negative_rate)
{
    struct Timestep ts = timestep_create(-30.0);
    EXPECT_EQ(ts.target_rate, -30.0);
    EXPECT_EQ(ts.target_delta, 0.0);
}

UTEST(timestep, set_rate)
{
    struct Timestep ts = timestep_create(30.0);
    timestep_set_rate(&ts, 60.0);
    EXPECT_EQ(ts.target_rate, 60.0);
    EXPECT_TRUE(fabsf((float)ts.target_delta - 1.0f / 60.0f) < 0.0001f);
}

UTEST(timestep, set_rate_zero)
{
    struct Timestep ts = timestep_create(60.0);
    timestep_set_rate(&ts, 0.0);
    EXPECT_EQ(ts.target_rate, 0.0);
    EXPECT_EQ(ts.target_delta, 0.0);
}

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
