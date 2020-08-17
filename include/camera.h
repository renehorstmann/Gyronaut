#ifndef GYRONAUT_CAMERA_H
#define GYRONAUT_CAMERA_H

#include "mathc/types.h"

extern mat44f camera_v;
extern mat44f camera_v_inv;
extern mat44f camera_p;
extern mat44f camera_p_inv;
extern mat44f camera_vp;
//extern mat44f camera_vp_inv;

void camera_init();

void camera_update();

void camera_set_pos(float x, float y);

void camera_set_angle(float alpha);

#endif //GYRONAUT_CAMERA_H
