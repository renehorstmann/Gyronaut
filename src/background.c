#include "r/rect.h"
#include "camera.h"
#include "background.h"

static rRect background;

void background_init() {
    r_rect_init(&background, "res/test_bg.png", &camera_vp.m00);
    background.pose[0][0] = background.pose[1][1] = 200;
    r_rect_update(&background, R_BASIC_RECT_UPDATE_XY);
}

void background_render() {
    r_rect_render(&background);
}

