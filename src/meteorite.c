#include "cglm/cglm.h"
#include "utilc/alloc.h"
#include "r/batch.h"
#include "r/texture.h"
#include "u/pose.h"
#include "u/color.h"
#include "u/prandom.h"
#include "camera.h"
#include "meteorite.h"

static rBatch batch;

typedef struct Meteorite_s {
	rRect_s *r;
	vec2 speed;
	float rot_speed;
} Meteorite_s;

static Meteorite_s *m;


void meteorite_init(int num) {
    r_batch_init(&batch, num, &camera_vp.m00, r_texture_from_file("res/meteorite.png"));

    m = New0(Meteorite_s, num);

    for(int i=0; i<num; i++) {
        u_pose_set_size(batch.rects[i].pose, 20, 20);
        U_PoseX(batch.rects[i].pose) = u_pnoise(0, 300);
        U_PoseY(batch.rects[i].pose) = u_pnoise(0, 300);
        
        u_hsv2rgb((vec3) {
        	u_prange(0, 360), 
        	u_prange(0, 0.1),
        	u_prange(0.5, 1),
        }, batch.rects[i].color);
        
        m[i].r = &batch.rects[i];
        m[i].speed[0] = u_pnoise(0, 10);
        m[i].speed[1] = u_pnoise(0, 10);
        m[i].rot_speed = u_pnoise(0, M_PI_2);
    }
}

void meteorite_kill() {
    r_batch_kill(&batch);
    Free0(m);
}

static void update_meteorite(Meteorite_s *meteor, float dt) {
    u_pose_shift(meteor->r->pose,
	    meteor->speed[0] * dt,
	    meteor->speed[1] * dt,
	    meteor->rot_speed * dt
	);	
}

void meteorite_update(double dt) {
	for(int i=0; i<batch.num; i++)
	    update_meteorite(&m[i], dt);

    r_batch_update(&batch, 0, batch.num);
}

void meteorite_render() {
    r_batch_render(&batch);
}

// ... meteroite_collision_test(...);
