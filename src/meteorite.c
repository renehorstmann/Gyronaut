#include "render/batch_rects.h"
#include "camera.h"
#include "meteorite.h"

static rBatchRects batch;

void meteorite_init(int num) {
    r_batch_rects_init(&batch, 4, "res/meteorite_test.png", &camera_vp.m00);
    
    batch.instances[0].m[0][0] = 50;
    batch.instances[0].m[1][1] = 50;
}

void meteorite_kill() {
	
}

void meteorite_update(double dt) {
	r_batch_rects_update(&batch);
}

void meteorite_render() {
	r_batch_rects_render(&batch);
}

// ... meteroite_collision_test(...);
