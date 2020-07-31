#include "render/basic_rect.h"
#include "camera.h"
#include "input.h"
#include "astronaut.h"
#include "game.h"

static rBasicRect background;

void game_init() {
    astronaut_init();
    r_basic_rect_init(&background, "res/test_bg_small_alpha.png", &camera_vp.m00);
    background.mat[0][0] = background.mat[1][1] = 200;
    r_basic_rect_update(&background, R_BASIC_RECT_UPDATE_XY);
}

void game_update(float dtime) {

    static float target = 0;
    if(input_right)
        target -= M_PI_2 * dtime;
    if(input_left)
        target += M_PI_2 * dtime;

    astronaut_rotate(target);

    astronaut_update(dtime);
}

void game_render() {
    r_basic_rect_render(&background);
    astronaut_render();
}
