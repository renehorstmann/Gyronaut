#include "cglm/cglm.h"
#include "r/r.h"
#include "r/rect.h"

static float buffer[] = {
    -1, -1, 0, 1, 0, 1, 0, 1,
    +1, -1, 0, 1, 1, 1, 0, 1,
    -1, +1, 0, 1, 0, 0, 0, 1,
    -1, +1, 0, 1, 0, 0, 0, 1,
    +1, -1, 0, 1, 1, 1, 0, 1,
    +1, +1, 0, 1, 1, 0, 0, 1
};

void r_rect_init(rRect *self, const float *vp, GLuint tex_sink) {
    glm_mat4_identity(self->rect.pose);
    glm_mat4_identity(self->rect.uv);
    glm_vec4_one(self->rect.color);

    self->vp = vp;

    self->program = r_compile_glsl_from_files((char *[]) {
            "res/shader/r/rect.vsh",
            "res/shader/r/rect.fsh",
            NULL
    });
    const int loc_position = 0;
    const int loc_tex_coord = 1;

    self->tex = tex_sink;
    self->owns_tex = true;

    // vao scope
    {
        glGenVertexArrays(1, &self->vao);
        glBindVertexArray(self->vao);

        // texture
        glUniform1i(glGetUniformLocation(self->program, "tex"), self->tex);

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
                                  8 * sizeof(float), NULL);
            glEnableVertexAttribArray(loc_tex_coord);
            glVertexAttribPointer(loc_tex_coord, 2, GL_FLOAT, GL_FALSE,
                                  8 * sizeof(float),
                                  (void *) (4 * sizeof(float)));

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        glBindVertexArray(0);
    }
}

void r_rect_update(rRect *self);

void r_rect_render(rRect *self);


void r_rect_kill(rRect *self) {
    glDeleteProgram(self->program);
    glDeleteVertexArrays(1, &self->vao);
    glDeleteBuffers(1, &self->vbo);
    if(self->owns_tex)
        glDeleteTextures(1, &self->tex);
    *self = (rRect) {0};
}

void r_rect_render(rRect *self) {
    glUseProgram(self->program);

    glUniformMatrix4fv(glGetUniformLocation(self->program, "m"),
                       1, GL_FALSE, &self->rect.pose[0][0]);

    glUniformMatrix4fv(glGetUniformLocation(self->program, "vp"),
                       1, GL_FALSE, self->vp);

    glUniformMatrix4fv(glGetUniformLocation(self->program, "uv"),
                       1, GL_FALSE, &self->rect.uv[0][0]);

    glUniform4fv(glGetUniformLocation(self->program, "color"),
                       1, self->rect.color);

    glActiveTexture(self->tex);
    glBindTexture(GL_TEXTURE_2D, self->tex);

    {
        glBindVertexArray(self->vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    glUseProgram(0);
}

void r_rect_set_texture(rRect *self, GLuint tex) {
    if(self->owns_tex)
        glDeleteTextures(1, &self->tex);
    self->tex = tex;
}
