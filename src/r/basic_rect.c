#include "r/r.h"
#include "r/basic_rect.h"
#include "cglm/cglm.h"


static void update_uv(rBasicRect *self) {
    float uv[] = {
            0, 1, 1, 1, 0, 0,
            0, 0, 1, 1, 1, 0
    };
    for (int i = 0; i < 6; i++) {
        self->buffer[i].u = uv[i * 2];
        self->buffer[i].v = uv[i * 2 + 1];
    }
}

static void update_pos(rBasicRect *self) {
    static const float v[] = {
            -1, -1, +1, -1, -1, +1,
            -1, +1, +1, -1, +1, +1
    };
    for (int i = 0; i < 6; i++) {
        vec3 from = {v[i * 2], v[i * 2 + 1], 1};
        vec3 to;
        glm_mat3_mulv(self->pose, from, to);
        self->buffer[i].x = to[0];
        self->buffer[i].y = to[1];
    }
}

void r_basic_rect_init(rBasicRect *self, const char *tex_file, const float *vp) {
    glm_mat3_identity(self->pose);

    self->vp = vp;

    self->program = r_compile_glsl_from_files((char *[]) {
            "res/shader/r/basic_rect.vsh",
            "res/shader/r/basic_rect.fsh",
            NULL
    });
    const int loc_position = 0;
    const int loc_tex_coord = 1;

    self->tex = r_texture_from_file(tex_file);

    update_pos(self);
    update_uv(self);

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
                         sizeof(self->buffer),
                         self->buffer,
                         GL_STREAM_DRAW);

            glEnableVertexAttribArray(loc_position);
            glVertexAttribPointer(loc_position, 2, GL_FLOAT, GL_FALSE,
                                  sizeof(struct rBasicRectVertex_s), NULL);
            glEnableVertexAttribArray(loc_tex_coord);
            glVertexAttribPointer(loc_tex_coord, 2, GL_FLOAT, GL_FALSE,
                                  sizeof(struct rBasicRectVertex_s),
                                  (void *) offsetof(
            struct rBasicRectVertex_s, u));

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        glBindVertexArray(0);
    }
}


void r_basic_rect_kill(rBasicRect *self) {
    glDeleteProgram(self->program);
    glDeleteVertexArrays(1, &self->vao);
    glDeleteBuffers(1, &self->vbo);
    glDeleteTextures(1, &self->tex);
}

void r_basic_rect_update(rBasicRect *self, int flags) {
    if (flags & R_BASIC_RECT_UPDATE_XY)
        update_pos(self);
    if (flags & R_BASIC_RECT_UPDATE_UV)
        update_uv(self);

    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(self->buffer), self->buffer);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void r_basic_rect_render(rBasicRect *self) {
    glUseProgram(self->program);

    glUniformMatrix4fv(glGetUniformLocation(self->program, "vp"),
                       1, GL_FALSE, self->vp);

    glActiveTexture(self->tex);
    glBindTexture(GL_TEXTURE_2D, self->tex);

    {
        glBindVertexArray(self->vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    glUseProgram(0);
}
