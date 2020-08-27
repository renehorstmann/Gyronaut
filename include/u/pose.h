#ifndef U_POSE_H
#define U_POSE_H

#include <math.h>
#include "mathc/types.h"


static float u_pose_get_x(mat4 p) {
	return p.m30;
}

static float u_pose_get_y(mat4 p) {
	return p.m31;
}

static float u_pose_get_w(mat4 p) {
	return sqrtf(powf(p.m00, 2) + powf(p.m01, 2));
}

static float u_pose_get_h(mat4 p) {
	return sqrtf(powf(p.m10, 2) + powf(p.m11, 2));
}

static float u_pose_get_angle(mat4 p) {
	return atan2(p.m01, p.m00);
}

static void u_pose_set_x(mat4 *p, float x) {
    p->m30 = x;
}

static void u_pose_set_y(mat4 *p, float y) {
    p->m31 = y;
}

static void u_pose_set_xy(mat4 *p, float x, float y) {
	u_pose_set_x(p, x);
	u_pose_set_y(p, y);
}

static void u_pose_set_size_angle(mat4 *p, float w, float h, float angle_rad) {
	p->m00 = cos(angle_rad) * w;
    p->m01 = sin(angle_rad) * w;
    p->m10 = -sin(angle_rad) * h;
    p->m11 = cos(angle_rad) * h;
}

static void u_pose_set_w(mat4 *p, float w) {
	float f = w / u_pose_get_w(*p);
	p->m00 *= f;
	p->m01 *= f;
}

static void u_pose_set_h(mat4 *p, float h) {
	float f = h / u_pose_get_h(*p);
	p->m10 *= f;
	p->m11 *= f;
}

static void u_pose_set_size(mat4 *p, float w, float h) {
	u_pose_set_w(p, w);
	u_pose_set_h(p, h);
}

static void u_pose_set_angle(mat4 *p, float angle_rad) {
	u_pose_set_size_angle(p,
	u_pose_get_w(*p),
	u_pose_get_h(*p),
	angle_rad);
}

static void u_pose_set(mat4 *p, float x, float y, float w, float h, float angle_rad) {
	u_pose_set_xy(p, x, y);
	u_pose_set_size_angle(p, w, h, angle_rad);
}

static void u_pose_shift_x(mat4 *p, float x) {
    p->m30 += x;
}

static void u_pose_shift_y(mat4 *p, float y) {
    p->m31 += y;
}

static void u_pose_shift_xy(mat4 *p, float x, float y) {
    u_pose_shift_x(p, x);
    u_pose_shift_y(p, y);
}

static void u_pose_shift_angle(mat4 *p, float angle_rad) {
    u_pose_set_angle(p, u_pose_get_angle(*p) + angle_rad);
}

static void u_pose_shift(mat4 *p, float x, float y, float angle_rad) {
	u_pose_shift_xy(p, x, y);
	u_pose_shift_angle(p, angle_rad);
}

static void u_pose_set_left(mat4 *p, float l) {
	p->m30 = l + u_pose_get_w(*p) /2;
}

static void u_pose_set_right(mat4 *p, float r) {
	p->m30 = r - u_pose_get_w(*p) /2;
}

static void u_pose_set_top(mat4 *p, float t) {
    p->m31 = t - u_pose_get_h(*p) /2;
}

static void u_pose_set_bottom(mat4 *p, float b) {
	p->m31 = b + u_pose_get_h(*p) /2;
}

static mat4 u_pose_ortho(float left,    float right,
                          float bottom,  float top,
                          float nearVal, float farVal) {
    // from cglm/cam.h/glm_ortho
    float rl, tb, fn;

    mat4 dest = MAT4_INIT_ZERO;

    rl = 1.0f / (right  - left);
    tb = 1.0f / (top    - bottom);
    fn =-1.0f / (farVal - nearVal);

    dest.m[0][0] = 2.0f * rl;
    dest.m[1][1] = 2.0f * tb;
    dest.m[2][2] = 2.0f * fn;
    dest.m[3][0] =-(right  + left)    * rl;
    dest.m[3][1] =-(top    + bottom)  * tb;
    dest.m[3][2] = (farVal + nearVal) * fn;
    dest.m[3][3] = 1.0f;

    return dest;
}

#endif //U_POSE_H
