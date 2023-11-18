#include <utest.h>
#include <data/vector.h>

UTEST( vector, init )
{
	int *v = NULL;

	vector_init( v, 0 );
	ASSERT_TRUE( v );

	EXPECT_EQ( vector_size( v ), ( size_t ) 0 );
	EXPECT_EQ( vector_capacity( v ), ( size_t ) 0 );

	vector_reserve( v, 10 );
	EXPECT_EQ( vector_capacity( v ), ( size_t ) 10 );

	vector_resize( v, 10 );
	EXPECT_EQ( vector_size( v ), ( size_t ) 10 );

	vector_shrink_to_fit( v );

	vector_free( v );
	ASSERT_FALSE( v );
}

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
