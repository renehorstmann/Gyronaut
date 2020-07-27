#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "astronaut.h"

#ifdef GYRONAUT_GLES
#define PRECISION "precision mediump float;\n"
#else
#define PRECISION ""
#endif

static const char *vertex_code =
        "#version 330\n"
        "layout(location = 0) in vec2 position;"
        "void main() {"
        "  gl_Position = vec4(position.x, position.y, 0, 1);"
        "}";

static const char *fragment_code =
        "#version 330 \n"
        "void main() {"
        "  gl_FragColor = vec4(0, 1, 0, 1);"
        "}";

static GLuint vao;
static GLuint vbo;
static GLuint program;

static GLuint create_shader(GLint type, const char *src) {
    GLint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        int log_len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);

        char *buffer = malloc(log_len + 1);
        glGetShaderInfoLog(shader, log_len, NULL, buffer);
        printf("Compile failure in %s shader: %s", type == GL_VERTEX_SHADER ? "vertex" : "fragment", buffer);
        free(buffer);

        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

static void compile() {
    GLuint vertex = create_shader(GL_VERTEX_SHADER, vertex_code);
    GLuint fragment = create_shader(GL_FRAGMENT_SHADER, fragment_code);

    // Combine shaders into program
    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        int log_len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);

        char *buffer = malloc(log_len + 1);
        glGetProgramInfoLog(program, log_len, NULL, buffer);
        printf("Linking failure: %s", buffer);
        free(buffer);

        glDeleteProgram(program);
        program = 0;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void astronaut_init() {
    compile();

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
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}
