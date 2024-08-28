#ifndef CORE_H
#define CORE_H

#include "input.h"
#include <util/types.h>

#include <SDL3/SDL.h>

/*
 * Definition for core data structure to store the state of the
 * program. I like this better than having mulitple global
 * variables floating around in random places.
 */

struct core
{
	struct
	{
		SDL_Window *window;
		SDL_GLContext glcontext;
	} platform;

	struct
	{
		// is the window running
		bool initialized;
		bool relative_mouse;

		// keeps track of width, height and aspect ratio
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
};

extern struct core core;

#endif
