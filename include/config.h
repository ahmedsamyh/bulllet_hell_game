#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <timer.h>
#include <commonlib.h>

#define WIDTH 1280
#define HEIGHT 960

#define TILE_SIZE 32
#define COLS (WIDTH/TILE_SIZE)
#define ROWS (HEIGHT/TILE_SIZE)

#define ENTITY_DEFAULT_SPEED 200.f
#define ENTITY_MEMBERS() \
    Vector2 pos, vel, acc, dir;\
    float speed;\
    Sprite spr;\
    bool despawned, despawning_move, despawning;\
    bool spawned, spawning_move, spawning;\
    Alarm fire_alarm;\
    float hitbox;\
    int* collide_masks;\
    int* collide_ids;\
    float health,  max_health;\
    float attack_points

#define PLAYER_DEFAULT_SPEED 400.f
#define PLAYER_FIRE_RATE 0.075f
#define PLAYER_HITBOX 2.f
#define PLAYER_SHOT_MIN_SPEED   250.f
#define PLAYER_SHOT_MAX_SPEED   750.f
#define PLAYER_SHOT_SPEED       750.f
#define PLAYER_SHOT_SPEED_DELTA -200.f

#define PLAYER_FIRE_KEY KEY_Z
#define PLAYER_RIGHT_KEY KEY_RIGHT
#define PLAYER_LEFT_KEY KEY_LEFT
#define PLAYER_UP_KEY   KEY_UP
#define PLAYER_DOWN_KEY KEY_DOWN
#define PLAYER_FIRE_KEY KEY_Z
#define PLAYER_ALT_KEY  KEY_LEFT_SHIFT
#define PLAYER_ANGLE_KEY KEY_X

#define BULLET_DEFAULT_MIN_SPEED 0.f
#define BULLET_DEFAULT_MAX_SPEED 500.f

ENUM(Collide_id);
enum Collide_id {
    CID_PLAYER,
    CID_PLAYER_BULLET,
    CID_ENEMY,
    CID_ENEMY_BULLET,
    CID_COUNT
};

#define PATTERN(name) void name(Enemy* this,Texture2D* bullet_textures, Bullet** bullets)

#define MOVING_OBJECT_MEMBERS() \
    ENTITY_MEMBERS();\
    float max_speed, min_speed;\
    float speed_delta;\
    float angle;

#endif // _CONFIG_H_
