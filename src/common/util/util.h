#ifndef UTIL_H
#define UTIL_H

#ifndef BITFLAG
#define BITFLAG( v ) ( 1 << ( v ) )
#endif

#ifndef HASFLAG
#define HASFLAG( f, v ) ( ( ( f ) & ( v ) ) == ( v ) )
#endif

#ifndef ANYFLAG
#define ANYFLAG( f, v ) ( ( ( f ) & ( v ) ) >  ( 0 ) )
#endif

#endif
