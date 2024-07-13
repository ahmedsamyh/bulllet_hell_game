#include <sprite.h>
#include <assert.h>
#include <stdlib.h>

bool Sprite_init(Sprite* spr, Texture2D texture, size_t hframes, size_t vframes) {
  spr->texture = texture;
  spr->hframes = hframes;
  spr->vframes = vframes;
  spr->pos = (Vector2) {0.f, 0.f};
  spr->width = (float)spr->texture.width;
  spr->height = (float)spr->texture.height;
  spr->scale = (Vector2) {1.f, 1.f};
  spr->tex_rect.width = spr->width / (float)spr->hframes;
  spr->tex_rect.height = spr->height / (float)spr->vframes;
  Sprite_set_hframe(spr, 1);
  Sprite_set_vframe(spr, 0);
  spr->tint = WHITE;

  spr->time_per_frame = SPRITE_DEFAULT_TIME_PER_FRAME;
  spr->accumulated_time = 0.f;
  return true;
}

void Sprite_update_tex_rect(Sprite *spr) {
  spr->tex_rect = (Rectangle) {
    .x = spr->tex_rect.width * (float)spr->hframe,
    .y = spr->tex_rect.height * (float)spr->vframe,
    .width =  spr->tex_rect.width,
    .height = spr->tex_rect.height,
  };
}

void Sprite_set_hframe(Sprite* spr, size_t hframe) {
  if (hframe > spr->hframes-1) hframe = 0;
  spr->hframe = hframe;
  Sprite_update_tex_rect(spr);
}

void Sprite_set_vframe(Sprite* spr, size_t vframe) {
  if (vframe > spr->vframes-1) vframe = 0;
  spr->vframe = vframe;
  Sprite_update_tex_rect(spr);
}

void Sprite_center_origin(Sprite* spr) {
  spr->origin.x = spr->tex_rect.width / 2.f;
  spr->origin.y = spr->tex_rect.height / 2.f;
}

void Sprite_draw(Sprite* spr) {
    Rectangle dest = {
        .x = spr->pos.x,
        .y = spr->pos.y,
        .width  = spr->tex_rect.width * spr->scale.x,
        .height = spr->tex_rect.height * spr->scale.y,
    };
    Vector2 origin = CLITERAL(Vector2) {
        .x = spr->origin.x * spr->scale.x,
        .y = spr->origin.y * spr->scale.y,
    };
    DrawTexturePro(spr->texture, spr->tex_rect, dest, origin, spr->rotation, spr->tint);
    /* DrawTexture(spr->texture, spr->pos.x, spr->pos.y, spr->tint); */
}

void Sprite_animate_hframe(Sprite* spr, float delta) {
  spr->accumulated_time += delta;
  if (spr->accumulated_time >= spr->time_per_frame) {
    spr->accumulated_time -= spr->time_per_frame;
    Sprite_set_hframe(spr, spr->hframe+1);
  }
}

void Sprite_deinit(Sprite* spr) {
  UnloadTexture(spr->texture);
}
