#include "r/texture.h"
#include "r/text.h"

TTF_Font *r_text_default_font;

GLuint r_text_create_texture(TTF_Font *font, const vec4 color, const char *text) {

    // SDL_ttf seems to render in BGRA format, so we just swap r and b
    SDL_Surface *img = TTF_RenderText_Blended(font, text,
            (SDL_Color) {color[2]*255, color[1]*255, color[0]*255, color[3]*255});
    return r_texture_from_img(img);
}


void r_text_init(rText *self, const float *vp, const vec4 color, const char *text) {
    self->font = r_text_default_font;
    r_single_init(&self->r, vp, r_text_create_texture(self->font, color, text));
    int w, h;
    r_texture_get_size(self->r.tex, &w, &h);
    self->ratio = (float) w / h;
}

void r_text_kill(rText *self) {
    r_single_kill(&self->r);
}

void r_text_render(rText *self) {
    r_single_render(&self->r);
}

void r_text_set_size(rText *self, float h) {
	r_pose_set_size(self->r.rect.pose, h*self->ratio, h);
}

void r_text_set_text(rText *self, const vec4 color, const char *text) {
    r_single_set_texture(&self->r, r_text_create_texture(self->font, color, text));
    int w, h;
    r_texture_get_size(self->r.tex, &w, &h);
    self->ratio = (float) w / h;
    r_text_set_size(self, r_pose_get_h(self->r.rect.pose));
}

