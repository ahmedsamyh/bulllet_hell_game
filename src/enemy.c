#include <enemy.h>

void default_pattern(Enemy* this,Texture2D* bullet_textures, Bullet** bullets) {
    for (size_t i = 0; i < this->bullet_count; ++i) {
        Bullet b = {0};
        if (!Bullet_init(&b, bullet_textures, BT_0)) {
            log_warning("Failed to init bullet in %s()!", __func__);
        }
        b.pos = this->pos;
        arrput(*bullets, b);
    }
}

bool Enemy_init(Enemy* this, Texture2D tex, size_t hframes, size_t vframes) {
    if (!Entity_init((Entity*)this, tex, hframes, vframes)) {
        return false;
    }
    this->spr.tint = RED;

    this->pattern = default_pattern;

    this->fire_alarm.alarm_time = 1.f;
    this->fire_count = 0, this->fire_count_max = 10; // 0 means infinite
    this->bullet_count = 5;

    return true;
}

void Enemy_update(Enemy* this) {
    if (this->spawning && !this->spawned) {
        Entity_spawn((Entity*)this);
    }
    if (this->spawned && !this->spawning && !this->despawned && !this->despawning) {
        // UPDATE
    }
    if (this->despawning && !this->despawned) {
        Entity_despawn((Entity*)this);
    }
}

void Enemy_draw(Enemy* this) {
   Entity_draw((Entity*)this);
}

void Enemy_fire(Enemy* this, Texture2D* bullet_textures, Bullet** bullets) {
    float delta = GetFrameTime();
    if (Alarm_on_alarm(&this->fire_alarm, delta)) {
        ASSERT(this->pattern);
        if (this->fire_count < this->fire_count_max) {
            this->pattern(this, bullet_textures, bullets);
        }
        this->fire_count++;
    }
}

void Enemy_deinit(Enemy* this) {
    Entity_deinit((Entity*)this);
}
