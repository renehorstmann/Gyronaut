#define DEBUG

#include "r/r.h"
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


static rText text;
static rParticle particle;
static float game_time;

static float frand() {
	return (float) rand() / RAND_MAX;
}

void game_init() {
    input_register_pointer_event(pointer, NULL);
    
    background_init();
    astronaut_init();
    meteorite_init(1000);

    r_text_init(&text, &camera_vp.m00, rRED, "FPS: 123456");
    r_text_set_size(&text, 10);
    R_PoseY(text.r.rect.pose) = 50;
    
    int pnum = 10000;

    r_particle_init(&particle, pnum, &camera_vp.m00, r_texture_from_file("res/meteorite_test.png"));
    for(int i=0; i<pnum; i++) {
        r_pose_set_size(particle.rects[i].pose, 5, 5);
        //R_PoseX(particle.rects[i].pose) = -10 + 20 * frand();
        //R_PoseY(particle.rects[i].pose) = -10 + 20 * frand();

        glm_vec4_copy((vec4){frand(), frand(), frand(), 1}, particle.rects[i].color);
        glm_vec4_copy((vec4) {-1+2*frand(), -1+2*frand(), -1+2*frand(), -0.1}, particle.rects[i].color_speed);

        //glm_vec2_copy((vec2) {0.1, 0.05}, particle.rects[i].uv_step);
        //particle.rects[i].uv_time = 0.2;

        particle.rects[i].speed[1] = -20 + 40 * frand();
        particle.rects[i].speed[0] = -20 + 40 * frand();
        particle.rects[i].acc[0] = -10 + 20 * frand();
        particle.rects[i].acc[1] = -10 + 20 * frand();
        glm_vec4_copy((vec4){0, 0, 1, M_PI*frand()}, particle.rects[i].axis_angle);
    }

    r_particle_update(&particle);
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
    ax = ax*0.9f + input_accel[0] *0.1f;
    ay = ay*0.9f + input_accel[1] *0.1f;
    float rot = atan2(ay, ax) - M_PI/2;
    target = - rot;
    
    
    astronaut_rotate(target);

    astronaut_update(dtime);

    static int cnt = 0;
    if(cnt++ % 20 == 0) {
        char msg[64];
        sprintf(msg, "FPS: %f", 1.0f / dtime);
        r_text_set_text(&text, rRED, msg);
        r_pose_set_left(text.r.rect.pose, -50);
    }

    game_time += dtime;
}

void game_render() {
    background_render();
    meteorite_render();
    astronaut_render();
    

    r_particle_render(&particle, fabs(sin(game_time/4)*8));
    
    r_text_render(&text);
}
