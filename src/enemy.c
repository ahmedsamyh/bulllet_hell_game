#include <enemy.h>

void default_pattern(Enemy* this, Texture2D* bullet_textures, Bullet** bullets) {
    float angle = 0.f;
    this->fire_alarm.alarm_time = 1.f;
    this->fire_count_max = 10;
    this->bullet_count = 5;
    for (size_t i = 0; i < this->bullet_count; ++i) {
        Bullet b = {0};
        if (!Bullet_init(&b, bullet_textures, BT_0, BC_CYAN)) {
            log_warning("Failed to init bullet in %s()!", __func__);
        }
        b.pos = this->pos;
        b.angle = angle;
        Bullet_set_speed(&b, 0.f, 500.f, 100.f, 50.f);
        angle += (360.f / this->bullet_count);
        arrput(b.collide_masks, CID_PLAYER);
        arrput(b.collide_ids, CID_ENEMY_BULLET);
        arrput(*bullets, b);
    }
}

void pattern1(Enemy* this, Texture2D* bullet_textures, Bullet** bullets) {
    float angle = this->dataf[0];
    this->dataf[0] += 5.f;
    this->fire_alarm.alarm_time = 0.1f;
    this->fire_count_max = 50;
    this->bullet_count = 8;
    for (size_t i = 0; i < this->bullet_count; ++i) {
        Bullet b = {0};
        if (!Bullet_init(&b, bullet_textures, BT_0, BC_CYAN)) {
            log_warning("Failed to init bullet in %s()!", __func__);
        }
        b.pos = this->pos;
        b.angle = angle;
        Bullet_set_speed(&b, 100.f, 500.f, 500.f, -50.f);
        angle += (360.f / this->bullet_count);
        arrput(b.collide_masks, CID_PLAYER);
        arrput(b.collide_ids, CID_ENEMY_BULLET);
        arrput(*bullets, b);
    }
}

void pattern2(Enemy* this, Texture2D* bullet_textures, Bullet** bullets) {
    float angle = this->dataf[0];
    this->dataf[0] += 93.1f;
    this->fire_alarm.alarm_time = 0.1;
    this->fire_count_max = 100;
    this->bullet_count = 20;
    for (size_t i = 0; i < this->bullet_count; ++i) {
        Bullet b = {0};
        if (!Bullet_init(&b, bullet_textures, BT_0, BC_PINK)) {
            log_warning("Failed to init bullet in %s()!", __func__);
        }
        b.pos = this->pos;
        b.angle = angle;
        Bullet_set_speed(&b, 50.f, 500.f, 500.f, -200.f);
        angle += (360.f / this->bullet_count);
        arrput(b.collide_masks, CID_PLAYER);
        arrput(b.collide_ids, CID_ENEMY_BULLET);
        arrput(*bullets, b);
    }
}

bool Enemy_init(Enemy* this, Texture2D tex, size_t hframes, size_t vframes) {
    if (!Entity_init((Entity*)this, tex, hframes, vframes)) {
        return false;
    }
    this->spr.tint = RED; // TMP

    this->pattern = default_pattern;

    this->fire_alarm.alarm_time = 1.f;
    this->fire_count = 0, this->fire_count_max = 10; // TODO: 0 means infinite
    this->bullet_count = 5;
    this->die_alarm.alarm_time = 3.f;

    return true;
}

void Enemy_update(Enemy* this) {
    if (this->spawning && !this->spawned) {
        Entity_spawn((Entity*)this);
    }
    if (this->spawned && !this->spawning && !this->despawned && !this->despawning) {
        // UPDATE
        float delta = GetFrameTime();
        if (this->fire_count == this->fire_count_max) {
            this->despawning = true;
        }
    }
    if (this->despawning && !this->despawned) {
        Entity_despawn((Entity*)this);
    }
}

void Enemy_draw(Enemy* this, bool debug) {
   Entity_draw((Entity*)this, debug);
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
