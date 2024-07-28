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

void Player_fire(Player* this, Texture2D shot_texture, Shot** shots) {
    float delta = GetFrameTime();
    if (Alarm_on_alarm(&this->fire_alarm, delta)) {
        Shot sh = {0};
        if (!Shot_init(&sh, shot_texture)) {
            log_warning("Failed to init shot in %s()!", __func__);
        }
        sh.pos = this->pos;
        arrput(*shots, sh);
    }
}

void Player_deinit(Player* this) {
    Entity_deinit((Entity*)this);
}
