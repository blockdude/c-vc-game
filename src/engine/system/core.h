#ifndef CORE_H
#define CORE_H

#include "input.h"
#include <util/types.h>

/*
 * Definition for core data structure to store the state of the
 * program. I like this better than having mulitple global
 * variables floating around in random places.
 */

struct core
{
	struct
	{
		const char *title;

		bool initialized;
		bool relative_mouse;

		unsigned int w;
		unsigned int h;
		float aspect;
	} window;

	struct
	{
		struct
		{
			int state[ KB_COUNT ];
		} keyboard;

		struct
		{
			int state[ MB_COUNT ];

			vec2_t wheel;

			struct
			{
				vec2_t rel;
				vec2_t global;
				vec2_t delta;
			} pos;

			bool moved;
		} mouse;
	} input;

	/*
	 * Keep track of the app state
	 */
	struct
	{
		int s;
	} app;
};

enum core_status
{
	CORE_SUCCESS = 0,
	CORE_ERROR   = 1
};

extern struct core core;

#ifdef __cplusplus
extern "C" {
#endif

int core_init( void );
int core_free( void );

#ifdef __cplusplus
}
#endif

#endif
