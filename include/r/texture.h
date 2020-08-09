#ifndef R_TEXTURE_H
#define R_TEXTURE_H

#include "core.h"

#define R_MAX_TEXTURES 1000

GLuint r_texture_from_img(SDL_Surface *img);

GLuint r_texture_from_file(const char *file);

void r_texture_get_size(GLuint tex, int *w, int *h);

#endif //R_TEXTURE_H
