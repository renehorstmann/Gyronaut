#ifndef R_BATCH_H
#define R_BATCH_H

#include "cglm/mat4.h"
#include "core.h"


struct rBatchRect_s {
    mat4 pose;
    vec4 color;
    vec2 uv_offset;
};

typedef struct rBatch {
    struct rBatchRect_s *instances;
    int num;
    const float *vp;
    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLuint instance_bo;
    GLuint tex;
} rBatch;

void r_batch_init(rBatch *self, int num, const char *tex_file, const float *vp);

void r_batch_kill(rBatch *self);

void r_batch_update(rBatch *self);

void r_batch_render(rBatch *self);

#endif //R_BATCH_H
