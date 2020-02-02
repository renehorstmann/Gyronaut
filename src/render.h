#ifndef GYRONAUT_RENDER_H
#define GYRONAUT_RENDER_H

#include <SDL.h>
#include <stdbool.h>

static float deg2rad(float deg) {
    return deg * (float) M_PI / 180.0f;
}
static float rad2deg(float rad) {
    return rad * 180.0f / (float) M_PI;
}

void render_init(SDL_Renderer *renderer, int screen_w, int screen_h);

typedef struct {
    float x, y; // mid point
    float w, h;
    float angle;
} rrect;

bool rreect_contains(rreect rect, float x, float y);

typedef struct {
    Uint8 r, g, b, a;
} color;

typedef struct {
    rrect rect;
    SDL_Texture *tex;
    SDL_Rect tex_pos;
    color color;
} renderobject;

void render_objects(renderobject *objects, int n);

#endif //GYRONAUT_RENDER_H
