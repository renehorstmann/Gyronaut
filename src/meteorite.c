#include "r/batch.h"
#include "camera.h"
#include "meteorite.h"

static rBatch batch;

void meteorite_init(int num) {
    r_batch_init(&batch, num, "res/meteorite_test.png", &camera_vp.m00);

    for(int i=0; i<num; i++) {
        batch.instances[i].pose[0][0] = 2;
        batch.instances[i].pose[1][1] = 2;
        batch.instances[i].pose[3][0] = -200.0f + 400.0f * rand() / RAND_MAX;
        batch.instances[i].pose[3][1] = -200.0f + 400.0f * rand() / RAND_MAX;
    }
}

void meteorite_kill() {
    r_batch_kill(&batch);
}

void color(int start, int cnt, float dt) {
	for(int i=start; i<start+cnt; i++) {
        for(int rgba=0; rgba<4; rgba++) {
            float col_shift = dt * rand() / RAND_MAX;
            if(rand() % 2 == 0) {
                batch.instances[i].color[rgba] += col_shift;
                if(batch.instances[i].color[rgba] > 1)
                    batch.instances[i].color[rgba] = 1;
            } else {
                batch.instances[i].color[rgba] -= col_shift;
                if(batch.instances[i].color[rgba] < 0)
                    batch.instances[i].color[rgba] = 0;
            }
        }
    }
}


void meteorite_update(double dt) {
    static int block = 0;
    int max = 100;
    int cnt = batch.num / max;
    color(cnt * block, cnt, dt * max);
    block++;
    if(block >= max)
        block = 0;

    r_batch_update(&batch);
}

void meteorite_render() {
    r_batch_render(&batch);
}

// ... meteroite_collision_test(...);
