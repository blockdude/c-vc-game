#ifndef CORE_INTERNAL_H
#define CORE_INTERNAL_H

#include "input.h"

#include <stdbool.h>
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
		unsigned int 	flags;
		const char * 	title;
		float        	aspect;
		unsigned int 	width;
		unsigned int 	height;
	} window;

	struct
	{
		bool         	initialized;
		int          	k_state[ K_COUNT ];
		int          	m_state[ B_COUNT ];
		bool         	m_moved;
		vec2_t       	m_wheel;
		vec2_t       	m_pos_rel;
		vec2_t       	m_pos_global;
		vec2_t       	m_pos_delta;
	} input;
};

extern struct core core;

#endif
