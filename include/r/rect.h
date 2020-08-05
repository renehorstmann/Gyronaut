#ifndef R_RECT_H
#define R_RECT_H

#include "cglm/mat3.h"
#include "core.h"

static const int R_BASIC_RECT_UPDATE_XY = 0x01;
static const int R_BASIC_RECT_UPDATE_UV = 0x02;


struct rBasicRectVertex_s {
    float x, y, u, v;
};

typedef struct rRect {
    struct rBasicRectVertex_s buffer[6];
    mat3 pose;
    const float *vp;
    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLuint tex;
} rRect;

// test
void r_rect_init(rRect *self, const char *tex_file, const float *vp);

void r_rect_kill(rRect *self);

// use flags above
void r_rect_update(rRect *self, int flags);

void r_rect_render(rRect *self);

#endif //R_RECT_H
