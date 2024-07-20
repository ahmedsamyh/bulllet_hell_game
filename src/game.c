#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <config.h>
#include <sprite.h>
#include <entity.h>
#include <player.h>
#include <bullet.h>
#include <common.h>

#define COMMONLIB_IMPLEMENTATION
#include <commonlib.h>

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Game");

    Bullet* bullets = NULL;

    Arena str_arena = Arena_make(0);
    Texture2D* bullet_textures = NULL;

    for (int i = 0; i < 1; ++i) {
        Arena_reset(&str_arena);
        cstr t_str = Arena_alloc_str(str_arena, "resources/gfx/bullet%02d.png", i+1);
        Texture2D t = LoadTexture(t_str);
        if (!IsTextureReady(t)) {
            panic("Can't load texture %s", t_str);
        }
        arrput(bullet_textures, t);
    }

    Texture2D tex = LoadTexture("resources/gfx/player.png");
    Player player = {0};
    if (!Player_init(&player, tex, 1, 1)) {
        panic("Failed to init player!");
    }

    player.pos.x = WIDTH*0.5f;
    player.pos.y = HEIGHT*0.75f;

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(GRAY);
            float delta = GetFrameTime();
            /* Vector2 mpos = GetMousePosition(); */

            Player_control(&player);
            Entity_control_physics((Entity*)&player, delta);
            Entity_update((Entity*)&player);
            if (IsKeyDown(player.keys[ECK_FIRE])) {
                Player_fire(&player, bullet_textures, &bullets);
            }

            Player_draw(&player);

            Arena_reset(&str_arena);
            begin_text_line();
            draw_fps(&str_arena);
            cstr pos_str = Arena_alloc_str(str_arena, "pos: %f, %f", player.pos.x, player.pos.y);
            draw_text_line(pos_str, 20, WHITE);

        EndDrawing();
    }

    arrfree(bullets);
    arrfree(bullet_textures);
    Player_deinit(&player);
    Arena_free(&str_arena);
    CloseWindow();

    return 0;
}
