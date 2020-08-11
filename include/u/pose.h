#ifndef U_POSE_H
#define U_POSE_H

#include <math.h>
#include "cglm/types.h"


#define U_Mat4(pointer) ((float(*)[4]) (pointer))

#define U_PoseX(p) (*(((float *) p)+4*3))
#define U_PoseY(p) (*(((float *) p)+4*3+1))

static float u_pose_get_x(/*const*/ mat4 p) {
	return U_PoseX(p);
}

static float u_pose_get_y(/*const*/ mat4 p) {
	return U_PoseY(p);
}

static float u_pose_get_w(/*const*/ mat4 p) {
	return sqrtf(powf(p[0][0], 2) + powf(p[0][1], 2));
}

static float u_pose_get_h(/*const*/ mat4 p) {
	return sqrtf(powf(p[1][0], 2) + powf(p[1][1], 2));
}

static float u_pose_get_angle(/*const*/ mat4 p) {
	return atan2(p[0][1], p[0][0]);
}

static void u_pose_set_xy(mat4 p, float x, float y) {
	U_PoseX(p) = x;
	U_PoseY(p) = y;
}

static void u_pose_set_size_angle(mat4 p, float w, float h, float angle_rad) {
	p[0][0] = cos(angle_rad) * w;
    p[0][1] = sin(angle_rad) * w;
    p[1][0] = -sin(angle_rad) * h;
    p[1][1] = cos(angle_rad) * h;
}

static void u_pose_set_w(mat4 p, float w) {
	float f = w / u_pose_get_w(p);    
	p[0][0] *= f;
	p[0][1] *= f;
}

static void u_pose_set_h(mat4 p, float h) {
	float f = h / u_pose_get_h(p);
	p[1][0] *= f;
	p[1][1] *= f;
}

static void u_pose_set_size(mat4 p, float w, float h) {
	u_pose_set_w(p, w);
	u_pose_set_h(p, h);
}

static void u_pose_set_angle(mat4 p, float angle_rad) {
	u_pose_set_size_angle(p,
	u_pose_get_w(p),
	u_pose_get_h(p),
	angle_rad);
}

static void u_pose_set(mat4 p, float x, float y, float w, float h, float angle_rad) {
	U_PoseX(p) = x;
	U_PoseY(p) = y;
	u_pose_set_size_angle(p, w, h, angle_rad);
}

static void u_pose_shift_xy(mat4 p, float x, float y) {
    U_PoseX(p) += x;
    U_PoseY(p) += y;	
}

static void u_pose_shift_angle(mat4 p, float angle_rad) {
    u_pose_set_angle(p, u_pose_get_angle(p) + angle_rad);	
}

static void u_pose_shift(mat4 p, float x, float y, float angle_rad) {
	u_pose_shift_xy(p, x, y);
	u_pose_shift_angle(p, angle_rad);
}

static void u_pose_set_left(mat4 p, float l) {
	U_PoseX(p) = l + u_pose_get_w(p) /2;
}

static void u_pose_set_right(mat4 p, float r) {
	U_PoseX(p) = r - u_pose_get_w(p) /2;
}

static void u_pose_set_top(mat4 p, float t) {
	U_PoseY(p) = t - u_pose_get_h(p) /2;
}

static void u_pose_set_bottom(mat4 p, float b) {
	U_PoseY(p) = b + u_pose_get_h(p) /2;
}


#define u_pose_print(p) \
printf("pose: x=%.1f y=%.1f w=%.1f h=%.1f angle_deg=%.1f\n", \
u_pose_get_x((p)), \
u_pose_get_y((p)), \
u_pose_get_w((p)), \
u_pose_get_h((p)), \
u_pose_get_angle((p)) * 180 / M_PI \
)

#endif //U_POSE_H
