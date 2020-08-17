#include "mathc/mathc.h"
#include "r/rect.h"
#include "u/pose.h"
#include "e/window.h"
#include "e/input.h"
#include "camera.h"


mat44f camera_v;
mat44f camera_v_inv;
mat44f camera_p;
mat44f camera_p_inv;
mat44f camera_vp;
//mat4s camera_vp_inv;

void camera_init() {
    camera_v = mat44f_eye();
    camera_v_inv = mat44f_eye();
    camera_p = mat44f_eye();
    camera_p_inv = mat44f_eye();
    camera_vp = mat44f_eye();
//    camera_vp_inv = mat44f_eye();

    e_input_camera_p_inv_ptr = &camera_p_inv;
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

    camera_v_inv = mat_invert(camera_v);

    camera_p = u_pose_ortho(-width / 2, width / 2, -height / 2, height / 2, -1, 1);
    camera_p_inv = mat_invert(camera_p);

    camera_vp = mat_mul_mat(camera_p, camera_v_inv);
//    camera_vp_inv = mat_invert(camera_vp);
}

void camera_set_pos(float x, float y) {
    u_pose_set_xy(&camera_v, x, y);
}

void camera_set_angle(float alpha) {
    u_pose_set_angle(&camera_v, alpha);
}
