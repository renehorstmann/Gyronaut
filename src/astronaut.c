#include "gl.h"

static const char *vertex_code =
        R_VERTEX
        "layout(location = 0) in vec2 in_position;\n"
        "layout(location = 1) in vec2 in_tex_coord;\n"
        "out VData {\n"
        "  vec2 tex_coord;\n"
        "} o;\n"
        "void main() {\n"
        "  gl_Position = vec4(in_position.x, in_position.y, 0, 1);\n"
        "  o.tex_coord = in_tex_coord;\n"
        "}\n";

static const char *fragment_code =
        R_FRAGMENT
        "in VData {\n"
        "  vec2 tex_coord;\n"
        "} i;\n"
        "out vec4 out_frag_color;\n"
        "uniform sampler2D tex;\n"
        "void main() {\n"
        "  out_frag_color = texture(tex, i.tex_coord);\n"
        "}\n";

static GLuint vao;
static GLuint program;
static GLuint tex;


void astronaut_init() {
    program = compile_glsl((shader_source[]) {
            {GL_VERTEX_SHADER,   vertex_code},
            {GL_FRAGMENT_SHADER, fragment_code}
    }, 2);

    tex = load_texture_from_file("res/test_astronaut.png");


    static float tr_data[] = {
            0, 0, 1, 0, 0, 1,
            0, 1, 1, 0, 1, 1
    };
    static float tex_pos_data[] = {
            0, 1, 1, 1, 0, 0,
            0, 0, 1, 1, 1, 0
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(tr_data),
                 tr_data,
                 GL_STATIC_DRAW);

    GLuint tbo;
    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tex_pos_data), tex_pos_data, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, tbo);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glUniform1i(glGetUniformLocation(program, "tex"), tex);

    // unbind
    glBindVertexArray(0);
}

void astronaut_update(double dtime) {

}

void astronaut_render() {
    glActiveTexture(tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
