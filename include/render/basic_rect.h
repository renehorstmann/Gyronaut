#ifndef RENDER_BASIC_RECT_H
#define RENDER_BASIC_RECT_H

#include "cglm/mat3.h"
#include "core.h"

static const int R_BASIC_RECT_UPDATE_XY = 0x01;
static const int R_BASIC_RECT_UPDATE_UV = 0x02;


struct rBasicRectVertex_s {
    float x, y, u, v;
};

typedef struct rBasicRect {
    struct rBasicRectVertex_s buffer[6];
    mat3 mat;
    const float *vp;
    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLuint tex;
} rBasicRect;

void r_basic_rect_init(rBasicRect *self, const char *tex_file, const float *vp);

void r_basic_rect_kill(rBasicRect *self);

// use flags above
void r_basic_rect_update(rBasicRect *self, int flags);

void r_basic_rect_render(rBasicRect *self);

#endif //RENDER_BASIC_RECT_H
