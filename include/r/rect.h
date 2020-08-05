#ifndef R_RECT_H
#define R_RECT_H

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

void r_rect_init(rRect *self, const float *vp, GLuint tex_sink);

void r_rect_kill(rRect *self);

void r_rect_update(rRect *self);

void r_rect_render(rRect *self);

#endif //R_RECT_H
