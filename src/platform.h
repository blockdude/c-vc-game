#ifndef VCP_PLATFORM_H
#define VCP_PLATFORM_H

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
#include "util/log.h"
#include "util/types.h"
#include "util/tcast.h"
#include "common.h"
#include "version.h"

enum platform_init_flags
{
    WINDOW = BITFLAG(0),
    INPUT  = BITFLAG(1),
    AUDIO  = BITFLAG(2),
    TIMER  = BITFLAG(3)
};

extern int platform_init(u32 flags);
extern void platform_deinit(void);

#endif
