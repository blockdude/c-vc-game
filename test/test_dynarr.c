#include "utest.h"
#include <util/dynarr.h>

/*
 * Testing dynarr_init and dynarr_free. Should assign our dynarr with an address
 * to the new dynarr and set the capacity then free it and assign our dynarr to NULL.
 */
UTEST( dynarr, init_free )
{
	int *v = NULL;

	EXPECT_EQ( dynarr_capacity( v ), ( size_t ) 0 );
	EXPECT_EQ( dynarr_size( v ), ( size_t ) 0 );

	dynarr_init( v, 10 );
	ASSERT_TRUE( v );

	EXPECT_EQ( dynarr_capacity( v ), ( size_t ) 10 );
	EXPECT_EQ( dynarr_size( v ), ( size_t ) 0 );

	dynarr_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing dynarr_reserve. Should initialize our dynarr if it is not initialized
 * then set its capacity.
 */
UTEST( dynarr, reserve )
{
	int *v = NULL;

	dynarr_reserve( v, 10 );
	ASSERT_TRUE( v );
	EXPECT_EQ( dynarr_capacity( v ), ( size_t ) 10 );

	dynarr_reserve( v, 5 );
	EXPECT_EQ( dynarr_capacity( v ), ( size_t ) 10 );

	dynarr_reserve( v, 20 );
	EXPECT_EQ( dynarr_capacity( v ), ( size_t ) 20 );

	dynarr_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing dynarr_resize. Should initialize our dynarr if it is not initialized
 * then set its size and initialize new elements to zero.
 */
UTEST( dynarr, resize )
{
	int *v = NULL;

	dynarr_resize( v, 5 );
	ASSERT_TRUE( v );
	EXPECT_EQ( dynarr_size( v ), ( size_t ) 5 );
	EXPECT_EQ( dynarr_capacity( v ), ( size_t ) 5 );

	// make sure elements are initialized to zero and assign them to one
	for ( int i = 0; i < 5; i++ )
	{
		EXPECT_EQ( v[ i ], 0 );
		v[ i ] = 1;
	}

	dynarr_resize( v, 10 );
	EXPECT_EQ( dynarr_size( v ), ( size_t ) 10 );
	EXPECT_EQ( dynarr_capacity( v ), ( size_t ) 10 );

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

	dynarr_resize( v, 5 );
	EXPECT_EQ( dynarr_size( v ), ( size_t ) 5 );
	EXPECT_EQ( dynarr_capacity( v ), ( size_t ) 10 );

	// make sure previous values are retained
	for ( int i = 0; i < 5; i++ )
	{
		EXPECT_EQ( v[ i ], 1 );
	}

	dynarr_free( v );
	ASSERT_FALSE( v );
}

/*
 * Test dynarr_push_back. Should initialize our dynarr if it is not already,
 * then insert the value to the back of the array. We should also see the dynarr
 * grow as needed.
 */
UTEST( dynarr, push_back )
{
	int *v = NULL;

	EXPECT_EQ( dynarr_capacity( v ), ( size_t ) 0 );
	EXPECT_EQ( dynarr_size( v ), ( size_t ) 0 );

	dynarr_push_back( v, 10 );

	ASSERT_TRUE( v );
	EXPECT_EQ( dynarr_capacity( v ), ( size_t ) 1 );
	EXPECT_EQ( dynarr_size( v ), ( size_t ) 1 );

	dynarr_push_back( v, 15 );

	EXPECT_EQ( dynarr_capacity( v ), ( size_t ) 2 );
	EXPECT_EQ( dynarr_size( v ), ( size_t ) 2 );

	dynarr_push_back( v, 20 );

	EXPECT_EQ( dynarr_capacity( v ), ( size_t ) 4 );
	EXPECT_EQ( dynarr_size( v ), ( size_t ) 3 );

	dynarr_push_back( v, 25 );

	EXPECT_EQ( dynarr_capacity( v ), ( size_t ) 4 );
	EXPECT_EQ( dynarr_size( v ), ( size_t ) 4 );

	dynarr_push_back( v, 30 );

	EXPECT_EQ( dynarr_capacity( v ), ( size_t ) 7 );
	EXPECT_EQ( dynarr_size( v ), ( size_t ) 5 );

	EXPECT_EQ( v[ 0 ], 10 );
	EXPECT_EQ( v[ 1 ], 15 );
	EXPECT_EQ( v[ 2 ], 20 );
	EXPECT_EQ( v[ 3 ], 25 );
	EXPECT_EQ( v[ 4 ], 30 );

	dynarr_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing dynarr_pop_back. Should simply reduce the size by one for each call.
 */
UTEST( dynarr, pop_back )
{
	int *v = NULL;

	dynarr_push_back( v, 10 );
	dynarr_push_back( v, 15 );
	dynarr_push_back( v, 20 );
	dynarr_push_back( v, 25 );
	dynarr_push_back( v, 30 );

	EXPECT_EQ( dynarr_size( v ), ( size_t ) 5 );

	dynarr_pop_back( v );
	dynarr_pop_back( v );
	dynarr_pop_back( v );

	EXPECT_EQ( dynarr_size( v ), ( size_t ) 2 );

	dynarr_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing dynarr_pop_back. Should simply set the size to zero.
 */
UTEST( dynarr, clear )
{
	int *v = NULL;

	dynarr_push_back( v, 10 );
	dynarr_push_back( v, 15 );
	dynarr_push_back( v, 20 );
	dynarr_push_back( v, 25 );
	dynarr_push_back( v, 30 );

	EXPECT_EQ( dynarr_size( v ), ( size_t ) 5 );

	dynarr_clear( v );

	EXPECT_EQ( dynarr_size( v ), ( size_t ) 0 );

	dynarr_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing dynarr_insert. Should be able to insert an element into the dynarr
 * within the size of the dynarr ( inclusive ) and move upper elements up one
 * index if needed.
 */
UTEST( dynarr, insert )
{
	int *v = NULL;

	dynarr_push_back( v, 10 );
	dynarr_push_back( v, 15 );
	dynarr_push_back( v, 20 );
	dynarr_push_back( v, 25 );
	dynarr_push_back( v, 30 );

	EXPECT_EQ( dynarr_size( v ), ( size_t ) 5 );

	dynarr_insert( v, 3, 22 );

	EXPECT_EQ( dynarr_size( v ), ( size_t ) 6 );

	EXPECT_EQ( v[ 0 ], 10 );
	EXPECT_EQ( v[ 1 ], 15 );
	EXPECT_EQ( v[ 2 ], 20 );
	EXPECT_EQ( v[ 3 ], 22 );
	EXPECT_EQ( v[ 4 ], 25 );
	EXPECT_EQ( v[ 5 ], 30 );

	dynarr_insert( v, 6, 35 );

	EXPECT_EQ( dynarr_size( v ), ( size_t ) 7 );

	EXPECT_EQ( v[ 0 ], 10 );
	EXPECT_EQ( v[ 1 ], 15 );
	EXPECT_EQ( v[ 2 ], 20 );
	EXPECT_EQ( v[ 3 ], 22 );
	EXPECT_EQ( v[ 4 ], 25 );
	EXPECT_EQ( v[ 5 ], 30 );
	EXPECT_EQ( v[ 6 ], 35 );

	dynarr_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing dynarr_remove. Should be able to remove an element into the dynarr
 * within the size of the dynarr ( exclusive ) and move upper elements down one
 * index if needed.
 */
UTEST( dynarr, remove )
{
	int *v = NULL;

	dynarr_push_back( v, 10 );
	dynarr_push_back( v, 15 );
	dynarr_push_back( v, 20 );
	dynarr_push_back( v, 25 );
	dynarr_push_back( v, 30 );
	dynarr_push_back( v, 35 );
	dynarr_push_back( v, 40 );

	EXPECT_EQ( dynarr_size( v ), ( size_t ) 7 );

	dynarr_remove( v, 0 );

	EXPECT_EQ( dynarr_size( v ), ( size_t ) 6 );

	EXPECT_EQ( v[ 0 ], 15 );
	EXPECT_EQ( v[ 1 ], 20 );
	EXPECT_EQ( v[ 2 ], 25 );
	EXPECT_EQ( v[ 3 ], 30 );
	EXPECT_EQ( v[ 4 ], 35 );
	EXPECT_EQ( v[ 5 ], 40 );

	dynarr_remove( v, 2 );

	EXPECT_EQ( dynarr_size( v ), ( size_t ) 5 );

	EXPECT_EQ( v[ 0 ], 15 );
	EXPECT_EQ( v[ 1 ], 20 );
	EXPECT_EQ( v[ 2 ], 30 );
	EXPECT_EQ( v[ 3 ], 35 );
	EXPECT_EQ( v[ 4 ], 40 );

	dynarr_remove( v, 4 );

	EXPECT_EQ( dynarr_size( v ), ( size_t ) 4 );

	EXPECT_EQ( v[ 0 ], 15 );
	EXPECT_EQ( v[ 1 ], 20 );
	EXPECT_EQ( v[ 2 ], 30 );
	EXPECT_EQ( v[ 3 ], 35 );

	dynarr_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing dynarr_condense. Should reallocate memory to make the capacity
 * equal size of the dynarr.
 */
UTEST( dynarr, condense )
{
	int *v = NULL;

	dynarr_reserve( v, 100 );
	dynarr_push_back( v, 10 );
	dynarr_push_back( v, 15 );
	dynarr_push_back( v, 20 );
	dynarr_push_back( v, 25 );
	dynarr_push_back( v, 30 );
	dynarr_push_back( v, 35 );
	dynarr_push_back( v, 40 );

	EXPECT_EQ( dynarr_capacity( v ), ( size_t ) 100 );
	EXPECT_EQ( dynarr_size( v ), ( size_t ) 7 );

	dynarr_condense( v );

	EXPECT_EQ( dynarr_capacity( v ), ( size_t ) 7 );
	EXPECT_EQ( dynarr_size( v ), ( size_t ) 7 );

	dynarr_free( v );
	ASSERT_FALSE( v );
}

struct data
{
	int a;
	float b;
	unsigned char c;
};

/*
 * Tests dynarr inserts with a struct type.
 */
UTEST( dynarr, complex_insert_A )
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

	dynarr_insert( v, 0, d );
	dynarr_insert( v, 0, c );
	dynarr_insert( v, 0, b );
	dynarr_insert( v, 0, a );

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

	dynarr_free( v );
	ASSERT_FALSE( v );
}

/*
 * Tests dynarr inserts with a struct pointer type.
 */
UTEST( dynarr, complex_insert_B )
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

	dynarr_insert( v, 0, &d );
	dynarr_insert( v, 0, &c );
	dynarr_insert( v, 0, &b );
	dynarr_insert( v, 0, &a );

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

	dynarr_free( v );
	ASSERT_FALSE( v );
}

/*
 * Test multiple references to the same dynarr.
 */
UTEST( dynarr, multi_ref )
{
	int *v = NULL;
	int **vptr = &v;

	dynarr_init( *vptr, 0 );

	ASSERT_TRUE( v );
	ASSERT_TRUE( *vptr );

	dynarr_push_back( v, 10 );
	dynarr_push_back( *vptr, 15 );
	dynarr_push_back( v, 10 );

	EXPECT_EQ( v[ 0 ], 10 );
	EXPECT_EQ( v[ 1 ], 15 );
	EXPECT_EQ( ( *vptr )[ 2 ], 10 );

	dynarr_free( v );
	ASSERT_FALSE( v );
	ASSERT_FALSE( *vptr );

}

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
