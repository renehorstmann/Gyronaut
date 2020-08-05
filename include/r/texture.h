#ifndef R_TEXTURE_H
#define R_TEXTURE_H

#include "core.h"

GLuint r_texture_from_img(SDL_Surface *img);

GLuint r_texture_from_file(const char *file);

#endif //R_TEXTURE_H
