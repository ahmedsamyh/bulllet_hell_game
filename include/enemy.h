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
    float dataf[4];
    Alarm die_alarm; // TMP
};

bool Enemy_init(Enemy* this, Texture2D tex, size_t hframes, size_t vframes);
void Enemy_update(Enemy* this);
void Enemy_fire(Enemy* this, Texture2D* bullet_textures, Bullet** bullets);
void Enemy_draw(Enemy* this, bool debug);
void Enemy_deinit(Enemy* this);

// PATTERNS
PATTERN(default_pattern);
PATTERN(pattern1);
PATTERN(pattern2);

#endif // __ENEMY_H__
