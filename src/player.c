#include <player.h>
#include <common.h>

bool Player_init(Player* this, Texture2D tex, size_t hframes, size_t vframes) {
    if (!Entity_init((Entity*)this, tex, hframes, vframes)) {
        return false;
    }

   this->speed = PLAYER_DEFAULT_SPEED;

   this->keys[ECK_RIGHT] = KEY_RIGHT;
   this->keys[ECK_LEFT]  = KEY_LEFT;
   this->keys[ECK_UP]    = KEY_UP;
   this->keys[ECK_DOWN]  = KEY_DOWN;
   this->keys[ECK_FIRE]  = KEY_Z;

   this->hitbox = PLAYER_HITBOX;
   this->fire_alarm.alarm_time = PLAYER_FIRE_RATE;

   arrput(this->collide_ids, CID_PLAYER);

   return true;
}

void Player_update(Player* this) {
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

void Player_draw(Player* this, bool debug) {
    Entity_draw((Entity*)this, debug);
}

void Player_control(Player* this) {
    Entity_control((Entity*)this);
}

void Player_fire(Player* this, Texture2D* bullet_textures, Bullet** bullets) {
    float delta = GetFrameTime();
    if (Alarm_on_alarm(&this->fire_alarm, delta)) {
        /* void add_bullet(Bullet** bullets, Texture2D* textures, Vector2 pos, Bullet_type type) { */
        Bullet b = {0};
        if (!Bullet_init(&b, bullet_textures, BT_0, BC_CYAN)) {
            log_warning("Failed to init bullet in %s()!", __func__);
        }
        b.pos = this->pos;
        arrput(*bullets, b);
    }
}

void Player_deinit(Player* this) {
    Entity_deinit((Entity*)this);
}
