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
#include <spawner.h>

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
        case STATE_COUNT:
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
        case STATE_COUNT:
         } break;
        default: {
             ASSERT(0 && "Unreachable!");
         } break;
    }
    return "INVALID STATE";
}

#define reset() do { \
    edit_time = 0.f;\
    edit_time_paused = true;\
    play_time = 0.f;\
} while (0)

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Game");

    bool DEBUG_DRAW = false;

    Bullet* bullets = NULL; // dynamic-array
    Shot*   shots = NULL; // dynamic-array
    Texture2D* bullet_textures = NULL; // dynamic-array
    Enemy* enemies = NULL; // dynamic-array
    Spawner* spawners = NULL; // dynamic-array
    int* selected_spawner_ids = NULL; // dynamic-array

    Rectangle play_rect = {
        .x = 20.f,
        .y = 20.f,
        .width = WIDTH-(2.f*20.f),
        .height = HEIGHT-(2.f*20.f),
    };

    State state = STATE_PLAY;
    bool paused = false;

    float play_time = 0.f;
    float edit_time = 0.f;
    float edit_time_paused = true;
    Vector2 edit_cursor = {0};
    Vector2 select_area_start, select_area_end = {0};
    bool selecting = false;

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

    Texture2D spawner_tex = LoadTexture("resources/gfx/spawner.png");
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
            if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_SPACE)) {
                paused = !paused;
            }

            if (!paused) {
                switch (state) {
                    case STATE_PLAY: {
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

                            if (IsKeyDown(KEY_THREE)) {
                                e.pattern = pattern3;
                            }

                            arrput(enemies, e);
                        }

                        // SPAWNER SPAWN
                        for (int i = arrlenu(spawners)-1; i >= 0; --i) {
                            Spawner_spawn(&spawners[i], play_time);
                            if (spawners[i].spawned) {
                                arrdel(spawners, i);
                            }
                        }

                        play_time += delta;
                     } break;
                    case STATE_EDIT: {
                        edit_cursor.x = ((int)mpos.x / (int)TILE_SIZE) * TILE_SIZE;
                        edit_cursor.y = ((int)mpos.y / (int)TILE_SIZE) * TILE_SIZE;

                        // ADD SPAWNER
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                            Spawner s = {0};
                            Spawner_init(&s, spawner_tex, &bullets, &enemies, edit_time, edit_cursor);
                            arrput(spawners, s);
                        }

                        // SELECT
                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            select_area_start = mpos;
                        }

                        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                            selecting = true;
                            select_area_end = mpos;
                        }

                        if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
                            selecting = false;
                            Rectangle select_area = {
                                .x = fminf(select_area_start.x, select_area_end.x),
                                .y = fminf(select_area_start.y, select_area_end.y),
                                .width = (select_area_start.x < select_area_end.x ? select_area_end.x - select_area_start.x : select_area_start.x - select_area_end.x),
                                .height = (select_area_start.y < select_area_end.y ? select_area_end.y - select_area_start.y : select_area_start.y - select_area_end.y),
                            };

                            for (int i = 0; i < arrlen(spawners); ++i) {
                                Spawner* s = &spawners[i];
                                if (CheckCollisionPointRec(s->pos, select_area)) {
                                    s->selected = true;
                                } else {
                                    s->selected = false;
                                }
                            }
                        }

                        // SAVE SPAWNER
                        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S)) {
                            if (SaveFileData("spawners.data", spawners, arrlenu(spawners)*sizeof(Spawner))) {
                                log_info("Saved %d bytes (%d spawners) to disk!", arrlenu(spawners)*sizeof(Spawner), arrlenu(spawners));
                            } else {
                                log_error("Couldn't save spawners to disk!");
                            }
                        }

                        // LOAD SPAWNER
                        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_L)) {
                            Spawner* old_spawners = spawners;
                            int loaded_data_size;
                            Spawner* loaded_spawners = (Spawner*)LoadFileData("spawners.data", &loaded_data_size);
                            if (loaded_spawners) {
                                log_info("Loaded %d bytes (%d spawners) from disk!", loaded_data_size, loaded_data_size / sizeof(Spawner));
                                // TODO: Prompt user for deletion of current spawners
                                arrfree(spawners);
                                for (size_t i = 0; i < (loaded_data_size/sizeof(Spawner)); ++i) {
                                    arrput(spawners, loaded_spawners[i]);
                                }
                                UnloadFileData((unsigned char*)loaded_spawners);
                            } else {
                                log_error("Failed to load spawners from disk!");
                            }
                        }

                        if (!IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_SPACE)) {
                            edit_time_paused = !edit_time_paused;
                        }

                     } break;
                    case STATE_COUNT:
                    default: {
                        ASSERT(0 && "Unreachable");
                     } break;
                }

                if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_R)) {
                    reset();
                }

                Player_control(&player);
                Player_update(&player);
                bind_circle_to_rect(&player.pos, player.hitbox, play_rect);
                if (IsKeyDown(player.keys[ECK_FIRE])) {
                    Player_fire(&player, shot_tex, &shots);
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
                    if (!CheckCollisionPointRec(sh->pos, play_rect)) {
                        sh->despawning = true;
                    }
                    // COLLIDE SHOT ENEMY
                    for (size_t j = 0; j < arrlenu(enemies); ++j) {
                        Enemy* e = &enemies[j];
                        if (Entity_collide((Entity*)sh, (Entity*)e)) {
                            sh->despawning = true;
                            Entity_damage((Entity*)e, sh->attack_points);
                        }
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
            draw_fps(&str_arena);
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
                                DrawLineV(a, b, ColorAlpha(WHITE, 0.01f));
                            }
                            {
                                Vector2 a = {
                                    x * TILE_SIZE, 0
                                };
                                Vector2 b = {
                                    x * TILE_SIZE, HEIGHT
                                };
                                DrawLineV(a, b, ColorAlpha(WHITE, 0.01f));
                            }
                        }
                    }
                    // spawner count
                    cstr spawners_count_str = Arena_alloc_str(str_arena, "spawners count: %zu", arrlenu(spawners));
                    draw_text_line(spawners_count_str, 20, WHITE);

                    cstr edit_time_str = Arena_alloc_str(str_arena, "time: %.3f %s", edit_time, (edit_time_paused ? "[PAUSED]" : ""));
                    draw_text_line(edit_time_str, 20, WHITE);

                    // SPAWNER DRAW
                    for (size_t i = 0; i < arrlenu(spawners); ++i) {
                        Spawner_draw(&spawners[i]);
                    }

                    // draw cursor
                    DrawCircleV(edit_cursor, TILE_SIZE*0.25f, RED);

                    if (selecting) {
                        Rectangle select_area = {
                            .x = fminf(select_area_start.x, select_area_end.x),
                            .y = fminf(select_area_start.y, select_area_end.y),
                            .width = (select_area_start.x < select_area_end.x ? select_area_end.x - select_area_start.x : select_area_start.x - select_area_end.x),
                            .height = (select_area_start.y < select_area_end.y ? select_area_end.y - select_area_start.y : select_area_start.y - select_area_end.y),
                        };

                        DrawRectangleLinesEx(select_area, 2.f, BLUE);
                    }

                 } break;
                case STATE_COUNT:
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
            cstr play_time_str = Arena_alloc_str(str_arena, "play_time: %.2f", play_time);
            draw_text_line(play_time_str, 20, WHITE);
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
    arrfree(spawners);
    arrfree(selected_spawner_ids);
    Player_deinit(&player);
    Arena_free(&str_arena);
    CloseWindow();

    return 0;
}
