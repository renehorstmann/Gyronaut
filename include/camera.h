#ifndef GYRONAUT_CAMERA_H
#define GYRONAUT_CAMERA_H

#include "cglm/struct.h"

extern int camera_wnd_size[2];
extern mat4s camera_v;
extern mat4s camera_v_inv;
extern mat4s camera_p;
extern mat4s camera_p_inv;
extern mat4s camera_vp;
//extern mat4s camera_vp_inv;

void camera_init();

void camera_update(int wnd_width, int wnd_height);

void camera_set_pos(float x, float y);

#endif //GYRONAUT_CAMERA_H
