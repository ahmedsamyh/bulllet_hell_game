#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <config.h>
#include <sprite.h>
#include <entity.h>
#include <common.h>

#define COMMONLIB_IMPLEMENTATION
#include <commonlib.h>

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Game");
    Texture2D tex = LoadTexture("resources/gfx/player.png");
    Entity e = {0};
    if (!Entity_init(&e, tex, 1, 1)) {
        panic("Failed to init entity!");
    }
    e.pos.x = WIDTH*0.5f;
    e.pos.y = HEIGHT*0.75f;

    Arena str_arena = Arena_make(0);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(GRAY);
            float delta = GetFrameTime();
            Vector2 mpos = GetMousePosition();

            Entity_control(&e);
            Entity_control_physics(&e, delta);
            Entity_update(&e);

            Entity_draw(&e);

            Arena_reset(&str_arena);
            begin_text_line();
            draw_fps(&str_arena);
            cstr pos_str = Arena_alloc_str(str_arena, "pos: %f, %f", e.pos.x, e.pos.y);
            /* RLAPI void DrawText(const char *text, int posX, int posY, int fontSize, Color color);       // Draw text (using default font) */
            draw_text_line(pos_str, 20, WHITE);

        EndDrawing();
    }

    Entity_deinit(&e);
    Arena_free(&str_arena);
    CloseWindow();

    return 0;
}
