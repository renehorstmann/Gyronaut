#define DEBUG
#include "cglm/struct.h"
#include "r/single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "camera.h"
#include "a_steam.h"
#include "astronaut.h"

const static float ALPHA_SPEED_P = 1;

static rSingle r;

static float speed;
static float alpha;
static float alpha_dest;


static float clamp_rotation(float angle) {
    while(angle < -M_PI)
        angle += 2*M_PI;
    while(angle > M_PI)
        angle -= 2*M_PI;
    return angle;
}


void astronaut_init() {
    a_steam_init();
    
    r_single_init(&r, &camera_vp.m00, r_texture_from_file("res/astronaut.png"));
    
    speed = 15;
    
    u_pose_set_size_angle(r.rect.pose, ASTRONAUT_W, ASTRONAUT_H, 0);
}

void astronaut_update(float dtime) {
    
    // set position and rotation
    float da = clamp_rotation(alpha_dest - alpha);
    
    float angular_speed = da * ALPHA_SPEED_P;
    alpha = clamp_rotation(alpha + angular_speed * dtime);
    
    u_pose_set_angle(r.rect.pose, alpha);
    
//    u_pose_print(r.rect.pose);
	u_pose_shift_xy(r.rect.pose,
	speed * cos(alpha) *dtime, 
	speed * sin(alpha) * dtime);
	
    // check collision


    // set camera position
    camera_set_pos(U_PoseX(r.rect.pose), U_PoseY(r.rect.pose));
    
    
    a_steam_update(dtime, r.rect.pose, da / M_PI);
}

void astronaut_render() {
    a_steam_render();
    r_single_render(&r);
}


void astronaut_rotate(float target_angle) {
    alpha_dest = target_angle;
}

