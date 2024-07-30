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

ENUM(State);

enum State {
    STATE_PLAY,
    STATE_EDIT,
    STATE_COUNT
};

void change_state(State* current, State next) {
    switch (*current) {
        case STATE_PLAY: {
         } break;
        case STATE_EDIT: {
         } break;
        default: {
             ASSERT(0 && "Unreachable!");
         } break;
    }
    *current = next;
}

cstr state_as_str(State state) {
    switch (state) {
        case STATE_PLAY: {
            return "STATE_PLAY";
         } break;
        case STATE_EDIT: {
            return "STATE_EDIT";
         } break;
        default: {
             ASSERT(0 && "Unreachable!");
         } break;
    }
    return "INVALID STATE";
}

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

    State state = STATE_PLAY;
    bool paused = false;

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

            /////////////////////UPDATE///////////////////////

            float delta = GetFrameTime();
            Vector2 mpos = GetMousePosition();

            // DEBUG
            if (IsKeyPressed(KEY_TAB)) {
                DEBUG_DRAW = !DEBUG_DRAW;
            }
            if (IsKeyPressed(KEY_GRAVE)) {
                change_state(&state, (state+1) % STATE_COUNT);
            }
            if (IsKeyPressed(KEY_SPACE)) {
                paused = !paused;
            }

            if (!paused) {
                switch (state) {
                    case STATE_PLAY: {
                     } break;
                    case STATE_EDIT: {
                     } break;
                    default: {
                        ASSERT(0 && "Unreachable");
                     } break;
                }

                Player_control(&player);
                Entity_control_physics((Entity*)&player);
                Player_update(&player);
                if (IsKeyDown(player.keys[ECK_FIRE])) {
                    Player_fire(&player, shot_tex, &shots);
                }

                // DEBUG
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
            }
            // << fold <<

            /////////////////////DRAW/////////////////////////
            Arena_reset(&str_arena);
            begin_text_line();
            switch (state) {
                case STATE_PLAY: {

                 } break;
                case STATE_EDIT: {
                    // draw grid
                    for (int x = 0; x < COLS; ++x) {
                        for (int y = 0; y < ROWS; ++y) {
                            {
                                Vector2 a = {
                                    0, y * TILE_SIZE
                                };
                                Vector2 b = {
                                    WIDTH, y * TILE_SIZE
                                };
                                DrawLineV(a, b, ColorAlpha(WHITE, 0.75f));
                            }
                            {
                                Vector2 a = {
                                    x * TILE_SIZE, 0
                                };
                                Vector2 b = {
                                    x * TILE_SIZE, HEIGHT
                                };
                                DrawLineV(a, b, ColorAlpha(WHITE, 0.75f));
                            }
                        }
                    }
                 } break;
                default: {
                    ASSERT(0 && "Unreachable");
                 } break;
            }

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


            // DEBUG
            if (DEBUG_DRAW) {
                DrawRectangleLinesEx(play_rect, 2.f, BLUE);
            }
            draw_fps(&str_arena);
            cstr pos_str = Arena_alloc_str(str_arena, "pos: %f, %f", player.pos.x, player.pos.y);
            draw_text_line(pos_str, 20, WHITE);
            cstr bullets_count_str = Arena_alloc_str(str_arena, "bullets: %zu", arrlenu(bullets));
            draw_text_line(bullets_count_str, 20, WHITE);
            cstr shots_count_str = Arena_alloc_str(str_arena, "shots: %zu", arrlenu(shots));
            draw_text_line(shots_count_str, 20, WHITE);
            cstr state_str = Arena_alloc_str(str_arena, "State: %s", state_as_str(state));
            draw_text_line(state_str, 20, RED);

            {
                cstr paused_str = Arena_alloc_str(str_arena, "[%s]", (paused ? "P" : " " ));
                Vector2 pos = { WIDTH, 0.f };
                Vector2 text_size = MeasureTextEx(GetFontDefault(), paused_str, 20, 0.f);
                Vector2 origin = { text_size.x, 0.f };
                DrawTextPro(GetFontDefault(), paused_str, pos, origin, 0.f, 20, 0.f, PINK);
            }

            // << fold <<

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
