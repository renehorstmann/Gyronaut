#include "render/basic_rect.h"
#include "camera.h"
#include "input.h"
#include "astronaut.h"
#include "game.h"

static rBasicRect background;

static bool rot_left = false;

static void pointer(Pointer_s p, void *ud) {
	if(p.action == POINTER_DOWN) {
		if(p.x < -75)
		    rot_left = true;
	}
	if(p.action == POINTER_UP)
	    rot_left = false;
}

void game_init() {
    input_register_pointer_event(pointer, NULL);
    
    astronaut_init();
    r_basic_rect_init(&background, "res/test_bg_small_alpha.png", &camera_vp.m00);
    background.mat[0][0] = background.mat[1][1] = 200;
    r_basic_rect_update(&background, R_BASIC_RECT_UPDATE_XY);
}

void game_update(float dtime) {

    static float target = 0;
    if(input_right || rot_left)
        target -= M_PI_2 * dtime;
    if(input_left)
        target += M_PI_2 * dtime;

    astronaut_rotate(target);

    astronaut_update(dtime);
}

void game_render() {
    r_basic_rect_render(&background);
    astronaut_render();
}
