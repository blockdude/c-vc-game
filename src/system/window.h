#ifndef VCP_WINDOW_H
#define VCP_WINDOW_H

#include "../vcp_common.h"
#include "../util/types.h"

enum window_flags
{
    WINDOW_RELATIVE_MOUSE = 0x01,
    WINDOW_VSYNC          = 0x02,
    WINDOW_FULLSCREEN     = 0x04,
    WINDOW_RESIZABLE      = 0x08,
    WINDOW_HIGHDPI        = 0x10
};

#ifdef __cplusplus
extern "C" {
#endif

extern int window_init(void);
extern void window_deinit(void);
extern void window_swap_buffer(void);
extern bool window_keep_open(void);
extern struct extent window_size(void);
extern int window_width(void);
extern int window_height(void);
extern float window_aspect(void);
extern const char *window_title(void);
extern u32 window_flags(void);
extern u32 window_id(void);
extern void *window_handle(void);
extern void window_set_size(int w, int h);
extern void window_set_title(const char *title);
extern void window_set_flags(u32 flags, bool state);
extern void window_toggle_flags(u32 flags);
extern void window_enable_flags(u32 flags);
extern void window_disable_flags(u32 flags);

#ifdef __cplusplus
}
#endif

#endif
