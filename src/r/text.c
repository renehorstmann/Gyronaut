
#include "r/text.h"

TTF_Font *r_text_default_font;


void r_text_init(rText *self, const char *text, const float *vp) {
	
	// todo
	r_basic_rect_init(&self->rect, NULL, vp);
	self->font = r_text_default_font;
}

void r_text_kill(rText *self) {
	
}

void r_text_update(rText *self) {
	
}

void r_text_render(rText *self) {
	
}

void r_text_set_text(rText *self, const char *text) {
	
}

