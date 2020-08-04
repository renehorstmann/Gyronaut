#define DEBUG
#include "cglm/struct.h"
#include "r/basic_rect.h"
#include "camera.h"
#include "input.h"

const static float ALPHA_SPEED_P = 1;

static rBasicRect rect;
static float scale = 20;

static float speed;
static float alpha;
static float alpha_dest;

static void set_angle(float alpha_rad) {
    rect.mat[0][0] = cos(alpha_rad) * scale;
    rect.mat[0][1] = sin(alpha_rad) * scale;
    rect.mat[1][0] = -sin(alpha_rad) * scale;
    rect.mat[1][1] = cos(alpha_rad) * scale;
}

void astronaut_init() {
    r_basic_rect_init(&rect, "res/test_astronaut.png", &camera_vp.m00);
    speed = 10;
}

void astronaut_update(float dtime) {
    // set position and rotation
    float angular_speed = (alpha_dest - alpha) * ALPHA_SPEED_P;
    alpha += angular_speed * dtime;
    set_angle(alpha);
    r_basic_rect_update(&rect, R_BASIC_RECT_UPDATE_XY);

    rect.mat[2][0] += speed * cos(alpha) * dtime;
    rect.mat[2][1] += speed * sin(alpha) * dtime;

    // check collision


    // set camera position
    camera_set_pos(rect.mat[2][0], rect.mat[2][1]);
    camera_set_angle(-alpha_dest);
}

void astronaut_render() {
    r_basic_rect_render(&rect);
}


void astronaut_rotate(float target_angle) {
    alpha_dest = target_angle;
}

