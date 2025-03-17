/**
 * Copyright (c) 2020 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

#ifndef VCP_LOG_H
#define VCP_LOG_H

#include "../common.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>

#define LOG_VERSION "0.1.0"

struct log_event
{
    va_list ap;
    const char *fmt;
    const char *file;
    struct tm *time;
    void *udata;
    int line;
    int level;
};

typedef void (*log_log_fn)(struct log_event *ev);
typedef void (*log_lock_fn)(bool lock, void *udata);

enum log_level
{
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL
};

#define log_trace(...) log_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...) log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)  log_log(LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...)  log_log(LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) log_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...) log_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

extern const char *log_level_string(int level);
extern void log_set_lock(log_lock_fn fn, void *udata);
extern void log_set_level(int level);
extern void log_set_quiet(bool enable);
extern int log_add_callback(log_log_fn fn, void *udata, int level);
extern int log_add_fp(FILE *fp, int level);
extern void log_log(int level, const char *file, int line, const char *fmt, ...);

#endif
