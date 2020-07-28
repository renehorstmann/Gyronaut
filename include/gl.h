#ifndef GYRONAUT_GL_H
#define GYRONAUT_GL_H

#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#ifdef G_GLES
static const int G_GL_MAJOR_VERSION = 3;
static const int G_GL_MINOR_VERSION = 0;
static const int G_GL_PROFILE = SDL_GL_CONTEXT_PROFILE_ES;
#else
static const int G_GL_MAJOR_VERSION = 3;
static const int G_GL_MINOR_VERSION = 3;
static const int G_GL_PROFILE = SDL_GL_CONTEXT_PROFILE_CORE;
#endif


#ifdef G_GLES
#define G_VERTEX "#version 300 es\n"
#define G_FRAGMENT "#version 300 es\nprecision mediump float;\n"
#else
#define G_VERTEX "#version 330 core\n"
#define G_FRAGMENT "#version 330 core\n"
#endif

#endif //GYRONAUT_GL_H
