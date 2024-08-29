#ifndef CORE_H
#define CORE_H

enum core_status
{
	CORE_SUCCESS = 0,
	CORE_ERROR   = 1
};

enum core_flags
{
	CORE_HEADLESS = 0x01,
	CORE_NO_AUDIO = 0x02
};

#ifdef __cplusplus
extern "C" {
#endif

int core_init( unsigned int flags );
int core_free( void );

#ifdef __cplusplus
}
#endif

#endif
