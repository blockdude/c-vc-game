#include <utest.h>
#include <gfx/obj3d.h>

UTEST( obj3d, load_obj_file )
{
	struct obj3d obj;
	int res = obj3d_load( &obj, "../res/objects/rayman.obj" );
	ASSERT_EQ( res, 0 );

	struct vec3 v;

	v = obj.v[ 0 ];

	EXPECT_EQ( v.x, -0.967716f );
	EXPECT_EQ( v.y, 11.993134f );
	EXPECT_EQ( v.z, -0.156907f );

	v = obj.v[ obj.v_len - 1 ];

	EXPECT_EQ( v.x, -0.026541f );
	EXPECT_EQ( v.y, 8.850442f );
	EXPECT_EQ( v.z, 1.286151f );

	obj3d_free( &obj );
}

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
