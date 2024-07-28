#ifndef __SHOT_H__
#define __SHOT_H__

#include <entity.h>

STRUCT(Shot);

struct Shot {
    MOVING_OBJECT_MEMBERS();
};

bool Shot_init(Shot* this, Texture2D texture);
void Shot_update(Shot* this);
void Shot_draw(Shot* this, bool debug);
void Shot_set_speed(Shot* this, float min, float max, float curr, float delta);
void Shot_deinit(Shot* this);

#endif // __SHOT_H__
