#ifndef CORE_INTERNAL_H
#define CORE_INTERNAL_H

#include "app.h"
#include "input.h"

#include <util/types.h>

struct core
{
	unsigned int		flags;

	struct
	{
		bool         	running;

		float        	frame_delta;
		float        	frame_target;
		float        	frame_avg;
		int          	frame_rate;
		uint64_t     	frame_count;

		float        	tick_delta;
		float        	tick_target;
		float        	tick_avg;
		int          	tick_rate;
		uint64_t     	tick_count;
	} timestep;

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

		void *			handle;
		void *			context;
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

	struct
	{
		struct app state;
	} app;
};

extern struct core core;

#endif
