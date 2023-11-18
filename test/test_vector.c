#include <utest.h>
#include <data/vector.h>

/*
 * Testing vector_init and vector_free. Should assign our vector with an address
 * to the new vector and set the capacity then free it and assign our vector to NULL.
 */
UTEST( vector, init_free )
{
	int *v = NULL;

	EXPECT_EQ( vector_capacity( v ), ( size_t ) 0 );
	EXPECT_EQ( vector_size( v ), ( size_t ) 0 );

	vector_init( v, 10 );
	ASSERT_TRUE( v );

	EXPECT_EQ( vector_capacity( v ), ( size_t ) 10 );
	EXPECT_EQ( vector_size( v ), ( size_t ) 0 );

	vector_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing vector_reserve. Should initialize our vector if it is not initialized
 * then set its capacity.
 */
UTEST( vector, reserve )
{
	int *v = NULL;

	vector_reserve( v, 10 );
	ASSERT_TRUE( v );
	EXPECT_EQ( vector_capacity( v ), ( size_t ) 10 );

	vector_reserve( v, 5 );
	EXPECT_EQ( vector_capacity( v ), ( size_t ) 10 );

	vector_reserve( v, 20 );
	EXPECT_EQ( vector_capacity( v ), ( size_t ) 20 );

	vector_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing vector_resize. Should initialize our vector if it is not initialized
 * then set its size and initialize new elements to zero.
 */
UTEST( vector, resize )
{
	int *v = NULL;

	vector_resize( v, 5 );
	ASSERT_TRUE( v );
	EXPECT_EQ( vector_size( v ), ( size_t ) 5 );
	EXPECT_EQ( vector_capacity( v ), ( size_t ) 5 );

	// make sure elements are initialized to zero and assign them to one
	for ( int i = 0; i < 5; i++ )
	{
		EXPECT_EQ( v[ i ], 0 );
		v[ i ] = 1;
	}

	vector_resize( v, 10 );
	EXPECT_EQ( vector_size( v ), ( size_t ) 10 );
	EXPECT_EQ( vector_capacity( v ), ( size_t ) 10 );

	// make sure previous values are retained
	for ( int i = 0; i < 5; i++ )
	{
		EXPECT_EQ( v[ i ], 1 );
	}

	// make sure new elements are zero
	for ( int i = 5; i < 10; i++ )
	{
		EXPECT_EQ( v[ i ], 0 );
	}

	vector_resize( v, 5 );
	EXPECT_EQ( vector_size( v ), ( size_t ) 5 );
	EXPECT_EQ( vector_capacity( v ), ( size_t ) 10 );

	// make sure previous values are retained
	for ( int i = 0; i < 5; i++ )
	{
		EXPECT_EQ( v[ i ], 1 );
	}

	vector_free( v );
	ASSERT_FALSE( v );
}

/*
 * Test vector_push_back. Should initialize our vector if it is not already,
 * then insert the value to the back of the array. We should also see the vector
 * grow as needed.
 */
UTEST( vector, push_back )
{
	int *v = NULL;

	EXPECT_EQ( vector_capacity( v ), ( size_t ) 0 );
	EXPECT_EQ( vector_size( v ), ( size_t ) 0 );

	vector_push_back( v, 10 );

	ASSERT_TRUE( v );
	EXPECT_EQ( vector_capacity( v ), ( size_t ) 1 );
	EXPECT_EQ( vector_size( v ), ( size_t ) 1 );

	vector_push_back( v, 15 );

	EXPECT_EQ( vector_capacity( v ), ( size_t ) 2 );
	EXPECT_EQ( vector_size( v ), ( size_t ) 2 );

	vector_push_back( v, 20 );

	EXPECT_EQ( vector_capacity( v ), ( size_t ) 4 );
	EXPECT_EQ( vector_size( v ), ( size_t ) 3 );

	vector_push_back( v, 25 );

	EXPECT_EQ( vector_capacity( v ), ( size_t ) 4 );
	EXPECT_EQ( vector_size( v ), ( size_t ) 4 );

	vector_push_back( v, 30 );

	EXPECT_EQ( vector_capacity( v ), ( size_t ) 7 );
	EXPECT_EQ( vector_size( v ), ( size_t ) 5 );

	EXPECT_EQ( v[ 0 ], 10 );
	EXPECT_EQ( v[ 1 ], 15 );
	EXPECT_EQ( v[ 2 ], 20 );
	EXPECT_EQ( v[ 3 ], 25 );
	EXPECT_EQ( v[ 4 ], 30 );

	vector_free( v );
	ASSERT_FALSE( v );
}

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
