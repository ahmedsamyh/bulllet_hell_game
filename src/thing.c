#include <thing.h>

Thing make_thing(Texture2D tex, Vector2 pos) {
    Thing res = {0};
    res.tex = tex;
    res.pos = pos;
    res.speed = 100.f;
    return res;
}

void update_thing(Thing* this, float delta) {
    if (IsKeyDown(KEY_D)) {
        this->acc.x += this->speed * delta;
    }
    if (IsKeyDown(KEY_A)) {
        this->acc.x -= this->speed * delta;
    }
    if (IsKeyDown(KEY_S)) {
        this->acc.y += this->speed * delta;
    }
    if (IsKeyDown(KEY_W)) {
        this->acc.y -= this->speed * delta;
    }

    this->vel = Vector2Add(this->vel, this->acc);
    this->pos = Vector2Add(this->pos, Vector2Scale(this->vel, delta));
    this->acc = Vector2Scale(this->acc, 0.f);
}

void draw_thing(Thing* this) {
    DrawTextureV(this->tex, this->pos, WHITE);
}

void warp_thing(Thing* this) {
    if (this->pos.x < -this->tex.width) {
        this->pos.x = WIDTH;
    }
    if (this->pos.x > WIDTH) {
        this->pos.x = -this->tex.width;
    }
    if (this->pos.y < -this->tex.height) {
        this->pos.y = HEIGHT;
    }
    if (this->pos.y > HEIGHT) {
        this->pos.y = -this->tex.height;
    }
}
