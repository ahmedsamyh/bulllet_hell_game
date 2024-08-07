#include <spawner.h>
#include <math.h>

bool Spawner_init(Spawner* this, Texture2D tex, Bullet** bullets, Enemy** enemies, float time, Vector2 pos) {
    this->bullets = bullets;
    this->enemies = enemies;
    this->time = time;
    this->pos = pos;
    if (!Sprite_init(&this->spr, tex, 1, 1)) { return false; }
    Sprite_center_origin(&this->spr);
    return true;
}

void Spawner_spawn(Spawner* this, float play_time) {
    if (fabsf(play_time - this->time) < 0.15f) {
        // spawn
        log_info("SPAWN!!!");
        this->spawned = true;
    }
}

void Spawner_draw(Spawner* this) {
    this->spr.pos = this->pos;
    if (this->selected) this->spr.tint = BLUE;
    else                this->spr.tint = WHITE;
    Sprite_draw(&this->spr);
}
