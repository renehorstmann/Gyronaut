#include "r/rect.h"
#include "e/window.h"
#include "e/input.h"
#include "camera.h"


mat4s camera_v;
mat4s camera_v_inv;
mat4s camera_p;
mat4s camera_p_inv;
mat4s camera_vp;
//mat4s camera_vp_inv;

void camera_init() {
    camera_v = glms_mat4_identity();
    camera_v_inv = glms_mat4_identity();
    camera_p = glms_mat4_identity();
    camera_p_inv = glms_mat4_identity();
    camera_vp = glms_mat4_identity();
//    camera_vp_inv = glms_mat4_identity();

    e_input_camera_p_inv_ptr = &camera_p_inv.m00;
}

void camera_update() {
    int wnd_width = e_window_size[0];
    int wnd_height = e_window_size[1];
    
    float width, height;
    if (wnd_width > wnd_height) {
        height = 200;
        width = 200 * wnd_width / wnd_height;
    } else {
        width = 200;
        height = 200 * wnd_height / wnd_width;
    }

    camera_v_inv = glms_mat4_inv(camera_v);

    camera_p = glms_ortho(-width / 2, width / 2, -height / 2, height / 2, -1, 1);
    camera_p_inv = glms_mat4_inv(camera_p);

    camera_vp = glms_mat4_mul(camera_p, camera_v_inv);
//    camera_vp_inv = glms_mat4_inv(camera_vp);
}

void camera_set_pos(float x, float y) {
    r_pose_set_xy(camera_v.raw, x, y);
}

void camera_set_angle(float alpha) {
    r_pose_set_angle(camera_v.raw, alpha);
}
