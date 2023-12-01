#include "utest.h"
#include <gfx/obj3d.h>
#include <util/fmath.h>

struct obj3d_test_fixture
{
	int initialized;
	struct obj3d obj;
};

UTEST_F_SETUP( obj3d_test_fixture )
{
	struct obj3d *obj = &utest_fixture->obj;
	utest_fixture->initialized = obj3d_load( obj, "../res/objects/rayman.obj" );
	ASSERT_EQ( utest_fixture->initialized, 0 );
	ASSERT_GT( obj->f_len, ( size_t )0 );
}

UTEST_F_TEARDOWN( obj3d_test_fixture )
{
	ASSERT_EQ( utest_fixture->initialized, 0 );
	obj3d_free( &utest_fixture->obj );
}

static int obj3d_test_fixture_vert_compare( struct vert va, struct vert vb )
{
	int res = 1;
	res = res & ( va.v.x == vb.v.x );
	res = res & ( va.v.y == vb.v.y );
	res = res & ( va.v.z == vb.v.z );

	res = res & ( va.vt.x == vb.vt.x );
	res = res & ( va.vt.y == vb.vt.y );

	res = res & ( va.vn.x == vb.vn.x );
	res = res & ( va.vn.y == vb.vn.y );
	res = res & ( va.vn.z == vb.vn.z );
	return res;
}

UTEST_F( obj3d_test_fixture, validate_f )
{
	struct obj3d *obj = &utest_fixture->obj;

	struct vert f_first = {
		.v  = { { -0.967716f, 11.993134f, -0.156907f } },
		.vt = { { 0.4033f   , 0.3064f				 } },
		.vn = { { -0.3183f  , -0.6137f  , -0.7226f   } }
	};

	struct vert f_last = {
		.v  = { { 0.536469f, 9.000515f, 1.657671f } },
		.vt = { { 0.205f   , 0.3177f              } },
		.vn = { { 0.4359f  , -0.5951f , 0.6751f   } }
	};

	struct vert f;
	f = obj->f[ 0 ];

	EXPECT_TRUE( obj3d_test_fixture_vert_compare( f, f_first ) );

	f = obj->f[ obj->f_len - 1 ];

	EXPECT_TRUE( obj3d_test_fixture_vert_compare( f, f_last ) );
}

UTEST_F( obj3d_test_fixture, validate_v )
{
	struct obj3d *obj = &utest_fixture->obj;

	vec3s v;
	v = obj->v[ 0 ];

	EXPECT_EQ( v.x, -0.967716f );
	EXPECT_EQ( v.y, 11.993134f );
	EXPECT_EQ( v.z, -0.156907f );

	v = obj->v[ obj->v_len - 1 ];

	EXPECT_EQ( v.x, -0.026541f );
	EXPECT_EQ( v.y, 8.850442f );
	EXPECT_EQ( v.z, 1.286151f );
}

UTEST_F( obj3d_test_fixture, validate_vt )
{
	struct obj3d *obj = &utest_fixture->obj;

	vec2s v;
	v = obj->vt[ 0 ];

	EXPECT_EQ( v.x, 0.4033f );
	EXPECT_EQ( v.y, 0.3064f );

	v = obj->vt[ obj->vt_len - 1 ];

	EXPECT_EQ( v.x, 0.1814f );
	EXPECT_EQ( v.y, 0.3465f );
}

UTEST_F( obj3d_test_fixture, validate_vn )
{
	struct obj3d *obj = &utest_fixture->obj;

	vec3s v;
	v = obj->vn[ 0 ];

	EXPECT_EQ( v.x, -0.3183f );
	EXPECT_EQ( v.y, -0.6137f );
	EXPECT_EQ( v.z, -0.7226f );

	v = obj->vn[ obj->vn_len - 1 ];

	EXPECT_EQ( v.x, -0.0081f );
	EXPECT_EQ( v.y, -0.9930f );
	EXPECT_EQ( v.z, 0.1175f );
}

UTEST_F( obj3d_test_fixture, validate_extent )
{
	struct obj3d *obj = &utest_fixture->obj;

	EXPECT_TRUE( fltcmp( obj->dia, 17.460607338f, 0.000000001f ) );

	EXPECT_TRUE( fltcmp( obj->center.x, 0.00865102f, 0.00000001f ) );
	EXPECT_TRUE( fltcmp( obj->center.y, 6.98831547f, 0.00000001f ) );
	EXPECT_TRUE( fltcmp( obj->center.z, 0.8941009f , 0.0000001f  ) );

	EXPECT_TRUE( fltcmp( obj->min.x, -4.32404613f, 0.00000001f ) );
	EXPECT_TRUE( fltcmp( obj->min.y, 0.025872f   , 0.000001f   ) );
	EXPECT_TRUE( fltcmp( obj->min.z, -2.1009481f , 0.0000001f  ) );

	EXPECT_TRUE( fltcmp( obj->max.x, 4.34134817f , 0.00000001f ) );
	EXPECT_TRUE( fltcmp( obj->max.y, 13.95075893f, 0.00000001f ) );
	EXPECT_TRUE( fltcmp( obj->max.z, 3.8891499f  , 0.0000001f  ) );
}

UTEST_F( obj3d_test_fixture, validate_properties )
{
	struct obj3d *obj = &utest_fixture->obj;

	// values calculated before hand
	EXPECT_EQ( obj->stride, ( size_t )32 );
	EXPECT_EQ( obj->f_len, ( size_t )1869 );
	EXPECT_EQ( obj->f_nbytes, ( size_t )59808 );
	EXPECT_EQ( sizeof( struct vert ), sizeof( float ) * 8 );
}

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
