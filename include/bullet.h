#ifndef __BULLET_H__
#define __BULLET_H__

#include <commonlib.h>
#include <raylib.h>
#include <entity.h>

STRUCT(Bullet);
ENUM(Bullet_type);

enum Bullet_type {
    BT_0,
    BT_COUNT
};

struct Bullet {
    ENTITY_MEMBERS();
    float max_speed, min_speed;
    float speed_delta;
    float angle;
    Bullet_type type;
};

// param:textures is dynamic-array
bool Bullet_init(Bullet* this, Texture2D* textures, Bullet_type type);
void Bullet_set_type(Bullet* this, Texture2D* textures, Bullet_type type);
void Bullet_update(Bullet* this);
void Bullet_draw(Bullet* this);
void Bullet_set_speed(Bullet* this, float min, float max, float curr, float delta);
void Bullet_deinit(Bullet* this);

#endif // __BULLET_H__
