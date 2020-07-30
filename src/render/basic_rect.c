#include "render/render.h"
#include "render/basic_rect.h"
#include "cglm/cglm.h"


static void update_uv(r_BasicRect *self) {
    float uv[] = {
            0, 1, 1, 1, 0, 0,
            0, 0, 1, 1, 1, 0
    };
    for (int i = 0; i < 6; i++) {
        self->buffer[i].u = uv[i * 2];
        self->buffer[i].v = uv[i * 2 + 1];
    }
}

static void update_pos(r_BasicRect *self) {
    static const float v[] = {
            -1, -1, +1, -1, -1, +1,
            -1, +1, +1, -1, +1, +1
    };
    for (int i = 0; i < 6; i++) {
        vec3 from = {v[i * 2], v[i * 2 + 1], 1};
        vec3 to;
        glm_mat3_mulv(self->mat, from, to);
        self->buffer[i].x = to[0];
        self->buffer[i].y = to[1];
    }
}

void r_basic_rect_init(r_BasicRect *self, const char *tex_file, const float *vp) {

    self->vp = vp;
    glm_mat3_identity(self->mat);
    update_pos(self);
    update_uv(self);

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
                          sizeof(struct r_BasicRectVertex_s), NULL);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                          sizeof(struct r_BasicRectVertex_s),
                          (void *) offsetof(struct r_BasicRectVertex_s, u));

    glUniform1i(glGetUniformLocation(self->program, tex_file), self->tex);

    // unbind
    glBindVertexArray(0);
}

void r_basic_rect_update(r_BasicRect *self, int flags) {
    if(flags & R_BASIC_RECT_UPDATE_XY)
        update_pos(self);
    if(flags & R_BASIC_RECT_UPDATE_UV)
        update_uv(self);

    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(self->buffer), self->buffer);
}

void r_basic_rect_render(r_BasicRect *self) {
    glUniformMatrix4fv(glGetUniformLocation(self->program, "vp"),
                       1, GL_FALSE, self->vp);

    glActiveTexture(self->tex);
    glBindTexture(GL_TEXTURE_2D, self->tex);

    glUseProgram(self->program);
    glBindVertexArray(self->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
