#ifndef CORE_INTERNAL_H
#define CORE_INTERNAL_H

#include "app.h"
#include "input.h"

#include <stdbool.h>
#include <util/types.h>

struct core
{
	unsigned int		flags;

	struct
	{
		bool         	running;
		bool			quit;

		int          	f_rate;
		float        	f_avg;
		float        	f_delta;
		float        	f_target;
		uint64_t     	f_count;

		int          	t_rate;
		float        	t_avg;
		float        	t_delta;
		float        	t_target;
		uint64_t     	t_count;

		// capture the frame rate & tick rate of the last second
		float           timer;
		uint64_t        f_last;
		uint64_t        t_last;

		double          elapsed;
		double          current;
		double          previous;
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
