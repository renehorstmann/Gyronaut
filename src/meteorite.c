#include "cglm/cglm.h"
#include "utilc/alloc.h"
#include "r/batch.h"
#include "r/texture.h"
#include "u/pose.h"
#include "camera.h"
#include "meteorite.h"

static rBatch batch;

typedef struct Meteorite_s {
	rRect_s *r;
	vec2 speed;
	float rot_speed;
} Meteorite_s;

static Meteorite_s *m;

static float randf() {
    return (float) rand() / RAND_MAX;	
}

static float noise(float f, float amplitude) {
	return f - amplitude + 2*amplitude*randf();
}

void meteorite_init(int num) {
    r_batch_init(&batch, num, &camera_vp.m00, r_texture_from_file("res/meteorite.png"));

    m = New0(Meteorite_s, num);

    for(int i=0; i<num; i++) {
        u_pose_set_size(batch.rects[i].pose, 20, 20);
        U_PoseX(batch.rects[i].pose) = -300.0f + 600.0f * rand() / RAND_MAX;
        U_PoseY(batch.rects[i].pose) = -300.0f + 600.0f * rand() / RAND_MAX;
        
        glm_vec4_copy((vec4) {
        	noise(0.9, 0.1),
        	noise(0.9, 0.1),
        	noise(0.9, 0.1),
        	1
        }, batch.rects[i].color);
        
        m[i].r = &batch.rects[i];
        m[i].speed[0] = -10 + randf() * 20;
        m[i].speed[1] = -10 + randf() * 20;
        m[i].rot_speed = -M_PI_2 + randf() * M_PI;
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
