#ifndef CORE_INTERNAL_H
#define CORE_INTERNAL_H

#include "input.h"
#include <util/types.h>
#include <util/app.h>

/*
 * Definition for core data structure to store the state of the
 * program. I like this better than having mulitple global
 * variables floating around in random places.
 */

struct core
{
	unsigned int flags;

	struct
	{
		const char *title;
		unsigned int flags;

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
		struct app state;
	} app;
};

extern struct core core;

#endif
