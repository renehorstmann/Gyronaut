#define DEBUG
#include "cglm/struct.h"
#include "r/single.h"
#include "r/texture.h"
#include "camera.h"

const static float ALPHA_SPEED_P = 1;

static rSingle r;
static float scale = 20;

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
    r_single_init(&r, &camera_vp.m00, r_texture_from_file("res/test_astronaut.png"));
    
    speed = 10;
    
    r_pose_set_size_angle(r.rect.pose, scale, scale, 0);
}

void astronaut_update(float dtime) {
    // set position and rotation
    float da = clamp_rotation(alpha_dest - alpha);
    
    float angular_speed = da * ALPHA_SPEED_P;
    alpha = clamp_rotation(alpha + angular_speed * dtime);
    
    r_pose_set_angle(r.rect.pose, alpha);
    
//    r_pose_print(r.rect.pose);
	r_pose_shift_xy(r.rect.pose,
	speed * cos(alpha) *dtime, 
	speed * sin(alpha) * dtime);
	
    // check collision


    // set camera position
    camera_set_pos(R_PoseX(r.rect.pose), R_PoseY(r.rect.pose));
}

void astronaut_render() {
    r_single_render(&r);
}


void astronaut_rotate(float target_angle) {
    alpha_dest = target_angle;
}

