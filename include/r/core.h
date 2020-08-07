#ifndef R_GL_H
#define R_GL_H

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <SDL_opengl.h>

#if defined R_GLES || __EMSCRIPTEN__
static const int R_GL_MAJOR_VERSION = 3;
static const int R_GL_MINOR_VERSION = 0;
static const int R_GL_PROFILE = SDL_GL_CONTEXT_PROFILE_ES;
#else
static const int R_GL_MAJOR_VERSION = 3;
static const int R_GL_MINOR_VERSION = 3;
static const int R_GL_PROFILE = SDL_GL_CONTEXT_PROFILE_CORE;
#endif


#if defined R_GLES || __EMSCRIPTEN__
#define R_VERTEX_BEGIN "#version 300 es\n"
#define R_FRAGMENT_BEGIN "#version 300 es\nprecision mediump float;\n"
#else
#define R_VERTEX_BEGIN "#version 330 core\n"
#define R_FRAGMENT_BEGIN "#version 330 core\n"
#endif


#endif //R_GL_H
