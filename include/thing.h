#ifndef _THING_H_
#define _THING_H_

#include <raylib.h>
#include <raymath.h>
#include <config.h>

typedef struct {
    Vector2 pos, vel, acc;
    float speed;
    Texture2D tex;
} Thing;

Thing make_thing(Texture2D tex, Vector2 pos);
void update_thing(Thing* this, float delta);
void draw_thing(Thing* this);
void warp_thing(Thing* this);

#endif // _THING_H_
