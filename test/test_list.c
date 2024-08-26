#include "utest.h"
#include <util/list.h>

/*
 * Testing list_init and list_free. Should assign our list with an address
 * to the new list and set the capacity then free it and assign our list to NULL.
 */
UTEST( list, init_free )
{
	int *v = NULL;

	EXPECT_EQ( list_capacity( v ), ( size_t ) 0 );
	EXPECT_EQ( list_size( v ), ( size_t ) 0 );

	list_init( v, 10 );
	ASSERT_TRUE( v );

	EXPECT_EQ( list_capacity( v ), ( size_t ) 10 );
	EXPECT_EQ( list_size( v ), ( size_t ) 0 );

	list_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing list_reserve. Should initialize our list if it is not initialized
 * then set its capacity.
 */
UTEST( list, reserve )
{
	int *v = NULL;

	list_reserve( v, 10 );
	ASSERT_TRUE( v );
	EXPECT_EQ( list_capacity( v ), ( size_t ) 10 );

	list_reserve( v, 5 );
	EXPECT_EQ( list_capacity( v ), ( size_t ) 10 );

	list_reserve( v, 20 );
	EXPECT_EQ( list_capacity( v ), ( size_t ) 20 );

	list_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing list_resize. Should initialize our list if it is not initialized
 * then set its size and initialize new elements to zero.
 */
UTEST( list, resize )
{
	int *v = NULL;

	list_resize( v, 5 );
	ASSERT_TRUE( v );
	EXPECT_EQ( list_size( v ), ( size_t ) 5 );
	EXPECT_EQ( list_capacity( v ), ( size_t ) 5 );

	// make sure elements are initialized to zero and assign them to one
	for ( int i = 0; i < 5; i++ )
	{
		EXPECT_EQ( v[ i ], 0 );
		v[ i ] = 1;
	}

	list_resize( v, 10 );
	EXPECT_EQ( list_size( v ), ( size_t ) 10 );
	EXPECT_EQ( list_capacity( v ), ( size_t ) 10 );

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

	list_resize( v, 5 );
	EXPECT_EQ( list_size( v ), ( size_t ) 5 );
	EXPECT_EQ( list_capacity( v ), ( size_t ) 10 );

	// make sure previous values are retained
	for ( int i = 0; i < 5; i++ )
	{
		EXPECT_EQ( v[ i ], 1 );
	}

	list_free( v );
	ASSERT_FALSE( v );
}

/*
 * Test list_push_back. Should initialize our list if it is not already,
 * then insert the value to the back of the array. We should also see the list
 * grow as needed.
 */
UTEST( list, push_back )
{
	int *v = NULL;

	EXPECT_EQ( list_capacity( v ), ( size_t ) 0 );
	EXPECT_EQ( list_size( v ), ( size_t ) 0 );

	list_push_back( v, 10 );

	ASSERT_TRUE( v );
	EXPECT_EQ( list_capacity( v ), ( size_t ) 1 );
	EXPECT_EQ( list_size( v ), ( size_t ) 1 );

	list_push_back( v, 15 );

	EXPECT_EQ( list_capacity( v ), ( size_t ) 2 );
	EXPECT_EQ( list_size( v ), ( size_t ) 2 );

	list_push_back( v, 20 );

	EXPECT_EQ( list_capacity( v ), ( size_t ) 4 );
	EXPECT_EQ( list_size( v ), ( size_t ) 3 );

	list_push_back( v, 25 );

	EXPECT_EQ( list_capacity( v ), ( size_t ) 4 );
	EXPECT_EQ( list_size( v ), ( size_t ) 4 );

	list_push_back( v, 30 );

	EXPECT_EQ( list_capacity( v ), ( size_t ) 7 );
	EXPECT_EQ( list_size( v ), ( size_t ) 5 );

	EXPECT_EQ( v[ 0 ], 10 );
	EXPECT_EQ( v[ 1 ], 15 );
	EXPECT_EQ( v[ 2 ], 20 );
	EXPECT_EQ( v[ 3 ], 25 );
	EXPECT_EQ( v[ 4 ], 30 );

	list_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing list_pop_back. Should simply reduce the size by one for each call.
 */
UTEST( list, pop_back )
{
	int *v = NULL;

	list_push_back( v, 10 );
	list_push_back( v, 15 );
	list_push_back( v, 20 );
	list_push_back( v, 25 );
	list_push_back( v, 30 );

	EXPECT_EQ( list_size( v ), ( size_t ) 5 );

	list_pop_back( v );
	list_pop_back( v );
	list_pop_back( v );

	EXPECT_EQ( list_size( v ), ( size_t ) 2 );

	list_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing list_pop_back. Should simply set the size to zero.
 */
UTEST( list, clear )
{
	int *v = NULL;

	list_push_back( v, 10 );
	list_push_back( v, 15 );
	list_push_back( v, 20 );
	list_push_back( v, 25 );
	list_push_back( v, 30 );

	EXPECT_EQ( list_size( v ), ( size_t ) 5 );

	list_clear( v );

	EXPECT_EQ( list_size( v ), ( size_t ) 0 );

	list_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing list_insert. Should be able to insert an element into the list
 * within the size of the list ( inclusive ) and move upper elements up one
 * index if needed.
 */
UTEST( list, insert )
{
	int *v = NULL;

	list_push_back( v, 10 );
	list_push_back( v, 15 );
	list_push_back( v, 20 );
	list_push_back( v, 25 );
	list_push_back( v, 30 );

	EXPECT_EQ( list_size( v ), ( size_t ) 5 );

	list_insert( v, 3, 22 );

	EXPECT_EQ( list_size( v ), ( size_t ) 6 );

	EXPECT_EQ( v[ 0 ], 10 );
	EXPECT_EQ( v[ 1 ], 15 );
	EXPECT_EQ( v[ 2 ], 20 );
	EXPECT_EQ( v[ 3 ], 22 );
	EXPECT_EQ( v[ 4 ], 25 );
	EXPECT_EQ( v[ 5 ], 30 );

	list_insert( v, 6, 35 );

	EXPECT_EQ( list_size( v ), ( size_t ) 7 );

	EXPECT_EQ( v[ 0 ], 10 );
	EXPECT_EQ( v[ 1 ], 15 );
	EXPECT_EQ( v[ 2 ], 20 );
	EXPECT_EQ( v[ 3 ], 22 );
	EXPECT_EQ( v[ 4 ], 25 );
	EXPECT_EQ( v[ 5 ], 30 );
	EXPECT_EQ( v[ 6 ], 35 );

	list_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing list_remove. Should be able to remove an element into the list
 * within the size of the list ( exclusive ) and move upper elements down one
 * index if needed.
 */
UTEST( list, remove )
{
	int *v = NULL;

	list_push_back( v, 10 );
	list_push_back( v, 15 );
	list_push_back( v, 20 );
	list_push_back( v, 25 );
	list_push_back( v, 30 );
	list_push_back( v, 35 );
	list_push_back( v, 40 );

	EXPECT_EQ( list_size( v ), ( size_t ) 7 );

	list_remove( v, 0 );

	EXPECT_EQ( list_size( v ), ( size_t ) 6 );

	EXPECT_EQ( v[ 0 ], 15 );
	EXPECT_EQ( v[ 1 ], 20 );
	EXPECT_EQ( v[ 2 ], 25 );
	EXPECT_EQ( v[ 3 ], 30 );
	EXPECT_EQ( v[ 4 ], 35 );
	EXPECT_EQ( v[ 5 ], 40 );

	list_remove( v, 2 );

	EXPECT_EQ( list_size( v ), ( size_t ) 5 );

	EXPECT_EQ( v[ 0 ], 15 );
	EXPECT_EQ( v[ 1 ], 20 );
	EXPECT_EQ( v[ 2 ], 30 );
	EXPECT_EQ( v[ 3 ], 35 );
	EXPECT_EQ( v[ 4 ], 40 );

	list_remove( v, 4 );

	EXPECT_EQ( list_size( v ), ( size_t ) 4 );

	EXPECT_EQ( v[ 0 ], 15 );
	EXPECT_EQ( v[ 1 ], 20 );
	EXPECT_EQ( v[ 2 ], 30 );
	EXPECT_EQ( v[ 3 ], 35 );

	list_free( v );
	ASSERT_FALSE( v );
}

/*
 * Testing list_condense. Should reallocate memory to make the capacity
 * equal size of the list.
 */
UTEST( list, condense )
{
	int *v = NULL;

	list_reserve( v, 100 );
	list_push_back( v, 10 );
	list_push_back( v, 15 );
	list_push_back( v, 20 );
	list_push_back( v, 25 );
	list_push_back( v, 30 );
	list_push_back( v, 35 );
	list_push_back( v, 40 );

	EXPECT_EQ( list_capacity( v ), ( size_t ) 100 );
	EXPECT_EQ( list_size( v ), ( size_t ) 7 );

	list_condense( v );

	EXPECT_EQ( list_capacity( v ), ( size_t ) 7 );
	EXPECT_EQ( list_size( v ), ( size_t ) 7 );

	list_free( v );
	ASSERT_FALSE( v );
}

struct data
{
	int a;
	float b;
	unsigned char c;
};

/*
 * Tests list inserts with a struct type.
 */
UTEST( list, complex_insert_A )
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

	list_insert( v, 0, d );
	list_insert( v, 0, c );
	list_insert( v, 0, b );
	list_insert( v, 0, a );

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

	list_free( v );
	ASSERT_FALSE( v );
}

/*
 * Tests list inserts with a struct pointer type.
 */
UTEST( list, complex_insert_B )
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

	list_insert( v, 0, &d );
	list_insert( v, 0, &c );
	list_insert( v, 0, &b );
	list_insert( v, 0, &a );

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

	list_free( v );
	ASSERT_FALSE( v );
}

/*
 * Test multiple references to the same list.
 */
UTEST( list, multi_ref )
{
	int *v = NULL;
	int **vptr = &v;

	list_init( *vptr, 0 );

	ASSERT_TRUE( v );
	ASSERT_TRUE( *vptr );

	list_push_back( v, 10 );
	list_push_back( *vptr, 15 );
	list_push_back( v, 10 );

	EXPECT_EQ( v[ 0 ], 10 );
	EXPECT_EQ( v[ 1 ], 15 );
	EXPECT_EQ( ( *vptr )[ 2 ], 10 );

	list_free( v );
	ASSERT_FALSE( v );
	ASSERT_FALSE( *vptr );
}

/*
 * Test multiple references to the same list.
 */
UTEST( list, multi_ref_2 )
{
	int *v0 = NULL;
	list_init( v0, 3 );
	int *v1 = v0;

	ASSERT_TRUE( v0 );
	ASSERT_TRUE( v1 );

	list_push_back( v0, 10 );
	list_push_back( v1, 15 );
	list_push_back( v0, 10 );

	EXPECT_EQ( v0[ 0 ], v1[ 0 ] );
	EXPECT_EQ( v0[ 1 ], v1[ 1 ] );
	EXPECT_EQ( v0[ 2 ], v1[ 2 ] );

	list_free( v0 );
	v1 = v0;

	ASSERT_FALSE( v0 );
	ASSERT_FALSE( v1 );
}

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
