#define DEBUG

#include "cglm/cglm.h"
#include "utilc/assume.h"
#include "utilc/alloc.h"
#include "r/batch.h"
#include "r/texture.h"
#include "u/pose.h"
#include "u/color.h"
#include "u/prandom.h"
#include "p/circle.h"
#include "camera.h"
#include "meteorite.h"

static rBatch batch;

typedef struct Meteorite_s {
	rRect_s *r;
	vec2 speed;
	float rot_speed;
} Meteorite_s;

static Meteorite_s *m;
static pCircle_s *mc;


static void update_meteorite(int idx, float dt) {
    u_pose_shift(m[idx].r->pose,
	    m[idx].speed[0] * dt,
	    m[idx].speed[1] * dt,
	    m[idx].rot_speed * dt
	);	
	mc[idx].x = U_PoseX(m[idx].r->pose);
	mc[idx].y = U_PoseY(m[idx].r->pose);
}


static void handle_collision(int a, int b) {
	p_circle_handle_elastic_collision(&mc[a], &mc[b], m[a].speed, m[b].speed);
	u_pose_set_xy(m[a].r->pose, mc[a].x, mc[a].y);
	u_pose_set_xy(m[b].r->pose, mc[b].x, mc[b].y);
}

static void self_collisions() {
    for(int i=0; i<batch.num; i++) {
    	int offset = i+1;
    	pIndices_s res = p_circle_og(mc[i], mc+offset, batch.num-offset);
    	
    	for(int c=0; c<res.num; c++) {
    		printf("%d - %d\n", i, c+offset);
    		handle_collision(i, res.data[c]+offset);
    	}	
    }
}


void meteorite_init(int num) {
    r_batch_init(&batch, num, &camera_vp.m00, r_texture_from_file("res/meteorite.png"));

    m = New0(Meteorite_s, num);
    mc = New0(pCircle_s, num);

    for(int i=0; i<num; i++) {
        float r = u_prange(10, 30);
        mc[i].r = r * 0.75f;
        u_pose_set_size(batch.rects[i].pose, r, r);
        
        U_PoseX(batch.rects[i].pose) = u_pnoise(0, 300);
        U_PoseY(batch.rects[i].pose) = u_pnoise(0, 300);
        
        u_hsv2rgb((vec3) {
        	u_prange(0, 360), 
        	u_prange(0, 0.1),
        	u_prange(0.5, 1),
        }, batch.rects[i].color);
        
        m[i].r = &batch.rects[i];
        m[i].speed[0] = u_pnoise(0, 20);
        m[i].speed[1] = u_pnoise(0, 20);
        m[i].rot_speed = u_pnoise(0, M_PI_2);
    }
    
}

void meteorite_kill() {
    r_batch_kill(&batch);
    Free0(m);
    Free0(mc);
}

void meteorite_update(double dt) {
	for(int i=0; i<batch.num; i++)
	    update_meteorite(i, dt);
	    
	self_collisions();

    r_batch_update(&batch, 0, batch.num);
}

void meteorite_render() {
    r_batch_render(&batch);
}



// ... meteroite_collision_test(...);
