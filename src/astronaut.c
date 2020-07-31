#define DEBUG
#include "cglm/cglm.h"
#include "render/basic_rect.h"
#include "camera.h"


static rBasicRect rect;
static float scale = 20;


static void astronaut_set_angle(float alpha) {
    rect.mat[0][0] = cos(alpha) * scale;
    rect.mat[0][1] = sin(alpha) * scale;
    rect.mat[1][0] = -sin(alpha) * scale;
    rect.mat[1][1] = cos(alpha) * scale;
}

void astronaut_init() {
    r_basic_rect_init(&rect, "res/test_astronaut.png", camera_get_vp());
}

void astronaut_update(float dtime) {
    static float alpha = 0;
    alpha -= M_PI_2 * dtime;
    astronaut_set_angle(alpha);
    rect.mat[2][0] += 10 * dtime;
    r_basic_rect_update(&rect, R_BASIC_RECT_UPDATE_XY);
}

void astronaut_render() {
    r_basic_rect_render(&rect);
}

