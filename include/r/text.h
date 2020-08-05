#ifndef R_TEXT_H
#define R_TEXT_H

#include "SDL_ttf.h"
#include "SDL_opengl.h"
#include "cglm/types.h"
#include "single.h"


extern TTF_Font *r_text_default_font;

GLuint r_text_create_texture(TTF_Font *font, const vec4 color, const char *text);

typedef struct rText {
	rSingle rect;
	TTF_Font *font;
	float ratio;    // width / height
} rText;

void r_text_init(rText *self, const float *vp, const vec4 color, const char *text);

void r_text_kill(rText *self);

void r_text_render(rText *self);

void r_text_set_text(rText *self, const vec4 color, const char *text);

#endif //R_TEXT_H
