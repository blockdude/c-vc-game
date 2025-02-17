#ifndef CORE_INTERNAL_H
#define CORE_INTERNAL_H

#include "input.h"
#include <util/types.h>

struct core
{
	unsigned int		flags;

	struct
	{
		bool			initialized;
	} timer;

	struct
	{
		bool            initialized;
	} audio;

	struct
	{
		bool         	initialized;
		unsigned int	id;
		unsigned int 	flags;
		const char * 	title;
		float        	aspect;
		unsigned int 	width;
		unsigned int 	height;
	} window;

	struct
	{
		bool         	initialized;
		struct keystate k_state[ K_COUNT ];
		struct keystate m_state[ B_COUNT ];
		bool         	m_moved;
		struct vec2     m_wheel;
		struct vec2     m_pos_rel;
		struct vec2     m_pos_global;
		struct vec2     m_pos_delta;
	} input;
};

extern struct core core;

#endif
