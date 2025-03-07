#ifndef VCP_PLATFORM_H
#define VCP_PLATFORM_H

#ifndef TIMESTEP_TIME_NOW
#define TIMESTEP_TIME_NOW time_now_s
#endif

#ifndef TIMESTEP_TIME_WAIT
#define TIMESTEP_TIME_WAIT time_wait_s
#endif

#include "graphics/shader.h"
#include "graphics/vao.h"
#include "graphics/vbo.h"
#include "math/color.h"
#include "math/math.h"
#include "math/mat4.h"
#include "math/quat.h"
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/vec4.h"
#include "system/allocator.h"
#include "system/audio.h"
#include "system/input.h"
#include "system/time.h"
#include "system/window.h"
#include "util/bitflag.h"
#include "util/timestep.h"
#include "util/camera.h"
#include "util/kdtree.h"
#include "util/list.h"
#include "util/log.h"
#include "util/types.h"
#include "common.h"

enum platform_init_flags
{
	WINDOW = BITFLAG( 0 ),
	INPUT  = BITFLAG( 1 ),
	AUDIO  = BITFLAG( 2 ),
	TIMER  = BITFLAG( 3 )
};

extern int platform_init( uint32_t flags );
extern void platform_deinit( void );

#endif
