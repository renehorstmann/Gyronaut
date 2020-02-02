#include "render.h"

static SDL_Renderer *renderer;
static int screen_w, screen_h;
static float screen_w_half, screen_h_half;
static float screen_scale;

void render_init(SDL_Renderer *r, int w, int h) {
    renderer = r;
    screen_w = w;
    screen_h = h;
    screen_w_half = (float) w / 2.0f;
    screen_h_half = (float) h / 2.0f;
    screen_scale = screen_h < screen_w ? (float) screen_h / 100.0f : (float) screen_w / 100.0f;
}

static SDL_Rect rrect_to_SDL_Rect(struct rrect rect) {
    SDL_Rect res;
    res.x = (int) (screen_w_half + rect.x * screen_scale);
    res.y = (int) (screen_h_half + rect.y * screen_scale);
    res.w = (int) (rect.w * screen_scale);
    res.h = (int) (rect.h * screen_scale);
    return res;
}

bool rrect_contains(struct rrect rect, float x, float y) {
    float dx = x - rect.x;
    float dy = y - rect.y;

    float alpha = atan2f(dy, dx);
    float hyp = dx / cosf(alpha);

    float rotated_x = hyp * cosf(alpha - rect.angle);
    float rotated_y = hyp * sinf(alpha - rect.angle);

    return rotated_x < rect.w / 2 && rotated_x > -rect.w / 2
           && rotated_y < rect.h / 2 && rotated_y > -rect.h / 2;
}

void render_objects(renderobject *objects, int n) {
    for(int i=0; i<n; i++) {
        SDL_Rect rect = rrect_to_SDL_Rect(objects[i].rect);

        SDL_SetRenderDrawColor(renderer,
                objects[i].color.r,
                objects[i].color.g,
                objects[i].color.b,
                objects[i].color.a);

        SDL_RenderCopyEx(renderer,
                         objects[i].tex,
                         &objects[i].tex_pos,
                         &rect,
                         rad2deg(objects[i].rect.angle),
                         NULL,
                         SDL_FLIP_NONE);
    }
}

