#ifndef VCP_PLATFORM_H
#define VCP_PLATFORM_h

#ifndef TS_TIME
#define TS_TIME time_now_s
#endif

#ifndef TS_SLEEP
#define TS_SLEEP time_wait_s
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

enum platform_flags
{
	WINDOW = BITFLAG( 0 ),
	INPUT  = BITFLAG( 1 ),
	AUDIO  = BITFLAG( 2 ),
	TIMER  = BITFLAG( 3 )
};

int  platform_init( unsigned int flags );
void platform_deinit( void );
void platform_allocator_set( void );
void platform_logger_set( void );

#endif
