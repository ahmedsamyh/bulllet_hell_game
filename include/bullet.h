#ifndef __BULLET_H__
#define __BULLET_H__

#include <commonlib.h>
#include <raylib.h>
#include <entity.h>

STRUCT(Bullet);
ENUM(Bullet_type);
ENUM(Bullet_color);

enum Bullet_type {
    BT_0,
    BT_COUNT
};

enum Bullet_color {
    BC_CYAN,
    BC_GREEN,
    BC_ORANGE,
    BC_YELLOW,
    BC_PINK,
    BC_GRAY,
    BC_COUNT
};

struct Bullet {
    MOVING_OBJECT_MEMBERS();
    Bullet_type type;
    Bullet_color color;

};

// param:textures is dynamic-array
bool Bullet_init(Bullet* this, Texture2D* textures, Bullet_type type, Bullet_color color);
void Bullet_set_type(Bullet* this, Texture2D* textures, Bullet_type type, Bullet_color color);
void Bullet_update(Bullet* this);
void Bullet_draw(Bullet* this, bool debug);
void Bullet_set_speed(Bullet* this, float min, float max, float curr, float delta);
void Bullet_deinit(Bullet* this);

#endif // __BULLET_H__
