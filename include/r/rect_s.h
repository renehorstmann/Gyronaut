#ifndef R_RECT_S_H
#define R_RECT_S_H

#include "cglm/types.h"

typedef struct rRect_s {
    mat4 pose;
    mat4 uv;
    vec4 color;
} rRect_s;

#endif //R_RECT_S_H
