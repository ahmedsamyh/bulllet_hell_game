#include <common.h>

void draw_fps(Arena* str_arena) {
    Arena_reset(str_arena);
    cstr fps_str = Arena_alloc_str(*str_arena, "%dFPS", GetFPS());
    DrawText(fps_str, 0, 0, 20, WHITE);
}
