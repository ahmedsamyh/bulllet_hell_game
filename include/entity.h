#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <raylib.h>
#include <sprite.h>
#include <commonlib.h>

STRUCT(Entity);

#define ENTITY_DEFAULT_SPEED 100.f

struct Entity {
    ENUM(Entity_Control_Key);
    enum Entity_Control_Key {
        ECK_LEFT,
        ECK_RIGHT,
        ECK_DOWN,
        ECK_UP,
        ECK_COUNT,
    };
    Entity_Control_Key keys[ECK_COUNT];
    Vector2 pos, vel, acc;
    float speed;
    Sprite spr;
};

bool Entity_init(Entity* this, Texture2D tex, size_t hframes, size_t vframes);
void Entity_physics(Entity* this, float delta);
void Entity_update(Entity* this);
void Entity_draw(Entity* this);
void Entity_control(Entity* this);
void Entity_deinit(Entity* this);

#endif // _ENTITY_H_
