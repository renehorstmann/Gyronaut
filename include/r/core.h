#ifndef R_CORE_H
#define R_CORE_H

#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <SDL_opengl.h>

#include "mathc/types.h"


#define rglerrclear while(glGetError()!=GL_NO_ERROR);
#define rglerr \
{ \
    GLenum err; \
    while((err = glGetError()) != GL_NO_ERROR) \
        SDL_Log("glerror: 0x%04x", err); \
}


static const vec4f rWHITE = {{1, 1, 1, 1}};
static const vec4f rBLACK = {{0, 0, 0, 1}};
static const vec4f rRED = {{1, 0, 0, 1}};
static const vec4f rGREEN= {{0, 1, 0, 1}};
static const vec4f rBLUE = {{0, 0, 1, 1}};
static const vec4f rYELLOW = {{1, 1, 0, 1}};
static const vec4f rCYAN = {{0, 1, 1, 1}};
static const vec4f rMAGENTA = {{1, 0, 1, 1}};

#endif //R_CORE_H
