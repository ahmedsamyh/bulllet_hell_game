#ifndef _CONFIG_H_
#define _CONFIG_H_

#define WIDTH 1280
#define HEIGHT 960

#define ENTITY_DEFAULT_SPEED 200.f
#define ENTITY_MEMBERS() \
    KeyboardKey keys[ECK_COUNT];\
    Vector2 pos, vel, acc, dir;\
    float speed;\
    Sprite spr;\
    bool despawned, despawning;\
    bool spawned, spawning

#define PLAYER_DEFAULT_SPEED 200.f
#define PLAYER_FIRE_RATE 0.01f

#define BULLET_DEFAULT_MIN_SPEED 0.f
#define BULLET_DEFAULT_MAX_SPEED 500.f

#endif // _CONFIG_H_
