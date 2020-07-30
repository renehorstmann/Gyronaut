#ifndef GYRONAUT_CAMERA_H
#define GYRONAUT_CAMERA_H


void camera_init();

void camera_update(int wnd_width, int wnd_height);

// mat4
const float *camera_get_v();

const float *camera_get_p();

const float *camera_get_vp();

void camera_set_pos(float x, float y);

#endif //GYRONAUT_CAMERA_H
