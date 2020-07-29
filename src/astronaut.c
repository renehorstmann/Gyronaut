#define DEBUG
#include "cglm/cglm.h"
#include "gl_utils.h"
#include "camera.h"

static const char *vertex_code =
        R_VERTEX
        "layout(location = 0) in vec2 in_position;\n"
        "layout(location = 1) in vec2 in_tex_coord;\n"
        "out vec2 v_tex_coord;\n"
        "void main() {\n"
        "  gl_Position = vec4(in_position.x, in_position.y, 0, 1);\n"
        "  v_tex_coord = in_tex_coord;\n"
        "}\n";

static const char *fragment_code =
        R_FRAGMENT
        "in vec2 v_tex_coord;\n"
        "out vec4 out_frag_color;\n"
        "uniform sampler2D tex;\n"
        "void main() {\n"
        "  out_frag_color = texture(tex, v_tex_coord);\n"
        "}\n";


static GLuint program;
static GLuint vao;
static GLuint vbo;
static GLuint tex;

typedef struct vertex {
    float x, y, u, v;
} vertex_s;
static vertex_s buffer[6];

static mat3 position;
static float scale;


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

void astronaut_set_angle(float alpha) {
    position[0][0] = cos(alpha) * scale;
    position[0][1] = sin(alpha) * scale;
    position[1][0] = -sin(alpha) * scale;
    position[1][1] = cos(alpha) * scale;
}

void astronaut_init() {
    scale = 20;
    glm_mat3_identity(position);
    astronaut_set_angle(0);
    update_uv();
    update_pos();

    program = compile_glsl_from_files((char *[]) {
            "res/shader/astronaut.vsh",
            "res/shader/astronaut.fsh",
            NULL
    });

    tex = load_texture_from_file("res/test_astronaut.png");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(buffer),
                 buffer,
                 GL_STREAM_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_s), NULL);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_s), (void *) offsetof(vertex_s, u));

    glUniform1i(glGetUniformLocation(program, "tex"), tex);

    // unbind
    glBindVertexArray(0);
}

void astronaut_update(float dtime) {
    static float alpha = 0;
    alpha += M_PI_2 * dtime;
    astronaut_set_angle(alpha);
    update_pos();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(buffer), buffer);
}

void astronaut_render() {
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"),
                       1, GL_FALSE, camera_get_projection());

    glActiveTexture(tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
