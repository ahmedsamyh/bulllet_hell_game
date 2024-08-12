#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <entity.h>
#include <shot.h>
#include <timer.h>

STRUCT(Player);

struct Player {
    ENTITY_MEMBERS();
    bool alt;
    float alt_speed;
    bool angling;
    float angle_delta;
    float angle; // in degrees
};

bool Player_init(Player* this, Texture2D tex, size_t hframes, size_t vframes);
void Player_update(Player* this);
void Player_draw(Player* this, bool debug);
void Player_control(Player* this);
void Player_angle(Player* this);
void Player_fire(Player* this, Texture2D shot_texture, Shot** shots);
void Player_control_physics(Player* this);
void Player_deinit(Player* this);

#endif // __PLAYER_H__
