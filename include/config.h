#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <timer.h>
#include <commonlib.h>

#define WIDTH 1280
#define HEIGHT 960

#define ENTITY_DEFAULT_SPEED 200.f
#define ENTITY_MEMBERS() \
    KeyboardKey keys[ECK_COUNT];\
    Vector2 pos, vel, acc, dir;\
    float speed;\
    Sprite spr;\
    bool despawned, despawning;\
    bool spawned, spawning;\
    Alarm fire_alarm;\
    float hitbox;\
    int* collide_masks;\
    int* collide_ids

#define PLAYER_DEFAULT_SPEED 200.f
#define PLAYER_FIRE_RATE 0.01f
#define PLAYER_HITBOX 6.f

#define BULLET_DEFAULT_MIN_SPEED 0.f
#define BULLET_DEFAULT_MAX_SPEED 500.f

ENUM(Collide_id);
enum Collide_id {
    CID_PLAYER,
    CID_ENEMY_BULLET,
    CID_COUNT
};

#define PATTERN(name) void name(Enemy* this,Texture2D* bullet_textures, Bullet** bullets)

#endif // _CONFIG_H_
