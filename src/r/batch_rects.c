#define DEBUG

#include "utilc/alloc.h"
#include "r/r.h"
#include "r/batch_rects.h"
#include "cglm/cglm.h"

// x, y, u, v
static const float buffer[] = {
        -1, -1, 0, 1,
        +1, -1, 1, 1,
        -1, +1, 0, 0,
        -1, +1, 0, 0,
        +1, -1, 1, 1,
        +1, +1, 1, 0
};

void r_batch_rects_init(rBatchRects *self, int num, const char *tex_file, const float *vp) {
    self->instances = New(struct rBatchRectsInstance_s, num);
    for (int i = 0; i < num; i++)
        glm_mat4_identity(self->instances[i].m);

    self->num = num;
    self->vp = vp;

    self->program = r_compile_glsl_from_files((char *[]) {
            "res/shader/r/batch_rects.vsh",
            "res/shader/r/batch_rects.fsh",
            NULL});
    const int loc_position = 0;
    const int loc_tex_coord = 1;
    const int loc_m = 2;

    self->tex = r_load_texture_from_file(tex_file);

    // vao scope
    {
        glGenVertexArrays(1, &self->vao);
        glBindVertexArray(self->vao);

        // texture
        glUniform1i(glGetUniformLocation(self->program, tex_file), self->tex);

        // vbo scope = xyuv
        {
            glGenBuffers(1, &self->vbo);
            glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(buffer),
                         buffer,
                         GL_STATIC_DRAW);

            glEnableVertexAttribArray(loc_position);
            glVertexAttribPointer(loc_position, 2, GL_FLOAT, GL_FALSE,
                                  4 * sizeof(float), NULL);
            glEnableVertexAttribArray(loc_tex_coord);
            glVertexAttribPointer(loc_tex_coord, 2, GL_FLOAT, GL_FALSE,
                                  4 * sizeof(float),
                                  (void *) (2 * sizeof(float)));

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        // instance_bo = mat4
        {
            glGenBuffers(1, &self->instance_bo);
            glBindBuffer(GL_ARRAY_BUFFER, self->instance_bo);
            glBufferData(GL_ARRAY_BUFFER,
                         num * sizeof(struct rBatchRectsInstance_s),
                         self->instances,
                         GL_STREAM_DRAW);

            glBindVertexArray(self->vao);

            for (int c = 0; c < 4; c++) {
                int loc = loc_m + c;
                glEnableVertexAttribArray(loc);
                glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void *) (c * sizeof(vec4)));
                glVertexAttribDivisor(loc, 1);
            }

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        glBindVertexArray(0);
    }
}

void r_batch_rects_kill(rBatchRects *self) {
    free(self->instances);
    glDeleteProgram(self->program);
    glDeleteVertexArrays(1, &self->vao);
    glDeleteBuffers(1, &self->vbo);
    glDeleteBuffers(1, &self->instance_bo);
    glDeleteTextures(1, &self->tex);
    *self = (rBatchRects) {0};
}

void r_batch_rects_update(rBatchRects *self) {
    glBindBuffer(GL_ARRAY_BUFFER, self->instance_bo);
    glBufferSubData(GL_ARRAY_BUFFER, 0,
                    self->num * sizeof(struct rBatchRectsInstance_s), self->instances);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void r_batch_rects_render(rBatchRects *self) {
    glUseProgram(self->program);

    glUniformMatrix4fv(glGetUniformLocation(self->program, "vp"),
                       1, GL_FALSE, self->vp);

    glActiveTexture(self->tex);
    glBindTexture(GL_TEXTURE_2D, self->tex);

    {
        glBindVertexArray(self->vao);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, self->num);
        glBindVertexArray(0);
    }

    glUseProgram(0);
}
