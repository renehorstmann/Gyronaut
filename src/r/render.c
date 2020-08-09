#include "r/render.h"

void r_render_init() {
    
    SDL_Log("OpenGL version: %s", glGetString(GL_VERSION));
    
    int max_vertex_attributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vertex_attributes);
    if(max_vertex_attributes < 16) {
        SDL_Log("OpenGL failed: only has %d/16 vertex attributes", max_vertex_attributes);
        exit(EXIT_FAILURE);
    }
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void r_render_error_check() {
	GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
        SDL_Log("OpenGl error in a frame: 0x%04x", err);
}
