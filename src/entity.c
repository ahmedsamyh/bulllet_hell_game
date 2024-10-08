#include <entity.h>
#include <raymath.h>
#include <momomath.h>

bool Entity_init(Entity* this, Texture2D tex, size_t hframes, size_t vframes) {
    if (!Sprite_init(&this->spr, tex, hframes, vframes)) {
       return false;
    }
    Sprite_center_origin(&this->spr);
    this->speed = ENTITY_DEFAULT_SPEED;
    this->spawning = true;
    this->spr.scale = CLITERAL(Vector2) {2.f, 2.f};
    this->spr.tint.a = 0.f;

    this->hitbox = 8.f; // TODO: hardcode

    Entity_init_health(this, 10.f);
    this->attack_points = 1.f;

    return true;
}

void Entity_physics(Entity* this) {
    float delta = GetFrameTime();
    this->vel = Vector2Add(this->vel, this->acc);
    this->pos = Vector2Add(this->pos, Vector2Scale(this->vel, delta));
    this->acc = Vector2Scale(this->acc, 0.f);
}

void Entity_control_physics(Entity* this) {
    float delta = GetFrameTime();
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

void Entity_damage(Entity* this, float attack_points) {
    this->health -= attack_points;
    if (this->health <= 0.f) {
        this->despawning = true;
    }
}

void Entity_draw(Entity* this, bool debug) {
    this->spr.pos = this->pos;
    Sprite_draw(&this->spr);

    if (debug) {
        DrawCircleV(this->pos, this->hitbox, ColorAlpha(RED, 0.5f));
    }
}

void Entity_spawn(Entity* this) {
    ASSERT(!this->spawned);
    float scl = this->spr.scale.x;
    scl -= (scl - 1.f) * GetFrameTime() * 10.f;
    uint8 a = (uint8)(map(scl, 2.f, 1.f, 0.f, 1.f) * 255.f);
    this->spr.tint.a = a;
    this->spr.scale = CLITERAL(Vector2) {scl, scl};
    if (fabsf(scl - 1.f) < 0.01f) {
        this->spawned = true;
        this->spawning = false;
    }
}

void Entity_despawn(Entity* this) {
    ASSERT(!this->despawned);
    float scl = this->spr.scale.x;
    scl -= (scl - 2.f) * GetFrameTime() * 10.f;
    uint8 a = (uint8)(map(scl, 1.f, 2.f, 1.f, 0.f) * 255.f);
    this->spr.tint.a = a;
    this->spr.scale = CLITERAL(Vector2) {scl, scl};
    if (fabsf(scl - 2.f) <= 0.01f) {
        this->despawned = true;
        this->despawning = false;
    }
}

bool Entity_collide(Entity* this, Entity* other) {
    if (!this->spawned || this->spawning || this->despawning || this->despawned ||
        !this->spawned || this->spawning || this->despawning || this->despawned) return false;
    // TODO: optimize?
    for (size_t i = 0; i < arrlenu(this->collide_masks); ++i) {
        for (size_t j = 0; j < arrlenu(other->collide_ids); ++j) {
            if (this->collide_masks[i] == other->collide_ids[j]) {
                return CheckCollisionCircles(this->pos, this->hitbox, other->pos, other->hitbox);
            }
        }
    }
    return false;
}

void Entity_init_health(Entity* this, float max_health) {
    this->health = max_health;
    this->max_health = max_health;
}

void Entity_deinit(Entity* this) {
    Sprite_deinit(&this->spr);
    arrfree(this->collide_masks);
    arrfree(this->collide_ids);
}
