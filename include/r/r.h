#ifndef R_H
#define R_H

#include "core.h"
#include "common.h"
#include "texture.h"
#include "shader.h"
#include "rect.h"
#include "single.h"
#include "batch.h"
#include "particle.h"
#include "text.h"


#define rglerrclear while(glGetError()!=GL_NO_ERROR);
#define rglerr \
{ \
    GLenum err; \
    while((err = glGetError()) != GL_NO_ERROR) \
        SDL_Log("glError: 0x%04x", err); \
}


static const vec4 rWHITE = {1, 1, 1, 1};
static const vec4 rBLACK = {0, 0, 0, 1};
static const vec4 rRED = {1, 0, 0, 1};
static const vec4 rGREEN= {0, 1, 0, 1};
static const vec4 rBLUE = {0, 0, 1, 1};
static const vec4 rYELLOW = {1, 1, 0, 1};
static const vec4 rCYAN = {0, 1, 1, 1};
static const vec4 rMAGENTA = {1, 0, 1, 1};

#endif //R_H
