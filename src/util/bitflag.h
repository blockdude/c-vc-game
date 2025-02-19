#ifndef VCP_BITFLAG_H
#define VCP_BITFLAG_H

#define BITFLAG( v ) ( 1 << ( v ) )
#define HASFLAG( f, v ) ( ( ( f ) & ( v ) ) == ( v ) )
#define ANYFLAG( f, v ) ( ( ( f ) & ( v ) ) >  ( 0 ) )

#endif