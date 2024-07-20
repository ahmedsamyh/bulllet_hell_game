#include <player.h>

bool Player_init(Player* this, Texture2D tex, size_t hframes, size_t vframes) {
    if (!Entity_init((Entity*)this, tex, hframes, vframes)) {
        return false;
    }

   this->speed = PLAYER_DEFAULT_SPEED;

   this->keys[ECK_RIGHT] = KEY_L;
   this->keys[ECK_LEFT]  = KEY_H;
   this->keys[ECK_UP]    = KEY_K;
   this->keys[ECK_DOWN]  = KEY_J;
   this->keys[ECK_FIRE]  = KEY_W;

   this->fire_alarm.alarm_time = PLAYER_FIRE_RATE;
   return true;
}

void Player_draw(Player* this) {
    Entity_draw((Entity*)this);
}

void Player_control(Player* this) {
    Entity_control((Entity*)this);
}

void Player_fire(Player* this, Texture2D* bullet_textures, Bullet** bullets) {
    float delta = GetFrameTime();
    if (Alarm_on_alarm(&this->fire_alarm, delta)) {
        Bullet b = {0};
        ASSERT(Bullet_init(&b, bullet_textures, BT_0));
        arrput(*bullets, b);
    }
}

void Player_deinit(Player* this) {
    Entity_deinit((Entity*)this);
}
