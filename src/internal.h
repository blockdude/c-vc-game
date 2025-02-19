#ifndef VCP_INTERNAL_GLOBAL_STATE_H
#define VCP_INTERNAL_GLOBAL_STATE_H

#include "common.h"
#include "system/input.h"
#include "util/types.h"

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
		char			title[ VCP_MAX_STRING_LEN ];
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