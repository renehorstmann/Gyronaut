#ifndef RENDER_TEXTURE_H
#define RENDER_TEXTURE_H

#include "core.h"

GLuint r_load_texture_from_img(SDL_Surface *img);

GLuint r_load_texture_from_file(const char *file);

#endif //RENDER_TEXTURE_H
