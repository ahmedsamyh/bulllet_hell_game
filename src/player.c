#include <player.h>
#include <common.h>
#include <raymath.h>

bool Player_init(Player* this, Texture2D tex, size_t hframes, size_t vframes) {
    if (!Entity_init((Entity*)this, tex, hframes, vframes)) {
        return false;
    }

   this->speed = PLAYER_DEFAULT_SPEED;
   this->alt_speed = this->speed * 0.5f;

   this->keys[ECK_RIGHT] = KEY_RIGHT;
   this->keys[ECK_LEFT]  = KEY_LEFT;
   this->keys[ECK_UP]    = KEY_UP;
   this->keys[ECK_DOWN]  = KEY_DOWN;
   this->keys[ECK_FIRE]  = KEY_Z;
   this->keys[ECK_ALT]   = KEY_LEFT_SHIFT;
   this->keys[ECK_ANGLE] = KEY_X;

   this->hitbox = PLAYER_HITBOX;
   this->fire_alarm.alarm_time = PLAYER_FIRE_RATE;

   this->angle = -90.f;
   this->angle_delta = 90.f;

   arrput(this->collide_ids, CID_PLAYER);

   return true;
}

void Player_update(Player* this) {
    if (this->spawning && !this->spawned) {
        Entity_spawn((Entity*)this);
    }
    if (this->spawned && !this->spawning && !this->despawned && !this->despawning) {
        // UPDATE
        if (this->angling) {
            Player_angle(this);
        } else {
            Player_control_physics(this);
        }
    }
    if (this->despawning && !this->despawned) {
        Entity_despawn((Entity*)this);
    }
}

void Player_angle(Player* this) {
    float delta = GetFrameTime();
    if (IsKeyDown(this->keys[ECK_LEFT])) {
        this->angle -= this->angle_delta * delta * (this->alt ? 1.f : 2.f);
    }
    if (IsKeyDown(this->keys[ECK_RIGHT])) {
        this->angle += this->angle_delta * delta * (this->alt ? 1.f : 2.f);
    }
    this->spr.rotation = this->angle + 90.f;
}

void Player_draw(Player* this, bool debug) {
    Entity_draw((Entity*)this, debug);
}

void Player_control(Player* this) {
    Entity_control((Entity*)this);
    this->alt = IsKeyDown(this->keys[ECK_ALT]);
    this->angling = IsKeyDown(this->keys[ECK_ANGLE]);
}

void Player_fire(Player* this, Texture2D shot_texture, Shot** shots) {
    float delta = GetFrameTime();
    if (Alarm_on_alarm(&this->fire_alarm, delta)) {
        Shot sh = {0};
        if (!Shot_init(&sh, shot_texture)) {
            log_warning("Failed to init shot in %s()!", __func__);
        }
        sh.pos = this->pos;
        sh.angle = this->angle;
        arrput(*shots, sh);
    }
}

void Player_control_physics(Player* this) {
    float delta = GetFrameTime();
    this->vel = Vector2Scale(this->dir, (this->alt ? this->alt_speed : this->speed));
    this->pos = Vector2Add(this->pos, Vector2Scale(this->vel, delta));
    this->acc = Vector2Scale(this->acc, 0.f);
}

void Player_deinit(Player* this) {
    Entity_deinit((Entity*)this);
}
