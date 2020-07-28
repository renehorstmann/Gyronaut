#include "gl.h"

static const char *vertex_code =
        R_VERTEX
        "layout(location = 0) in vec2 position;\n"
        "void main() {\n"
        "  gl_Position = vec4(position.x, position.y, 0, 1);\n"
        "}\n";

static const char *fragment_code =
        R_FRAGMENT
        "out vec4 fragcolor;\n"
        "void main() {\n"
        "  fragcolor = vec4(0, 1, 0, 1);\n"
        "}\n";

static GLuint vao;
static GLuint vbo;
static GLuint program;


void astronaut_init() {
    program = compile_glsl((shader_source[]) {
            {GL_VERTEX_SHADER,   vertex_code},
            {GL_FRAGMENT_SHADER, fragment_code}
    }, 2);

    static float data[] = {
            0, 0, 1, 0, 0, 1
    };
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(data),
                 data,
                 GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    // unbind
    glBindVertexArray(0);
}

void astronaut_render() {

    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}
