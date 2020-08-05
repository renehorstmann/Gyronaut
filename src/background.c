#include "r/rect.h"
#include "r/texture.h"
#include "camera.h"
#include "background.h"

static rRect background;

void background_init() {
    r_rect_init(&background, &camera_vp.m00, r_texture_from_file("res/test_bg.png"));
    background.rect.pose[0][0] = background.rect.pose[1][1] = 200;
    r_rect_update(&background);
}

void background_render() {
    r_rect_render(&background);
}

