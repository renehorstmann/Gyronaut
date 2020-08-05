#ifndef R_SINGLE_H
#define R_SINGLE_H

#include <stdbool.h>
#include "rect_s.h"
#include "core.h"

typedef struct rRect {
    rRect_s rect;
    const float *vp;
    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLuint tex;
    bool owns_tex;
} rRect;

void r_rect_init(rRect *self, GLuint tex_sink, const float *vp);

void r_rect_kill(rRect *self);

void r_rect_update(rRect *self);

void r_rect_render(rRect *self);

#endif //R_SINGLE_H
