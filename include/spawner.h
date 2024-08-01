#ifndef __SPAWNER_H__
#define __SPAWNER_H__

#include <raylib.h>
#include <commonlib.h>
#include <sprite.h>

STRUCT(Spawner);
STRUCT(Bullet);
STRUCT(Enemy);

struct Spawner {
    float time; // seconds
    Vector2 pos;
    Bullet** bullets;
    Enemy** enemies;
    bool spawned;
    Sprite spr;
};

bool Spawner_init(Spawner* this, Texture2D tex, Bullet** bullets, Enemy** enemies, float time, Vector2 pos);
void Spawner_spawn(Spawner* this, float play_time);
void Spawner_draw(Spawner* this);

#endif // __SPAWNER_H__
