#define DEBUG

#include "e/e.h"
#include "r/r.h"
#include "u/u.h"
#include "controller.h"
#include "background.h"
#include "astronaut.h"
#include "meteorite.h"
#include "game.h"

#include "camera.h"






static rText text;


void game_init() {
    u_pseed(1234);
    
    controller_init(0);
    background_init();
    astronaut_init();
    meteorite_init(25);

    r_text_init(&text, &camera_vp.m00, rRED, "FPS: 123456");
    r_text_set_size(&text, 10);
    U_PoseY(text.r.rect.pose) = 50;
    
}

void game_update(float dtime) {
    controller_update(dtime);
    
    meteorite_update(dtime);

    astronaut_update(dtime);
    
    camera_update();
    
    static int cnt = 0;
    if(cnt++ %20 == 0) {	
        char fps[16];
        sprintf(fps, "FPS: %.1f", 1/dtime);
        r_text_set_text(&text, rWHITE, fps);
        u_pose_set_left(text.r.rect.pose, 0);
    }
}

void game_render() {
    background_render();
    meteorite_render();
    astronaut_render();
    
    r_text_render(&text);
}
