#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <entity.h>
#include <bullet.h>
#include <commonlib.h>

STRUCT(Enemy);

struct Enemy {
    ENTITY_MEMBERS();
    size_t fire_count, fire_count_max;
    void(*pattern)(Enemy*, Texture2D*, Bullet**);
    size_t bullet_count;
};

bool Enemy_init(Enemy* this, Texture2D tex, size_t hframes, size_t vframes);
void Enemy_update(Enemy* this);
void Enemy_draw(Enemy* this);
void default_pattern(Enemy* this,Texture2D* bullet_textures, Bullet** bullets);
void Enemy_fire(Enemy* this, Texture2D* bullet_textures, Bullet** bullets);
void Enemy_deinit(Enemy* this);

#endif // __ENEMY_H__
