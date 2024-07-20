#include <common.h>

void begin_text_line(void) {
    Y = 0;
}

void draw_text_line(const char *text, int fontSize, Color color) {
    DrawText(text, 0, Y, fontSize, color);
    Y += fontSize;
}


void draw_fps(Arena* str_arena) {
    cstr fps_str = Arena_alloc_str(*str_arena, "%dFPS", GetFPS());
    draw_text_line(fps_str, 20, WHITE);
}

void add_bullet(Bullet** bullets, Vector2 pos, Bullet_type type) {
    Bullet b = {0};
}
