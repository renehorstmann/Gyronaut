#ifndef RENDER_BASIC_RECT_H
#define RENDER_BASIC_RECT_H

#include "cglm/mat3.h"
#include "core.h"

static const int R_BASIC_RECT_UPDATE_XY = 0x01;
static const int R_BASIC_RECT_UPDATE_UV = 0x02;


struct r_BasicRectVertex_s {
    float x, y, u, v;
};

typedef struct r_BasicRect {
    struct r_BasicRectVertex_s buffer[6];
    mat3 mat;
    const float *vp;
    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLuint tex;
} r_BasicRect;

void r_basic_rect_init(r_BasicRect *self, const char *tex_file, const float *vp);

// use flags above
void r_basic_rect_update(r_BasicRect *self, int flags);

void r_basic_rect_render(r_BasicRect *self);

#endif //RENDER_BASIC_RECT_H
