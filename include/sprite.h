#ifndef _CLOCK_SPRITE_H_
#define _CLOCK_SPRITE_H_

#include <raylib.h>
#include <stdlib.h>

#define SPRITE_DEFAULT_TIME_PER_FRAME 0.25f // seconds

typedef struct {
  Texture2D texture;
  Rectangle tex_rect;
  Vector2 pos;
  float width, height;
  Vector2 origin;
  Vector2 scale;
  bool vflip, hflip;
  size_t vframes, hframes;
  size_t vframe, hframe;
  float time_per_frame; // in seconds
  float accumulated_time;
  Color tint;
} Sprite;

bool Sprite_init(Sprite* spr, Texture tex, size_t hframes, size_t vframes);
void Sprite_update_tex_rect(Sprite *spr);
void Sprite_set_hframe(Sprite* spr, size_t hframe);
void Sprite_set_vframe(Sprite* spr, size_t vframe);
void Sprite_center_origin(Sprite* spr);
void Sprite_draw(Sprite* spr);
void Sprite_animate_hframe(Sprite* spr, float delta);
void Sprite_deinit(Sprite* spr);

#endif /* _CLOCK_SPRITE_H_ */

