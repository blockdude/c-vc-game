#include "utest.h"
#include <gfx/mesh.h>
#include <util/math.h>

struct mesh_test_fixture
{
	int initialized;
	struct mesh obj;
};

UTEST_F_SETUP( mesh_test_fixture )
{
	struct mesh *obj = &utest_fixture->obj;
	utest_fixture->initialized = mesh_load( obj, "res/objects/rayman.obj" );
	ASSERT_EQ( utest_fixture->initialized, 0 );
	ASSERT_GT( obj->fv_len, ( size_t )0 );
}

UTEST_F_TEARDOWN( mesh_test_fixture )
{
	ASSERT_EQ( utest_fixture->initialized, 0 );
	mesh_free( &utest_fixture->obj );
}

static int compare_face( const float *a, const float *b )
{
	int res = 1;
	res = res & ( a[ 0 ] == b[ 0 ] );
	res = res & ( a[ 1 ] == b[ 1 ] );
	res = res & ( a[ 2 ] == b[ 2 ] );

	res = res & ( a[ 3 ] == b[ 3 ] );
	res = res & ( a[ 4 ] == b[ 4 ] );

	res = res & ( a[ 5 ] == b[ 5 ] );
	res = res & ( a[ 6 ] == b[ 6 ] );
	res = res & ( a[ 7 ] == b[ 7 ] );
	return res;
}

UTEST_F( mesh_test_fixture, validate_f )
{
	struct mesh *obj = &utest_fixture->obj;

	float first_real[] = {
		-0.967716f, 11.993134f, -0.156907f,
		 0.4033f,    0.3064f,
		-0.3183f,   -0.6137f,   -0.7226f
	};

	float last_real[] = {
		0.536469f,  9.000515f, 1.657671f,
		0.205f,     0.3177f,
		0.4359f,   -0.5951f,   0.6751f
	};

	float *first_test = &obj->fv[ 0 ];
	EXPECT_TRUE( compare_face( first_real, first_test ) );

	float *last_test = &obj->fv[ obj->fv_len - obj->fv_nval ];
	EXPECT_TRUE( compare_face( last_real, last_test ) );
}

UTEST_F( mesh_test_fixture, validate_v )
{
	struct mesh *obj = &utest_fixture->obj;

	float *v = &obj->vp[ 0 ];

	EXPECT_EQ( v[ 0 ], -0.967716f );
	EXPECT_EQ( v[ 1 ], 11.993134f );
	EXPECT_EQ( v[ 2 ], -0.156907f );

	v = &obj->vp[ obj->vp_len - obj->vp_nval ];

	EXPECT_EQ( v[ 0 ], -0.026541f );
	EXPECT_EQ( v[ 1 ],  8.850442f );
	EXPECT_EQ( v[ 2 ],  1.286151f );
}

UTEST_F( mesh_test_fixture, validate_vt )
{
	struct mesh *obj = &utest_fixture->obj;

	float *v = &obj->vt[ 0 ];

	EXPECT_EQ( v[ 0 ], 0.4033f );
	EXPECT_EQ( v[ 1 ], 0.3064f );

	v = &obj->vt[ obj->vt_len - obj->vt_nval ];

	EXPECT_EQ( v[ 0 ], 0.1814f );
	EXPECT_EQ( v[ 1 ], 0.3465f );
}

UTEST_F( mesh_test_fixture, validate_vn )
{
	struct mesh *obj = &utest_fixture->obj;

	float *v = &obj->vn[ 0 ];

	EXPECT_EQ( v[ 0 ], -0.3183f );
	EXPECT_EQ( v[ 1 ], -0.6137f );
	EXPECT_EQ( v[ 2 ], -0.7226f );

	v = &obj->vn[ obj->vn_len - obj->vn_nval ];

	EXPECT_EQ( v[ 0 ], -0.0081f );
	EXPECT_EQ( v[ 1 ], -0.9930f );
	EXPECT_EQ( v[ 2 ],  0.1175f );
}

UTEST_F( mesh_test_fixture, validate_extent )
{
	struct mesh *obj = &utest_fixture->obj;

	EXPECT_TRUE( flteq( obj->dia, 17.460607338f, 0.000000001f ) );

	EXPECT_TRUE( flteq( obj->center.x, 0.00865102f, 0.00000001f ) );
	EXPECT_TRUE( flteq( obj->center.y, 6.98831547f, 0.00000001f ) );
	EXPECT_TRUE( flteq( obj->center.z, 0.8941009f , 0.0000001f  ) );

	EXPECT_TRUE( flteq( obj->min.x, -4.32404613f, 0.00000001f ) );
	EXPECT_TRUE( flteq( obj->min.y, 0.025872f   , 0.000001f   ) );
	EXPECT_TRUE( flteq( obj->min.z, -2.1009481f , 0.0000001f  ) );

	EXPECT_TRUE( flteq( obj->max.x, 4.34134817f , 0.00000001f ) );
	EXPECT_TRUE( flteq( obj->max.y, 13.95075893f, 0.00000001f ) );
	EXPECT_TRUE( flteq( obj->max.z, 3.8891499f  , 0.0000001f  ) );
}

UTEST_F( mesh_test_fixture, validate_properties )
{
	struct mesh *obj = &utest_fixture->obj;

	// values calculated before hand
	EXPECT_EQ( obj->stride, ( size_t )32 );
	EXPECT_EQ( obj->fv_len, ( size_t )14952 );
	EXPECT_EQ( obj->fv_nbytes, ( size_t )59808 );
}

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
