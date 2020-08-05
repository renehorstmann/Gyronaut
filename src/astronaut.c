#define DEBUG
#include "cglm/struct.h"
#include "r/single.h"
#include "r/texture.h"
#include "camera.h"
#include "input.h"

const static float ALPHA_SPEED_P = 1;

static rSingle r;
static float scale = 20;

static float speed;
static float alpha;
static float alpha_dest;


void astronaut_init() {
    r_single_init(&r, &camera_vp.m00, r_texture_from_file("res/test_astronaut.png"));
    speed = 10;
    
    r_pose_set_size_angle(r.rect.pose, scale, scale, 0);

//    rect.rect.uv[0][0] = 0.5;
//    rect.rect.uv[1][1] = 0.5;
}

void astronaut_update(float dtime) {
    // set position and rotation
    float angular_speed = (alpha_dest - alpha) * ALPHA_SPEED_P;
    alpha += angular_speed * dtime;
    
    r_pose_set_angle(r.rect.pose, alpha);
    
    r_pose_print(r.rect.pose);
	r_pose_shift_xy(r.rect.pose,
	speed * cos(alpha) *dtime, 
	speed * sin(alpha) * dtime);
	
	//R_PoseY(r.rect.pose) = 50;

//    rect.rect.uv[3][0] += dtime;
//    rect.rect.uv[3][1] += dtime;
    // check collision


    // set camera position
    camera_set_pos(r.rect.pose[2][0], r.rect.pose[2][1]);
    camera_set_angle(-alpha_dest);
}

void astronaut_render() {
    r_single_render(&r);
}


void astronaut_rotate(float target_angle) {
    alpha_dest = target_angle;
}

