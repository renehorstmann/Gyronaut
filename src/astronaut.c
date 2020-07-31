#define DEBUG
#include "cglm/cglm.h"
#include "render/basic_rect.h"
#include "camera.h"
#include "inputs.h"

static rBasicRect rect;
static float scale = 20;


static void astronaut_set_angle(float alpha) {
    rect.mat[0][0] = cos(alpha) * scale;
    rect.mat[0][1] = sin(alpha) * scale;
    rect.mat[1][0] = -sin(alpha) * scale;
    rect.mat[1][1] = cos(alpha) * scale;
}


static void pointer_cb(Pointer_s p, void *ud) {
	rect.mat[2][0] = p.x;
	rect.mat[2][1] = p.y;
}


void astronaut_init() {
    r_basic_rect_init(&rect, "res/test_astronaut.png", camera_get_vp());
    
    input_register_pointer_event(pointer_cb, NULL);
}

void astronaut_update(float dtime) {
    static float alpha = 0;
    alpha -= M_PI_2 * dtime;
    astronaut_set_angle(alpha);
    rect.mat[2][0] += 10 * dtime;
    r_basic_rect_update(&rect, R_BASIC_RECT_UPDATE_XY);
}

void astronaut_render() {
    r_basic_rect_render(&rect);
}


void astronaut_rotate(float angular_speed) {
    // todo
}

