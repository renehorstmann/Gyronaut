#include "gl.h"


GLuint compile_shader(GLint type, const char *src) {
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


GLuint compile_glsl(shader_source *sources, int n) {
    GLuint program = 0;
    GLuint shaders[n];

    // Compile shaders
    for(int i=0; i<n; i++) {
        shaders[i] = compile_shader(sources[i].type, sources[i].src);
        if(shaders[i] == 0) {
            n = i;  // delete previous compiled shaders
            goto CLEAN_UP;
        }
    }

    // Combine shaders into program
    program = glCreateProgram();
    for(int i=0; i<n; i++)
        glAttachShader(program, shaders[i]);
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

    CLEAN_UP:
    for(int i=0; i<n; i++)
        glDeleteShader(shaders[i]);

    return program;
}
