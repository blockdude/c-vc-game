#ifndef CORE_H
#define CORE_H

enum core_status
{
	CORE_SUCCESS = 0,
	CORE_ERROR   = 1
};

enum core_flags
{
	WINDOW = 0x01,

	/*
	 * Input events are limited if the window is not also initialized.
	 */
	INPUT  = 0x02,

	AUDIO  = 0x04,
	TIMER  = 0x08
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
