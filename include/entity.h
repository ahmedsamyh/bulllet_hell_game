#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <raylib.h>
#include <sprite.h>
#include <commonlib.h>
#include <config.h>

STRUCT(Entity);
ENUM(Entity_Control_Key);

enum Entity_Control_Key {
        ECK_LEFT,
        ECK_RIGHT,
        ECK_DOWN,
        ECK_UP,
        ECK_FIRE,
        ECK_COUNT,
};

struct Entity {
    ENTITY_MEMBERS();
};

bool Entity_init(Entity* this, Texture2D tex, size_t hframes, size_t vframes);
void Entity_physics(Entity* this, float delta);
void Entity_control_physics(Entity* this, float delta);
void Entity_apply_force(Entity* this, Vector2 force);
void Entity_update(Entity* this);
void Entity_draw(Entity* this);
void Entity_control(Entity* this);
void Entity_deinit(Entity* this);

#endif // _ENTITY_H_
