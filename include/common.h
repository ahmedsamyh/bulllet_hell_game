#ifndef _COMMON_H_
#define _COMMON_H_

#include <raylib.h>
#include <commonlib.h>

#define panic(fmt, ...) \
    TraceLog(LOG_ERROR, "[PANIC] "fmt, ##__VA_ARGS__);\
    CloseWindow();\
    return 1

void draw_fps(Arena* str_arena);

#endif // _COMMON_H_
