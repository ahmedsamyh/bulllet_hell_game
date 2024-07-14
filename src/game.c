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

    Arena str_arena = Arena_make(0);
    Camera2D cam = {
        .offset = {0},
        .target = {WIDTH*0.5f, HEIGHT*0.5f},
        .rotation = 0.f,
        .zoom = 2.f,
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(GRAY);
            /* float delta = GetFrameTime(); */
            Vector2 mposs = GetMousePosition();
            Vector2 mposw = GetScreenToWorld2D(mposs, cam);
            e.pos = mposw;

            BeginMode2D(cam);
                Entity_draw(&e);
            EndMode2D();
            draw_fps(&str_arena);
        EndDrawing();
    }

    Entity_deinit(&e);
    Arena_free(&str_arena);
    CloseWindow();

    return 0;
}
