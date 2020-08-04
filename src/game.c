#include "r/basic_rect.h"
#include "camera.h"
#include "input.h"
#include "background.h"
#include "astronaut.h"
#include "meteorite.h"
#include "game.h"



static bool rot_left = false;
static bool rot_right = false;

static void pointer(Pointer_s p, void *ud) {
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

void game_init() {
    input_register_pointer_event(pointer, NULL);
    
    background_init();
    astronaut_init();
    meteorite_init(10);
}

void game_update(float dtime) {
    meteorite_update(dtime);

    static float target = 0;
    if(input_right || rot_left)
        target -= M_PI_2 * dtime;
    if(input_left || rot_right)
        target += M_PI_2 * dtime;

    
    
    // todo: running mean not works for alpha
    // rotation should effect the gyronaut, not the bg in that mode 
    static float ax=0, ay=0;
    ax = ax*0.95f + input_accel[0] *0.05f;
    ay = ay*0.95f + input_accel[1] *0.05f;
    float rot = atan2(ay, ax);
    target = - rot;
    
    
    astronaut_rotate(target);

    astronaut_update(dtime);
    
}

void game_render() {
    background_render();
    meteorite_render();
    astronaut_render();
}
