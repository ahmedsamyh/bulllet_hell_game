#include <entity.h>
#include <raymath.h>

bool Entity_init(Entity* this, Texture2D tex, size_t hframes, size_t vframes) {
   if (!Sprite_init(&this->spr, tex, hframes, vframes)) {
       return false;
   }
   Sprite_center_origin(&this->spr);
   this->speed = ENTITY_DEFAULT_SPEED;

   return true;
}

void Entity_physics(Entity* this, float delta) {
    this->vel = Vector2Add(this->vel, this->acc);
    this->pos = Vector2Add(this->pos, Vector2Scale(this->vel, delta));
    this->acc = Vector2Scale(this->acc, 0.f);
}

void Entity_update(Entity* this) {
    (void)this;

}

void Entity_draw(Entity* this) {
    this->spr.pos = this->pos;
    Sprite_draw(&this->spr);
}

void Entity_deinit(Entity* this) {
   Sprite_deinit(&this->spr);
}
