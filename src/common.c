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

void bind_point_to_rect(Vector2* point, Rectangle rect) {
    if (point->x < rect.x) point->x = rect.x;
    if (point->x > rect.x+rect.width) point->x = rect.x+rect.width;
    if (point->y < rect.y) point->y = rect.y;
    if (point->y > rect.y+rect.height) point->y = rect.y+rect.height;
}

void bind_circle_to_rect(Vector2* point, float radius, Rectangle rect) {
    if (point->x < rect.x+radius) point->x = rect.x+radius;
    if (point->x > rect.x+rect.width-radius) point->x = rect.x+rect.width-radius;
    if (point->y < rect.y+radius) point->y = rect.y+radius;
    if (point->y > rect.y+rect.height-radius) point->y = rect.y+rect.height-radius;
}
