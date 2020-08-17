#include "r/single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "camera.h"
#include "background.h"

static rSingle background;

void background_init() {
    r_single_init(&background, &camera_vp.m00, r_texture_from_file("res/test_bg.png"));
    u_pose_set_size(&background.rect.pose, 200, 200);
}

void background_render() {
    r_single_render(&background);
}

