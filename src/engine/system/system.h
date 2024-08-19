#ifndef SYSTEM_H
#define SYSTEM_H

enum system_status
{
    SYSTEM_ERROR   = -1,
    SYSTEM_SUCCESS =  0
};

#ifdef __cplusplus
extern "C" {
#endif

int system_init( void );
int system_free( void );

#ifdef __cplusplus
}
#endif

#endif
