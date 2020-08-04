#ifndef RENDER_BATCH_RECTS_H
#define RENDER_BATCH_RECTS_H

#include "cglm/mat4.h"
#include "core.h"


struct rBatchRectsInstance_s {
    mat4 pose;
    vec4 color;
    vec2 uv_offset;
};

typedef struct rBatchRects {
    struct rBatchRectsInstance_s *instances;
    int num;
    const float *vp;
    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLuint instance_bo;
    GLuint tex;
} rBatchRects;

void r_batch_rects_init(rBatchRects *self, int num, const char *tex_file, const float *vp);

void r_batch_rects_kill(rBatchRects *self);

void r_batch_rects_update(rBatchRects *self);

void r_batch_rects_render(rBatchRects *self);

#endif //RENDER_BATCH_RECTS_H
