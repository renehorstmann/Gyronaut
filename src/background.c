#include "r/basic_rect.h"
#include "camera.h"
#include "background.h"

static rBasicRect background;

void background_init() {
    r_basic_rect_init(&background, "res/test_bg.png", &camera_vp.m00);
    background.mat[0][0] = background.mat[1][1] = 200;
    r_basic_rect_update(&background, R_BASIC_RECT_UPDATE_XY);
}

void background_render() {
	r_basic_rect_render(&background);
}

