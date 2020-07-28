#ifndef GYRONAUT_GL_H
#define GYRONAUT_GL_H

#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#ifdef GYRONAUT_GLES
#define GYRONAUT_OPENGL_MAJOR_VERSION 3
#define GYRONAUT_OPENGL_MINOR_VERSION 0
#else
#define GYRONAUT_OPENGL_MAJOR_VERSION 3
#define GYRONAUT_OPENGL_MINOR_VERSION 3
#endif


//#ifdef GYRONAUT_GLES
//#define GYRONAUT_VERTEX "#version 300 es\n"
//#define GYRONAUT_FRAGMENT "#version 300 es\nprecision mediump float;\n"
//#else
//#define GYRONAUT_VERTEX "#version 330\n"
//#define GYRONAUT_FRAGMENT "#version 330\n"
//#endif

#endif //GYRONAUT_GL_H
