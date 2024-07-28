#include <bullet.h>
#include <raymath.h>
#include <momomath.h>

bool Bullet_init(Bullet* this, Texture2D* textures, Bullet_type type, Bullet_color color) {
    Entity_init((Entity*)this, textures[0], 1, 1);

    Bullet_set_speed(this, BULLET_DEFAULT_MIN_SPEED, BULLET_DEFAULT_MAX_SPEED, ENTITY_DEFAULT_SPEED+randomf(-100.f, 100.f), 0.f);
    Bullet_set_type(this, textures, type, color);
    this->spr.scale = CLITERAL(Vector2) {2.f, 2.f};

    this->angle = randomf(0.f, 360.f);
    return true;
}

void Bullet_set_type(Bullet* this, Texture2D* textures, Bullet_type type, Bullet_color color) {
    this->type = type;
    ASSERT(arrlenu(textures) <= BT_COUNT);
    this->color = color;
    switch (this->type) {
        case BT_0: {
                       // TODO: check return
                       Sprite_init(&this->spr, textures[BT_0], BC_COUNT, 1);
                       Sprite_center_origin(&this->spr);
                   } break;
        default: {
                     ASSERT(0 && "Unreachable!");
                 } break;
    }
    Sprite_set_hframe(&this->spr, (int)this->color);

}

void Bullet_update(Bullet* this) {
    if (this->spawning && !this->spawned) {
        Entity_spawn((Entity*)this);
    }
    if (this->spawned && !this->spawning && !this->despawned && !this->despawning) {
        float delta = GetFrameTime();
        this->dir = vector2_from_degrees(this->angle);
        this->speed += this->speed_delta * delta;
        this->speed = Clamp(this->speed, this->min_speed, this->max_speed);
        this->vel = Vector2Scale(this->dir, this->speed);
        this->pos = Vector2Add(this->pos, Vector2Scale(this->vel, delta));
    }
    if (this->despawning && !this->despawned) {
        Entity_despawn((Entity*)this);
    }
}

void Bullet_draw(Bullet* this, bool debug) {
   Entity_draw((Entity*)this, debug);
}

void Bullet_deinit(Bullet* this) {
   Entity_deinit((Entity*)this);
}

void Bullet_set_speed(Bullet* this, float min, float max, float curr, float delta) {
    this->speed_delta = delta;
    this->min_speed = min;
    this->max_speed = max;
    this->speed = Clamp(curr, min, max);
}
