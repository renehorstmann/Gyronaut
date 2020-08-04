#include "r/texture.h"
#include "r/text.h"

TTF_Font *r_text_default_font;

static GLuint create_tex(TTF_Font *font, const char *text) {
    
    return 0;
}


void r_text_init(rText *self, const char *text, const float *vp) {
	
	// todo
	r_basic_rect_init(&self->rect, NULL, vp);
	self->font = r_text_default_font;
}

void r_text_kill(rText *self) {
	r_basic_rect_kill(&self->rect);
}

void r_text_update(rText *self) {
	r_basic_rect_update(&self->rect, R_BASIC_RECT_UPDATE_XY);
}

void r_text_render(rText *self) {
	r_basic_rect_render(&self->rect);
}

void r_text_set_text(rText *self, const char *text) {
	
}

