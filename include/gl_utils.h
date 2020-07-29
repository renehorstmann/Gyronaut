#ifndef GYRONAUT_GL_UTILS_H
#define GYRONAUT_GL_UTILS_H

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
#define R_VERTEX "#version 300 es\n"
#define R_FRAGMENT "#version 300 es\nprecision mediump float;\n"
#else
#define R_VERTEX "#version 330 core\n"
#define R_FRAGMENT "#version 330 core\n"
#endif


void setup_blending();

GLuint compile_shader(GLint type, const char *src);

typedef struct shader_source {
    GLint type;
    const char *src;
} shader_source;

GLuint compile_glsl(shader_source *sources, int n);

GLuint compile_shader_from_file(const char *file);

GLuint compile_glsl_from_files(char **files);

GLuint load_texture_from_file(const char *file);

#endif //GYRONAUT_GL_UTILS_H
