#include <stdio.h>
#include <stdlib.h>

int main( void )
{
    /* testing */
    int dim_x = 62;
    int dim_y = 43;
    int dim_z = 91;

    int real_x = 19;
    int real_y = 20;
    int real_z = 48;
    int real_i = ( real_z * dim_x * dim_y ) + ( real_y * dim_x ) + real_x;

    union
    {
        int c[ dim_z * dim_y * dim_x ];
        int m[ dim_z ][ dim_y ][ dim_x ];
    } a;

    {
        int x = real_x;
        int y = real_y;
        int z = real_z;
        int i = ( z * dim_x * dim_y ) + ( y * dim_x ) + x;
        //int i = ((z * dim_z) + y) * dim_y + x;

        printf( "-------------\n" );
        printf( "given zyx:     %d,%d,%d\n", z, y, x );
        printf( "i:             %d\n", i );
        printf( "expected i:    %d\n", real_i );
        printf( "-------------\n" );
    }
    {
        int i = real_i;

        // N(ABC) -> N(A) x N(BC)
        int z = i / ( dim_x * dim_y ); // z in N(A)
        int w = i % ( dim_x * dim_y ); // w in N(BC)

        // below might be faster idk idc... yet
        //int w = i - z * dim_x * dim_y;

        // N(BC) -> N(B) x N(C)
        int y = w / dim_x; // y in N(B)
        int x = w % dim_x; // x in N(C)

        printf( "-------------\n" );
        printf( "given i:       %d\n", i );
        printf( "zyx:           %d,%d,%d\n", z, y, x );
        printf( "expected zyx:  %d,%d,%d\n", real_z, real_y, real_x );
    }
}
