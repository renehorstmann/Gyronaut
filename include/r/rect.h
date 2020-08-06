#ifndef R_RECT_H
#define R_RECT_H

#include <math.h>
#include "cglm/types.h"

typedef struct rRect_s {
    mat4 pose;
    mat4 uv;
    vec4 color;
} rRect_s;

typedef mat4 r_const_mat4;
#define R_Mat4(pointer) ((float(*)[4]) (pointer))

#define R_PoseX(p) (*(((float *) p)+4*3))
#define R_PoseY(p) (*(((float *) p)+4*3+1))

static float r_pose_get_x(r_const_mat4 p) {
	return R_PoseX(p);
}

static float r_pose_get_y(r_const_mat4 p) {
	return R_PoseY(p);
}

static float r_pose_get_w(r_const_mat4 p) {
	return sqrtf(powf(p[0][0], 2) + powf(p[0][1], 2));
}

static float r_pose_get_h(r_const_mat4 p) {
	return sqrtf(powf(p[1][0], 2) + powf(p[1][1], 2));
}

static float r_pose_get_angle(r_const_mat4 p) {
	return atan2(p[0][1], p[0][0]);
}

static void r_pose_set_xy(mat4 p, float x, float y) {
	R_PoseX(p) = x;
	R_PoseY(p) = y;
}

static void r_pose_set_size_angle(mat4 p, float w, float h, float angle_rad) {
	p[0][0] = cos(angle_rad) * w;
    p[0][1] = sin(angle_rad) * w;
    p[1][0] = -sin(angle_rad) * h;
    p[1][1] = cos(angle_rad) * h;
}

static void r_pose_set_w(mat4 p, float w) {
	float f = w / r_pose_get_w(p);    p[0][0] *= f;
	p[0][1] *= f;
}

static void r_pose_set_h(mat4 p, float h) {
	float f = h / r_pose_get_h(p);
	p[1][0] *= f;
	p[1][1] *= f;
}

static void r_pose_set_size(mat4 p, float w, float h) {
	r_pose_set_w(p, w);
	r_pose_set_h(p, h);
}

static void r_pose_set_angle(mat4 p, float angle_rad) {
	r_pose_set_size_angle(p,
	r_pose_get_w(p),
	r_pose_get_h(p),
	angle_rad);
}

static void r_pose_set(mat4 p, float x, float y, float w, float h, float angle_rad) {
	R_PoseX(p) = x;
	R_PoseY(p) = y;
	r_pose_set_size_angle(p, w, h, angle_rad);
}

static void r_pose_shift_xy(mat4 p, float x, float y) {
    R_PoseX(p) += x;
    R_PoseY(p) += y;	
}

static void r_pose_shift_angle(mat4 p, float angle_rad) {
    r_pose_set_angle(p, r_pose_get_angle(p) + angle_rad);	
}

static void r_pose_shift(mat4 p, float x, float y, float angle_rad) {
	r_pose_shift_xy(p, x, y);
	r_pose_shift_angle(p, angle_rad);
}

static void r_pose_set_left(mat4 p, float l) {
	R_PoseX(p) = l + r_pose_get_w(p) /2;
}

static void r_pose_set_right(mat4 p, float r) {
	R_PoseX(p) = r - r_pose_get_w(p) /2;
}

static void r_pose_set_top(mat4 p, float t) {
	R_PoseY(p) = t - r_pose_get_h(p) /2;
}

static void r_pose_set_bottom(mat4 p, float b) {
	R_PoseY(p) = b + r_pose_get_h(p) /2;
}


#define r_pose_print(p) \
printf("pose: x=%.1f y=%.1f w=%.1f h=%.1f angle_deg=%.1f\n", \
r_pose_get_x((p)), \
r_pose_get_y((p)), \
r_pose_get_w((p)), \
r_pose_get_h((p)), \
r_pose_get_angle((p)) * 180 / M_PI \
)

#endif //R_RECT_H
