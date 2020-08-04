#ifndef RENDER_GL_H
#define RENDER_GL_H

#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <SDL_opengl.h>

#ifdef R_GLES
static const int R_GL_MAJOR_VERSION = 3;
static const int R_GL_MINOR_VERSION = 0;
static const int R_GL_PROFILE = SDL_GL_CONTEXT_PROFILE_ES;
#else
static const int R_GL_MAJOR_VERSION = 3;
static const int R_GL_MINOR_VERSION = 3;
static const int R_GL_PROFILE = SDL_GL_CONTEXT_PROFILE_CORE;
#endif


#ifdef R_GLES
#define R_VERTEX_BEGIN "#version 300 es\n"
#define R_FRAGMENT_BEGIN "#version 300 es\nprecision mediump float;\n"
#else
#define R_VERTEX_BEGIN "#version 330 core\n"
#define R_FRAGMENT_BEGIN "#version 330 core\n"
#endif


#endif //RENDER_GL_H
