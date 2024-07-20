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
    Bullet_type type;
};

// param:textures is dynamic-array
bool Bullet_init(Bullet* this, Texture2D* textures, Bullet_type type);
void Bullet_set_type(Bullet* this, Texture2D* textures, Bullet_type type);
void Bullet_draw(Bullet* this);
void Bullet_deinit(Bullet* this);

#endif // __BULLET_H__
