#include "r/texture.h"
#include "r/text.h"

TTF_Font *r_text_default_font;

GLuint r_text_create_texture(TTF_Font *font, const vec4 color, const char *text) {

    // SDL_ttf seems to render in BGRA format, so we just swap r and b
    SDL_Surface *img = TTF_RenderText_Blended(font, text,
            (SDL_Color) {color[2]*255, color[1]*255, color[0]*255, color[3]*255});
    return r_texture_from_img(img);
}


// from u/pose.h
static float pose_get_w(/*const*/ mat4 p) {
	return sqrtf(powf(p[0][0], 2) + powf(p[0][1], 2));
}
static float pose_get_h(/*const*/ mat4 p) {
	return sqrtf(powf(p[1][0], 2) + powf(p[1][1], 2));
}
static void pose_set_w(mat4 p, float w) {
	float f = w / pose_get_w(p);    
	p[0][0] *= f;
	p[0][1] *= f;
}
static void pose_set_h(mat4 p, float h) {
	float f = h / pose_get_h(p);
	p[1][0] *= f;
	p[1][1] *= f;
}
static void pose_set_size(mat4 p, float w, float h) {
	pose_set_w(p, w);
	pose_set_h(p, h);
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
	pose_set_size(self->r.rect.pose, h*self->ratio, h);
}

void r_text_set_text(rText *self, const vec4 color, const char *text) {
    r_single_set_texture(&self->r, r_text_create_texture(self->font, color, text));
    int w, h;
    r_texture_get_size(self->r.tex, &w, &h);
    self->ratio = (float) w / h;
    r_text_set_size(self, pose_get_h(self->r.rect.pose));
}

