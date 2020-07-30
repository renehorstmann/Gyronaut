#define DEBUG

#include "cglm/cglm.h"
#include "render/render.h"
#include "camera.h"


static mat4 view;
static mat4 projection;
static mat4 view_projection;

void camera_init() {
    glm_mat4_identity(view);
    glm_mat4_identity(projection);
    glm_mat4_identity(view_projection);
}

void camera_update(int wnd_width, int wnd_height) {
    float width, height;
    if (wnd_width > wnd_height) {
        height = 200;
        width = 200 * wnd_width / wnd_height;
    } else {
        width = 200;
        height = 200 * wnd_height / wnd_width;
    }

    glm_ortho(-width / 2, width / 2, -height / 2, height / 2, -1, 1, projection);

    mat4 view_inv;
    glm_mat4_inv(view, view_inv);
    glm_mat4_mul(projection, view_inv, view_projection);
}


const float *camera_get_v() {
    return &view[0][0];
}

const float *camera_get_p() {
    return &projection[0][0];
}

const float *camera_get_vp() {
    return &view_projection[0][0];
}

void camera_set_pos(float x, float y) {
    view[3][0] = x;
    view[3][1] = y;
}
