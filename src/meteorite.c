#include "r/r.h"
#include "camera.h"
#include "meteorite.h"

static rBatch batch;

void meteorite_init(int num) {
    r_batch_init(&batch, num, &camera_vp.m00, r_texture_from_file("res/meteorite.png"));

    for(int i=0; i<num; i++) {
        r_pose_set_size(batch.rects[i].pose, 20, 20);
        R_PoseX(batch.rects[i].pose) = -300.0f + 600.0f * rand() / RAND_MAX;
        R_PoseY(batch.rects[i].pose) = -300.0f + 600.0f * rand() / RAND_MAX;
    }
}

void meteorite_kill() {
    r_batch_kill(&batch);
}

void color(int start, int cnt, float dt) {
	return;
	for(int i=start; i<start+cnt; i++) {
        for(int rgba=0; rgba<4; rgba++) {
            float col_shift = dt * rand() / RAND_MAX;
            if(rand() % 2 == 0) {
                batch.rects[i].color[rgba] += col_shift;
                if(batch.rects[i].color[rgba] > 1)
                    batch.rects[i].color[rgba] = 1;
            } else {
                batch.rects[i].color[rgba] -= col_shift;
                if(batch.rects[i].color[rgba] < 0)
                    batch.rects[i].color[rgba] = 0;
            }
        }
    }
}


void meteorite_update(double dt) {
    color(0, batch.num, dt);

    r_batch_update(&batch, 0, batch.num);
}

void meteorite_render() {
    r_batch_render(&batch);
}

// ... meteroite_collision_test(...);
