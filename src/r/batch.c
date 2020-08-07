#define DEBUG

#include "cglm/cglm.h"
#include "utilc/alloc.h"
#include "r/r.h"
#include "r/batch.h"


static void init_rects(rRect_s *instances, int num) {
    for (int i = 0; i < num; i++) {
        rRect_s *r = &instances[i];
        glm_mat4_identity(r->pose);
        glm_mat4_identity(r->uv);
        glm_vec4_one(r->color);
    }
}

void r_batch_init(rBatch *self, int num, const float *vp, GLuint tex_sink) {
    self->rects = New(rRect_s, num);
    init_rects(self->rects, num);

    self->num = num;
    self->vp = vp;

    self->program = r_compile_glsl_from_files((char *[]) {
            "res/shader/r/batch.vsh",
            "res/shader/r/batch.fsh",
            NULL});
    const int loc_pose = 0;
    const int loc_uv = 4;
    const int loc_color = 8;

    self->tex = tex_sink;
    self->owns_tex = true;

    // vao scope
    {
        glGenVertexArrays(1, &self->vao);
        glBindVertexArray(self->vao);

        // texture
        glUniform1i(glGetUniformLocation(self->program, "tex"), self->tex);

        // vbo
        {
            glGenBuffers(1, &self->vbo);
            glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
            glBufferData(GL_ARRAY_BUFFER,
                         num * sizeof(rRect_s),
                         self->rects,
                         GL_STREAM_DRAW);

            glBindVertexArray(self->vao);

            // pose
            for (int c = 0; c < 4; c++) {
                int loc = loc_pose + c;
                glEnableVertexAttribArray(loc);
                glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE,
                                      sizeof(rRect_s), (void *) (c * sizeof(vec4)));
                glVertexAttribDivisor(loc, 1);
            }

            // uv
            for (int c = 0; c < 4; c++) {
                int loc = loc_uv + c;
                glEnableVertexAttribArray(loc);
                glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE,
                                      sizeof(rRect_s), (void *) (offsetof(rRect_s, uv) + c * sizeof(vec4)));
                glVertexAttribDivisor(loc, 1);
            }

            // color
            glEnableVertexAttribArray(loc_color);
            glVertexAttribPointer(loc_color, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rRect_s),
                                  (void *) offsetof(rRect_s, color));
            glVertexAttribDivisor(loc_color, 1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        glBindVertexArray(0);
    }
}

void r_batch_kill(rBatch *self) {
    free(self->rects);
    glDeleteProgram(self->program);
    glDeleteVertexArrays(1, &self->vao);
    glDeleteBuffers(1, &self->vbo);
    if(self->owns_tex)
        glDeleteTextures(1, &self->tex);
    *self = (rBatch) {0};
}

void r_batch_update(rBatch *self) {
    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0,
                    self->num * sizeof(rRect_s), self->rects);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void r_batch_render(rBatch *self) {
    glUseProgram(self->program);

    glUniformMatrix4fv(glGetUniformLocation(self->program, "vp"),
                       1, GL_FALSE, self->vp);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self->tex);

    {
        glBindVertexArray(self->vao);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, self->num);
        glBindVertexArray(0);
    }

    glUseProgram(0);
}

void r_batch_set_texture(rBatch *self, GLuint tex) {
    if(self->owns_tex)
        glDeleteTextures(1, &self->tex);
    self->tex = tex;
}

