#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <config.h>
#include <sprite.h>

int main(void) {

    InitWindow(WIDTH, HEIGHT, "Game");
    Texture2D tex = LoadTexture("resources/gfx/flower.png");
    Sprite spr = {0};
    if (!Sprite_init(&spr, tex, 1, 1)) {
        TraceLog(LOG_ERROR, "Failed to init sprite!");
        CloseWindow();
        return 1;
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
        EndDrawing();
    }

    Sprite_deinit(&spr);
    CloseWindow();

    return 0;
}
