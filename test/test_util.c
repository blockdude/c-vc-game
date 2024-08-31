#include "utest.h"
#include <util/util.h>

UTEST( util, clamp )
{
	int x;

	x = CLAMP( 100, 0, 50 );
	EXPECT_EQ( x, 50 );
	x = CLAMP( -3, 0, 50 );
	EXPECT_EQ( x, 0 );
}

UTEST( util, max )
{
	int x;
	x = MAX( 10, 32 );
	EXPECT_EQ( x, 32 );
	x = MAX( 21, 3 );
	EXPECT_EQ( x, 21 );
}

UTEST( util, min )
{
	int x;
	x = MIN( 10, 32 );
	EXPECT_EQ( x, 10 );
	x = MIN( 21, 3 );
	EXPECT_EQ( x, 3 );
}

UTEST( util, degtorad )
{
	float x;
	x = DEGTORAD( 45.0f );
	EXPECT_EQ( x, PI / 4.0f );
	x = DEGTORAD( 90.0f );
	EXPECT_EQ( x, PI / 2.0f );
	x = DEGTORAD( 135.0f );
	EXPECT_EQ( x, 3.0f * PI / 4.0f );
	x = DEGTORAD( 180.0f );
	EXPECT_EQ( x, PI );
}

UTEST( util, radtodeg )
{
	float x;
	x = RADTODEG( PI / 4.0f );
	EXPECT_EQ( x, 45.0f );
	x = RADTODEG( PI / 2.0f );
	EXPECT_EQ( x, 90.0f );
	x = RADTODEG( 3.0f * PI / 4.0f );
	EXPECT_EQ( x, 135.0f );
	x = RADTODEG( PI );
	EXPECT_EQ( x, 180.0f );
}

UTEST( util, flteq )
{
	EXPECT_TRUE( flteq( 1.0001f, 1.0002f, 0.0001f ) );
	EXPECT_FALSE( flteq( 1.0001f, 1.0003f, 0.0001f ) );
}

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
