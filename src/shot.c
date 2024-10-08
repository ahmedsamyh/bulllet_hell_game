#include <shot.h>
#include <bullet.h>
#include <momomath.h>

bool Shot_init(Shot* this, Texture2D texture) {
    if (!Entity_init((Entity*)this, texture, 1, 1)) { return false; }
    Shot_set_speed(this, PLAYER_SHOT_MIN_SPEED, PLAYER_SHOT_MAX_SPEED, PLAYER_SHOT_SPEED, PLAYER_SHOT_SPEED_DELTA);
    this->spr.scale = CLITERAL(Vector2) {2.f, 2.f};

    this->angle = -90.f;
    this->spawning_move = true;

    arrput(this->collide_ids, CID_PLAYER_BULLET);
    arrput(this->collide_masks, CID_ENEMY);

    return true;
}

void Shot_update(Shot* this) {
    Bullet_update((Bullet*)this);
    this->spr.rotation = this->angle + 90.f;
}

void Shot_draw(Shot* this, bool debug) {
    Bullet_draw((Bullet*)this, debug);
}

void Shot_set_speed(Shot* this, float min, float max, float curr, float delta) {
    Bullet_set_speed((Bullet*)this, min, max, curr, delta);
}

void Shot_deinit(Shot* this) {
    Bullet_deinit((Bullet*)this);
}

