#include <bullet.h>

bool Bullet_init(Bullet* this, Texture2D* textures, Bullet_type type) {
    Entity_init((Entity*)this, textures[0], 1, 1);
    this->speed = ENTITY_DEFAULT_SPEED;

    Bullet_set_type(this, textures, type);

    return true;
}

void Bullet_set_type(Bullet* this, Texture2D* textures, Bullet_type type) {
    this->type = type;
    ASSERT(arrlenu(textures) <= BT_COUNT);
    switch (this->type) {
        case BT_0: {
                       // TODO: check return
                       Sprite_init(&this->spr, textures[BT_0], 1, 1);
                   } break;
        default: {
                     ASSERT(0 && "Unreachable!");
                 } break;
    }
}

void Bullet_draw(Bullet* this) {
   Entity_draw((Entity*)this);
}

void Bullet_deinit(Bullet* this) {
   Entity_deinit((Entity*)this);
}

