#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <config.h>
#include <sprite.h>
#include <entity.h>
#include <player.h>
#include <bullet.h>
#include <shot.h>
#include <enemy.h>
#include <common.h>

#define COMMONLIB_IMPLEMENTATION
#include <commonlib.h>

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Game");

    bool DEBUG_DRAW = false;

    Bullet* bullets = NULL; // dynamic-array
    Shot*   shots = NULL; // dynamic-array
    Texture2D* bullet_textures = NULL; // dynamic-array
    Enemy* enemies  = NULL; // dynamic-array

    Rectangle play_rect = {
        .x = 20.f,
        .y = 20.f,
        .width = WIDTH-(2.f*20.f),
        .height = HEIGHT-(2.f*20.f),
    };

    Arena str_arena = Arena_make(0);

    for (int i = 0; i < 1; ++i) {
        Arena_reset(&str_arena);
        cstr t_str = Arena_alloc_str(str_arena, "resources/gfx/bullet%02d.png", i+1);
        Texture2D t = LoadTexture(t_str);
        if (!IsTextureReady(t)) {
            panic("Can't load texture %s", t_str);
        }
        arrput(bullet_textures, t);
    }
    /* log_info("bullet_textures_count: %u", arrlenu(bullet_textures)); */

    Texture2D tex = LoadTexture("resources/gfx/player.png");
    Player player = {0};
    if (!Player_init(&player, tex, 1, 1)) {
        panic("Failed to init player!");
    }

    Texture2D shot_tex = LoadTexture("resources/gfx/player_shot.png");

    Texture2D entity_tex = LoadTexture("resources/gfx/entity.png");
    ASSERT(IsTextureReady(entity_tex));

    player.pos.x = WIDTH*0.5f;
    player.pos.y = HEIGHT*0.75f;

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(GRAY);
            float delta = GetFrameTime();
            Vector2 mpos = GetMousePosition();

            Player_control(&player);
            Entity_control_physics((Entity*)&player);
            Player_update(&player);
            if (IsKeyDown(player.keys[ECK_FIRE])) {
                Player_fire(&player, shot_tex, &shots);
            }

            // DEBUG
            if (IsKeyPressed(KEY_TAB)) {
                DEBUG_DRAW = !DEBUG_DRAW;
            }
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Enemy e = {0};
                if (!Enemy_init(&e, entity_tex, 1, 1)) {
                    CloseWindow();
                }
                e.pos = mpos;
                e.bullet_count = 100;

                if (IsKeyDown(KEY_ONE)) {
                    e.pattern = pattern1;
                }

                if (IsKeyDown(KEY_TWO)) {
                    e.pattern = pattern2;
                }

                arrput(enemies, e);
            }

            /* if (IsKeyPressed(KEY_X)) { */
            /*     for (int i = 0; i < arrlenu(enemies); ++i) { */
            /*         enemies[i].despawning = true; */
            /*     } */
            /* } */

            // BULLET UPDATE
            for (int i = arrlenu(bullets)-1; i >= 0; --i) {
                Bullet* b = &bullets[i];
                Bullet_update(b);
                if (!CheckCollisionPointRec(b->pos, play_rect) ||
                    Entity_collide((Entity*)b, (Entity*)&player)) {
                    b->despawning = true;
                }
                if (b->despawned) {
                    arrdel(bullets, i);
                }
            }

            // SHOT UPDATE
            for (int i = arrlenu(shots)-1; i >= 0; --i) {
                Shot* sh = &shots[i];
                Shot_update(sh);
                if (!CheckCollisionPointRec(sh->pos, play_rect) ||
                    Entity_collide((Entity*)sh, (Entity*)&player)) {
                    sh->despawning = true;
                }
                if (sh->despawned) {
                    arrdel(shots, i);
                }
            }

            // ENEMY UPDATE
            for (int i = arrlenu(enemies)-1; i >= 0; --i) {
                Enemy* e = &enemies[i];
                Enemy_update(e);
                Enemy_fire(e, bullet_textures, &bullets);
                if (!CheckCollisionPointRec(e->pos, play_rect)) {
                    e->despawning = true;
                }
                if (e->despawned) {
                    arrdel(enemies, i);
                }
            }

            /////////////////////DRAW/////////////////////////
            Player_draw(&player, DEBUG_DRAW);

            // ENEMY DRAW
            for (int i = arrlenu(enemies)-1; i >= 0; --i) {
                Enemy* e = &enemies[i];
                Enemy_draw(e, DEBUG_DRAW);
            }

            // BULLET DRAW
            for (int i = arrlenu(bullets)-1; i >= 0; --i) {
                Bullet* b = &bullets[i];
                Bullet_draw(b, DEBUG_DRAW);
            }

            // SHOT DRAW
            for (int i = arrlenu(shots)-1; i >= 0; --i) {
                Shot* sh = &shots[i];
                Shot_draw(sh, DEBUG_DRAW);
            }

            Arena_reset(&str_arena);
            begin_text_line();
            draw_fps(&str_arena);
            cstr pos_str = Arena_alloc_str(str_arena, "pos: %f, %f", player.pos.x, player.pos.y);
            draw_text_line(pos_str, 20, WHITE);
            cstr bullets_count_str = Arena_alloc_str(str_arena, "bullets: %zu", arrlenu(bullets));
            draw_text_line(bullets_count_str, 20, WHITE);
            cstr shots_count_str = Arena_alloc_str(str_arena, "shots: %zu", arrlenu(shots));
            draw_text_line(shots_count_str, 20, WHITE);

            // DEBUG
            if (DEBUG_DRAW) {
                DrawRectangleLinesEx(play_rect, 2.f, BLUE);
            }

        EndDrawing();
    }

    arrfree(bullets);
    arrfree(shots);
    arrfree(enemies);
    arrfree(bullet_textures);
    Player_deinit(&player);
    Arena_free(&str_arena);
    CloseWindow();

    return 0;
}
