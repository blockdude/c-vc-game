#ifndef CORE_INTERNAL_H
#define CORE_INTERNAL_H

#include "../app.h"
#include "../input.h"

#include <util/types.h>

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
		bool     running;

		float    frame_delta;
		float    frame_target;
		float    frame_avg;
		int      frame_rate;
		uint64_t frame_count;

		float    tick_delta;
		float    tick_target;
		float    tick_avg;
		int      tick_rate;
		uint64_t tick_count;
	} timestep;

	struct
	{
		bool         initialized;
		unsigned int flags;
		const char * title;
		float        aspect;
		unsigned int w;
		unsigned int h;
	} window;

	struct
	{
		bool initialized;
		struct
		{
			int state[ KB_COUNT ];
		} keyboard;

		struct
		{
			int    state[ MB_COUNT ];
			bool   moved;
			vec2_t wheel;
			struct
			{
				vec2_t rel;
				vec2_t global;
				vec2_t delta;
			} pos;
		} mouse;
	} input;

	struct
	{
		struct app state;
	} app;
};

extern struct core core;

#endif
