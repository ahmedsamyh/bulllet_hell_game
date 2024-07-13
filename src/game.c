#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <config.h>
#define COMMONLIB_IMPLEMENTATION
#include <commonlib.h>
#include <sprite.h>

int main(void) {

    InitWindow(WIDTH, HEIGHT, "Game");
    Texture2D tex = LoadTexture("resources/gfx/player.png");
    Sprite spr = {0};
    if (!Sprite_init(&spr, tex, 4, 8)) {
        TraceLog(LOG_ERROR, "Failed to init sprite!");
        CloseWindow();
        return 1;
    }
    Sprite_center_origin(&spr);
    spr.scale.x = 5.0f; spr.scale.y = 5.0f;
    float R = 100.f;
    float S = 0.5;

    Arena str_arena = Arena_make(0);

    Vector2 pos = CLITERAL(Vector2) { WIDTH*0.5f, HEIGHT*0.5f };
    Vector2 vel = CLITERAL(Vector2) { 0.f, 0.f };
    Vector2 acc = CLITERAL(Vector2) { 0.f, 0.f };
    float speed = 250.f;
    Vector2 last_dir = {0};

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(GRAY);
            float delta = GetFrameTime();
            /* Vector2 mpos = GetMousePosition(); */

            // movement
            Vector2 dir = {0};
            if (IsKeyDown(KEY_A)) { dir.x--; }
            if (IsKeyDown(KEY_D)) { dir.x++; }
            if (IsKeyDown(KEY_W)) { dir.y--; }
            if (IsKeyDown(KEY_S)) { dir.y++; }
            dir = Vector2Normalize(dir);
            if (dir.x != 0 || dir.y != 0) { last_dir = dir; }

            /* vel = Vector2Add(vel, acc); */
            vel = Vector2Scale(dir, speed);
            pos = Vector2Add(pos, Vector2Scale(vel, delta));
            acc = Vector2Scale(acc, 0.f);

            // movement animation
            if (last_dir.x < 0) { Sprite_set_vframe(&spr, 2); }
            else if (last_dir.x > 0) { Sprite_set_vframe(&spr, 0); }
            if (last_dir.y < 0) { Sprite_set_vframe(&spr, 3); }
            else if (last_dir.y > 0) { Sprite_set_vframe(&spr, 1); }
            if (dir.x != 0 || dir.y != 0) { Sprite_set_vframe(&spr, spr.vframe + 4); }

            spr.pos = pos;
            Sprite_animate_hframe(&spr, delta);

            if (IsKeyDown(KEY_E)) {
                spr.rotation += R * delta;
            }
            if (IsKeyDown(KEY_Q)) {
                spr.rotation -= R * delta;
            }
            if (IsKeyDown(KEY_X)) {
                float scl = spr.scale.x;
                scl += S * delta;
                spr.scale = CLITERAL(Vector2) { scl, scl };
            }
            if (IsKeyDown(KEY_Z)) {
                float scl = spr.scale.x;
                scl -= S * delta;
                spr.scale = CLITERAL(Vector2) { scl, scl };
            }

            Arena_reset(&str_arena);
            int Y = 0;
            cstr fps_str = Arena_alloc_str(str_arena, "%dFPS", GetFPS());
            DrawText(fps_str, 0, Y, 20, WHITE);
            Y += 20;

            cstr rotation_str = Arena_alloc_str(str_arena, "rotation: %f", spr.rotation);
            DrawText(rotation_str, 0, Y, 20, WHITE);
            Y += 20;

            cstr scale_str = Arena_alloc_str(str_arena, "scale: %f %f", spr.scale.x, spr.scale.y);
            DrawText(scale_str, 0, Y, 20, WHITE);
            Y += 20;

            Sprite_draw(&spr);
        EndDrawing();
    }

    Arena_free(&str_arena);
    Sprite_deinit(&spr);
    CloseWindow();

    return 0;
}
