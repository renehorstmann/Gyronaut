#ifndef RENDER_BATCH_RECTS_H
#define RENDER_BATCH_RECTS_H

#include "cglm/mat3.h"
#include "core.h"



struct rBasicRectVertex_s {
    float x, y, u, v;
};

typedef struct rBatchRects {
    struct rBasicRectVertex_s buffer[6];
    mat3 mat;
    const float *vp;
    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLuint tex;
} rBatchRects;

void r_batch_rects_init(rBatchRects *self, int num, const char *tex_file, const float *vp);

void r_batch_rects_kill(rBatchRects *self);

void r_batch_rects_render(rBatchRects *self);

#endif //RENDER_BATCH_RECTS_H
