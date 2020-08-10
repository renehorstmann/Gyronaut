#define DEBUG

#include "cglm/cglm.h"
#include "utilc/assume.h"
#include "e/input.h"
#include "camera.h"
#include "astronaut.h"
#include "controller.h"


static bool rot_left = false;
static bool rot_right = false;

static void pointer(ePointer_s p, void *ud) {
#ifdef R_GLES
    if(rot_left) {
        if(p.action == POINTER_UP || p.x > -75)
            rot_left = false;
    } else {
        if(p.action != POINTER_UP && p.x < -75)
            rot_left = true;
    }
    if(rot_right) {
        if(p.action == POINTER_UP || p.x < 75)
            rot_right = false;
    } else {
        if(p.action != POINTER_UP && p.x > 75)
            rot_right = true;
    }
#endif
}


/*
void game_update(float dtime) {
    meteorite_update(dtime);

    static float target = 0;
    if(e_input_right || rot_left)
        target -= M_PI_2 * dtime;
    if(e_input_left || rot_right)
        target += M_PI_2 * dtime;

    
    
    // todo: running mean not works for alpha
    // rotation should effect the gyronaut, not the bg in that mode 
    static float ax=0, ay=0;
    ax = ax*0.9f + e_input_accel[0] *0.1f;
    ay = ay*0.9f + e_input_accel[1] *0.1f;
    float rot = atan2(ay, ax) - M_PI/2;
    target = - rot;
    
    
    astronaut_rotate(target);
}
*/

static const float a_mean = 0.9f;


static bool accel;
static float ax, ay;
static float target;

void controller_init(bool use_accel) {
	if(use_accel) {
	    assume(e_input_accel_active, "Accel not available");
	    ax = e_input_accel[0];
	    ay = e_input_accel[1];
	}
	accel = use_accel;
	e_input_register_pointer_event(pointer, NULL);
	
}

void controller_update() {
    if(accel) {
    	ax = ax * a_mean + e_input_accel[0] * (1.0f - a_mean);
    	ay = ay * a_mean + e_input_accel[1] * (1.0f - a_mean);

        float rot = atan2f(ay, ax);
        
        target = rot - M_PI_2;
        
        // todo camera
    } else {
    	
    	// todo
    }
	
	astronaut_rotate(target);
}
