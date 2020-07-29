#define DEBUG
#include "cglm/cglm.h"
#include "render/render.h"
#include "camera.h"

static struct {
    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLuint tex;
} gl;

typedef struct vertex_s {
    float x, y, u, v;
} vertex_s;
static vertex_s buffer[6];

static mat3 position;
static float scale = 20;


static void update_uv() {
    float uv[] = {
            0, 1, 1, 1, 0, 0,
            0, 0, 1, 1, 1, 0
    };
    for (int i = 0; i < 6; i++) {
        buffer[i].u = uv[i * 2];
        buffer[i].v = uv[i * 2 + 1];
    }
}

static void update_pos() {
    static const float v[] = {
            -1, -1, +1, -1, -1, +1,
            -1, +1, +1, -1, +1, +1
    };
    for (int i = 0; i < 6; i++) {
        vec3 from = {v[i * 2], v[i * 2 + 1], 1};
        vec3 to;
        glm_mat3_mulv(position, from, to);
        buffer[i].x = to[0];
        buffer[i].y = to[1];
    }
}

static void update_buffer() {
    glBindBuffer(GL_ARRAY_BUFFER, gl.vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(buffer), buffer);
}

void astronaut_set_angle(float alpha) {
    position[0][0] = cos(alpha) * scale;
    position[0][1] = sin(alpha) * scale;
    position[1][0] = -sin(alpha) * scale;
    position[1][1] = cos(alpha) * scale;
}

void astronaut_init() {
    glm_mat3_identity(position);
    astronaut_set_angle(0);
    update_uv();
    update_pos();

    gl.program = r_compile_glsl_from_files((char *[]) {
            "res/shader/astronaut.vsh",
            "res/shader/astronaut.fsh",
            NULL
    });

    gl.tex = r_load_texture_from_file("res/test_astronaut.png");

    glGenVertexArrays(1, &gl.vao);
    glBindVertexArray(gl.vao);

    glGenBuffers(1, &gl.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, gl.vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(buffer),
                 buffer,
                 GL_STREAM_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_s), NULL);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_s), (void *) offsetof(vertex_s, u));

    glUniform1i(glGetUniformLocation(gl.program, "tex"), gl.tex);

    // unbind
    glBindVertexArray(0);
}

void astronaut_update(float dtime) {
    static float alpha = 0;
    alpha -= M_PI_2 * dtime;
    astronaut_set_angle(alpha);
    position[2][0] += 10 * dtime;
    update_pos();
    update_buffer();
}

void astronaut_render() {
    glUniformMatrix4fv(glGetUniformLocation(gl.program, "projection"),
                       1, GL_FALSE, camera_get_projection());

    glActiveTexture(gl.tex);
    glBindTexture(GL_TEXTURE_2D, gl.tex);

    glUseProgram(gl.program);
    glBindVertexArray(gl.vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
