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

/*
 * Testing vector_pop_back. Should simply reduce the size by one for each call.
 */
UTEST( vector, pop_back )
{
	int *v = NULL;

	vector_push_back( v, 10 );
	vector_push_back( v, 15 );
	vector_push_back( v, 20 );
	vector_push_back( v, 25 );
	vector_push_back( v, 30 );

	EXPECT_EQ( vector_size( v ), ( size_t ) 5 );

	vector_pop_back( v );
	vector_pop_back( v );
	vector_pop_back( v );

	EXPECT_EQ( vector_size( v ), ( size_t ) 2 );

	vector_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing vector_pop_back. Should simply set the size to zero.
 */
UTEST( vector, clear )
{
	int *v = NULL;

	vector_push_back( v, 10 );
	vector_push_back( v, 15 );
	vector_push_back( v, 20 );
	vector_push_back( v, 25 );
	vector_push_back( v, 30 );

	EXPECT_EQ( vector_size( v ), ( size_t ) 5 );

	vector_clear( v );

	EXPECT_EQ( vector_size( v ), ( size_t ) 0 );

	vector_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing vector_insert. Should be able to insert an element into the vector
 * within the size of the vector ( inclusive ) and move upper elements up one
 * index if needed.
 */
UTEST( vector, insert )
{
	int *v = NULL;

	vector_push_back( v, 10 );
	vector_push_back( v, 15 );
	vector_push_back( v, 20 );
	vector_push_back( v, 25 );
	vector_push_back( v, 30 );

	EXPECT_EQ( vector_size( v ), ( size_t ) 5 );

	vector_insert( v, 3, 22 );

	EXPECT_EQ( vector_size( v ), ( size_t ) 6 );

	EXPECT_EQ( v[ 0 ], 10 );
	EXPECT_EQ( v[ 1 ], 15 );
	EXPECT_EQ( v[ 2 ], 20 );
	EXPECT_EQ( v[ 3 ], 22 );
	EXPECT_EQ( v[ 4 ], 25 );
	EXPECT_EQ( v[ 5 ], 30 );

	vector_insert( v, 6, 35 );

	EXPECT_EQ( vector_size( v ), ( size_t ) 7 );

	EXPECT_EQ( v[ 0 ], 10 );
	EXPECT_EQ( v[ 1 ], 15 );
	EXPECT_EQ( v[ 2 ], 20 );
	EXPECT_EQ( v[ 3 ], 22 );
	EXPECT_EQ( v[ 4 ], 25 );
	EXPECT_EQ( v[ 5 ], 30 );
	EXPECT_EQ( v[ 6 ], 35 );

	vector_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing vector_remove. Should be able to remove an element into the vector
 * within the size of the vector ( exclusive ) and move upper elements down one
 * index if needed.
 */
UTEST( vector, remove )
{
	int *v = NULL;

	vector_push_back( v, 10 );
	vector_push_back( v, 15 );
	vector_push_back( v, 20 );
	vector_push_back( v, 25 );
	vector_push_back( v, 30 );
	vector_push_back( v, 35 );
	vector_push_back( v, 40 );

	EXPECT_EQ( vector_size( v ), ( size_t ) 7 );

	vector_remove( v, 0 );

	EXPECT_EQ( vector_size( v ), ( size_t ) 6 );

	EXPECT_EQ( v[ 0 ], 15 );
	EXPECT_EQ( v[ 1 ], 20 );
	EXPECT_EQ( v[ 2 ], 25 );
	EXPECT_EQ( v[ 3 ], 30 );
	EXPECT_EQ( v[ 4 ], 35 );
	EXPECT_EQ( v[ 5 ], 40 );

	vector_remove( v, 2 );

	EXPECT_EQ( vector_size( v ), ( size_t ) 5 );

	EXPECT_EQ( v[ 0 ], 15 );
	EXPECT_EQ( v[ 1 ], 20 );
	EXPECT_EQ( v[ 2 ], 30 );
	EXPECT_EQ( v[ 3 ], 35 );
	EXPECT_EQ( v[ 4 ], 40 );

	vector_remove( v, 4 );

	EXPECT_EQ( vector_size( v ), ( size_t ) 4 );

	EXPECT_EQ( v[ 0 ], 15 );
	EXPECT_EQ( v[ 1 ], 20 );
	EXPECT_EQ( v[ 2 ], 30 );
	EXPECT_EQ( v[ 3 ], 35 );

	vector_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing vector_shrink_to_fit. Should reallocate memory to make the capacity
 * equal size of the vector.
 */
UTEST( vector, shrink_to_fit )
{
	int *v = NULL;

	vector_reserve( v, 100 );
	vector_push_back( v, 10 );
	vector_push_back( v, 15 );
	vector_push_back( v, 20 );
	vector_push_back( v, 25 );
	vector_push_back( v, 30 );
	vector_push_back( v, 35 );
	vector_push_back( v, 40 );

	EXPECT_EQ( vector_capacity( v ), ( size_t ) 100 );
	EXPECT_EQ( vector_size( v ), ( size_t ) 7 );

	vector_shrink_to_fit( v );

	EXPECT_EQ( vector_capacity( v ), ( size_t ) 7 );
	EXPECT_EQ( vector_size( v ), ( size_t ) 7 );

	vector_free( v );
	ASSERT_FALSE( v );
}

struct data
{
	int a;
	float b;
	unsigned char c;
};

/*
 * Tests vector inserts with a struct type.
 */
UTEST( vector, complex_insert_A )
{
	struct data a = {
		.a = 2,
		.b = 4.5f,
		.c = 255
	};

	struct data b = {
		.a = 3,
		.b = 2.233f,
		.c = 'a'
	};

	struct data c = {
		.a = 123,
		.b = 3.14159f,
		.c = 'k'
	};

	struct data d = {
		.a = 333,
		.b = 20.5f,
		.c = 'z'
	};

	struct data *v = NULL;

	vector_insert( v, 0, d );
	vector_insert( v, 0, c );
	vector_insert( v, 0, b );
	vector_insert( v, 0, a );

	EXPECT_EQ( v[ 0 ].a, 2 );
	EXPECT_EQ( v[ 0 ].b, 4.5f );
	EXPECT_EQ( v[ 0 ].c, 255 );

	EXPECT_EQ( v[ 1 ].a, 3 );
	EXPECT_EQ( v[ 1 ].b, 2.233f );
	EXPECT_EQ( v[ 1 ].c, 'a' );

	EXPECT_EQ( v[ 2 ].a, 123 );
	EXPECT_EQ( v[ 2 ].b, 3.14159f );
	EXPECT_EQ( v[ 2 ].c, 'k' );

	EXPECT_EQ( v[ 3 ].a, 333 );
	EXPECT_EQ( v[ 3 ].b, 20.5f );
	EXPECT_EQ( v[ 3 ].c, 'z' );

	vector_free( v );
	ASSERT_FALSE( v );
}

/*
 * Tests vector inserts with a struct pointer type.
 */
UTEST( vector, complex_insert_B )
{
	struct data a = {
		.a = 2,
		.b = 4.5f,
		.c = 255
	};

	struct data b = {
		.a = 3,
		.b = 2.233f,
		.c = 'a'
	};

	struct data c = {
		.a = 123,
		.b = 3.14159f,
		.c = 'k'
	};

	struct data d = {
		.a = 333,
		.b = 20.5f,
		.c = 'z'
	};

	struct data **v = NULL;

	vector_insert( v, 0, &d );
	vector_insert( v, 0, &c );
	vector_insert( v, 0, &b );
	vector_insert( v, 0, &a );

	EXPECT_EQ( v[ 0 ]->a, 2 );
	EXPECT_EQ( v[ 0 ]->b, 4.5f );
	EXPECT_EQ( v[ 0 ]->c, 255 );

	EXPECT_EQ( v[ 1 ]->a, 3 );
	EXPECT_EQ( v[ 1 ]->b, 2.233f );
	EXPECT_EQ( v[ 1 ]->c, 'a' );

	EXPECT_EQ( v[ 2 ]->a, 123 );
	EXPECT_EQ( v[ 2 ]->b, 3.14159f );
	EXPECT_EQ( v[ 2 ]->c, 'k' );

	EXPECT_EQ( v[ 3 ]->a, 333 );
	EXPECT_EQ( v[ 3 ]->b, 20.5f );
	EXPECT_EQ( v[ 3 ]->c, 'z' );

	v[ 0 ]->a = 1234;
	v[ 0 ]->b = 1.333;
	v[ 0 ]->c = 'w';

	EXPECT_EQ( a.a, 1234 );
	EXPECT_EQ( a.b, 1.333f );
	EXPECT_EQ( a.c, 'w' );

	vector_free( v );
	ASSERT_FALSE( v );
}

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
