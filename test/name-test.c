#include <stdio.h>

const char *test( char *name )
{
	return name;
}

int main( void )
{
	int size = 10000000;
	char *s[ size ];
	for ( int i = 0; i < size; i++ )
	{
		s[ i ] = test( "this is a test" );
	}

	for ( int i = 0; i < size; i++ )
	{
		//printf( "%s\n", s[ i ] );
	}
	return 0;
}
