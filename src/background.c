#include "r/single.h"
#include "r/texture.h"
#include "camera.h"
#include "background.h"

static rSingle background;

void background_init() {
    r_single_init(&background, &camera_vp.m00, r_texture_from_file("res/test_bg.png"));
    background.rect.pose[0][0] = background.rect.pose[1][1] = 200;
}

void background_render() {
    r_single_render(&background);
}

