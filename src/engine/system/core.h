#ifndef CORE_H
#define CORE_H

enum core_status
{
	CORE_SUCCESS = 0,
	CORE_ERROR   = 1
};

#ifdef __cplusplus
extern "C" {
#endif

int core_init( void );
int core_free( void );

#ifdef __cplusplus
}
#endif

#endif
