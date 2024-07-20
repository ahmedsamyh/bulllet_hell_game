#include <entity.h>
#include <raymath.h>

bool Entity_init(Entity* this, Texture2D tex, size_t hframes, size_t vframes) {
   if (!Sprite_init(&this->spr, tex, hframes, vframes)) {
       return false;
   }
   Sprite_center_origin(&this->spr);
   this->speed = ENTITY_DEFAULT_SPEED;

   this->keys[ECK_RIGHT] = KEY_D;
   this->keys[ECK_LEFT]  = KEY_A;
   this->keys[ECK_UP]    = KEY_W;
   this->keys[ECK_DOWN]  = KEY_S;

   return true;
}

void Entity_physics(Entity* this, float delta) {
    this->vel = Vector2Add(this->vel, this->acc);
    this->pos = Vector2Add(this->pos, Vector2Scale(this->vel, delta));
    this->acc = Vector2Scale(this->acc, 0.f);
}

void Entity_control_physics(Entity* this, float delta) {
    this->vel = Vector2Scale(this->dir, this->speed);
    this->pos = Vector2Add(this->pos, Vector2Scale(this->vel, delta));
    this->acc = Vector2Scale(this->acc, 0.f);
}

void Entity_apply_force(Entity* this, Vector2 force) {
    this->acc = Vector2Add(this->acc, force);
}

void Entity_update(Entity* this) {
    (void)this;

}

void Entity_control(Entity* this) {
    Vector2 dir = {0};
    if (IsKeyDown(this->keys[ECK_LEFT])) {
        dir.x--;
    }
    if (IsKeyDown(this->keys[ECK_RIGHT])) {
        dir.x++;
    }
    if (IsKeyDown(this->keys[ECK_UP])) {
        dir.y--;
    }
    if (IsKeyDown(this->keys[ECK_DOWN])) {
        dir.y++;
    }
    dir = Vector2Normalize(dir);
    this->dir = dir;
}

void Entity_draw(Entity* this) {
    this->spr.pos = this->pos;
    Sprite_draw(&this->spr);
}

void Entity_deinit(Entity* this) {
   Sprite_deinit(&this->spr);
}
