#include "render/render.h"
#include "render/batch_rects.h"
#include "cglm/cglm.h"


void r_batch_rects_init(rBatchRects *self, int num, const char *tex_file, const float *vp) {

    self->vp = vp;
    glm_mat3_identity(self->mat);
    //update_pos(self);
    //update_uv(self);

    self->program = r_compile_glsl_from_files((char *[]) {
            "res/shader/render/basic_rect.vsh",
            "res/shader/render/basic_rect.fsh",
            NULL
    });

    self->tex = r_load_texture_from_file(tex_file);

    glGenVertexArrays(1, &self->vao);
    glBindVertexArray(self->vao);

    glGenBuffers(1, &self->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(self->buffer),
                 self->buffer,
                 GL_STREAM_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                          sizeof(struct rBasicRectVertex_s), NULL);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                          sizeof(struct rBasicRectVertex_s),
                          (void *) offsetof(struct rBasicRectVertex_s, u));

    glUniform1i(glGetUniformLocation(self->program, tex_file), self->tex);

    // unbind
    glBindVertexArray(0);
}


void r_batch_rects_kill(rBatchRects *self) {
	glDeleteProgram(self->program);
	glDeleteVertexArrays(1, &self->vao);
	glDeleteBuffers(1, &self->vbo);
	glDeleteTextures(1, &self->tex);
}

void r_batch_rects_render(rBatchRects *self) {
    glUniformMatrix4fv(glGetUniformLocation(self->program, "vp"),
                       1, GL_FALSE, self->vp);

    glActiveTexture(self->tex);
    glBindTexture(GL_TEXTURE_2D, self->tex);

    glUseProgram(self->program);
    glBindVertexArray(self->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
