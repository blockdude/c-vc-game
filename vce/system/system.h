#ifndef SYSTEM_H
#define SYSTEM_H

#define SYSTEM_SUCCESS 0
#define SYSTEM_ERROR -1

#ifdef __cplusplus
extern "C" {
#endif

int system_init( void );
int system_free( void );

#ifdef __cplusplus
}
#endif

#endif
