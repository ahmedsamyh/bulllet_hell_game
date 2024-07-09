#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <thing.h>
#include <config.h>
#define STB_DS_IMPLEMENTATION
#include <stb_ds.h>

static Thing *things = NULL;

void add_thing(Texture2D tex, Vector2 pos) {
    for (int i = 0; i < 100; ++i) {
        Vector2 actual_pos = Vector2Add(pos, CLITERAL(Vector2) {GetRandomValue(-100.f, 100.f), GetRandomValue(-100.f, 100.f)});
        Thing t = make_thing(tex, actual_pos);
        arrput(things, t);
        TraceLog(LOG_INFO, "%zu", arrlenu(things));
    }
}

int main(void)
{
    const char *title = "Game";
    InitWindow(WIDTH, HEIGHT, title);
    Texture2D flower_tex = LoadTexture("resources/gfx/flower.png");
    while (!WindowShouldClose())
    {
        BeginDrawing();
            float delta = GetFrameTime();

            if (IsKeyPressedRepeat(KEY_SPACE)) {
                add_thing(flower_tex, GetMousePosition());
            }

            for (int i = arrlenu(things) - 1; i >= 0; --i) {
                Thing* t = &things[i];
                warp_thing(t);
                update_thing(t, delta);
                draw_thing(t);
            }

            DrawFPS(0, 0);
            ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
