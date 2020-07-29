#ifndef GYRONAUT_CAMERA_H
#define GYRONAUT_CAMERA_H

const float *camera_get_view();
const float *camera_get_projection();

void camera_init();

void camera_update(int wnd_width, int wnd_height);

#endif //GYRONAUT_CAMERA_H
