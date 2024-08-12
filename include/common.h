#ifndef _COMMON_H_
#define _COMMON_H_

#include <raylib.h>
#include <bullet.h>
#include <commonlib.h>

#define panic(fmt, ...) \
    TraceLog(LOG_ERROR, "[PANIC] "fmt, ##__VA_ARGS__);\
    CloseWindow();\
    return 1

static int Y = 0;
void draw_fps(Arena* str_arena);
void begin_text_line(void);
void draw_text_line(const char *text, int fontSize, Color color);

void bind_point_to_rect(Vector2* point, Rectangle rect);
void bind_circle_to_rect(Vector2* point, float radius, Rectangle rect);

#endif // _COMMON_H_
