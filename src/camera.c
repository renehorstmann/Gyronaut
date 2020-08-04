#define DEBUG

#include "r/r.h"
#include "camera.h"


int camera_wnd_size[2];
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
}

void camera_update(int wnd_width, int wnd_height) {
    camera_wnd_size[0] = wnd_width;
    camera_wnd_size[1] = wnd_height;
    
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
    camera_v.m30 = x;
    camera_v.m31 = y;
}

void camera_set_angle(float alpha) {
    camera_v.m00 = cos(alpha);
    camera_v.m01 = -sin(alpha);
    camera_v.m10 = sin(alpha);
    camera_v.m11 = cos(alpha);
}
