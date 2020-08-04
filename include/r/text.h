#ifndef R_TEXT_H
#define R_TEXT_H

#include "SDL_ttf.h"
#include "basic_rect.h"


extern TTF_Font *r_text_default_font;

typedef struct rText {
	rBasicRect rect;
	TTF_Font *font;
} rText;

void r_text_init(rText *self, const char *text, const float *vp);

void r_text_kill(rText *self);

void r_text_update(rText *self);

void r_text_render(rText *self);

void r_text_set_text(rText *self, const char *text);

#endif //R_TEXT_H
