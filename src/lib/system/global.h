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

		float        	f_delta;
		float        	f_target;
		float        	f_avg;
		int          	f_rate;
		uint64_t     	f_count;

		float        	t_delta;
		float        	t_target;
		float        	t_avg;
		int          	t_rate;
		uint64_t     	t_count;

		double          elapsed;
		float           timer;
		uint64_t        f_last;
		uint64_t        t_last;

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
