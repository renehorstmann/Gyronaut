#include "r/r.h"
#include "r/rect.h"


//static void update_uv(rRect *self) {
//    float uv[] = {
//            0, 1, 1, 1, 0, 0,
//            0, 0, 1, 1, 1, 0
//    };
//    for (int i = 0; i < 6; i++) {
//        self->buffer[i].u = uv[i * 2];
//        self->buffer[i].v = uv[i * 2 + 1];
//    }
//}
//
//static void update_pos(rRect *self) {
//    static const float v[] = {
//            -1, -1, +1, -1, -1, +1,
//            -1, +1, +1, -1, +1, +1
//    };
//    for (int i = 0; i < 6; i++) {
//        vec3 from = {v[i * 2], v[i * 2 + 1], 1};
//        vec3 to;
//        glm_mat3_mulv(self->pose, from, to);
//        self->buffer[i].x = to[0];
//        self->buffer[i].y = to[1];
//    }
//}

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

void r_rect_update(rRect *self) {
//    if (flags & R_BASIC_RECT_UPDATE_XY)
//        update_pos(self);
//    if (flags & R_BASIC_RECT_UPDATE_UV)
//        update_uv(self);
//
//    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
//    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(self->buffer), self->buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
