#ifndef R_RECT_H
#define R_RECT_H

#include "mathc/types.h"

typedef struct rRect_s {
    mat44f pose;
    mat44f uv;
    vec4f color;
} rRect_s;


#endif //R_RECT_H
