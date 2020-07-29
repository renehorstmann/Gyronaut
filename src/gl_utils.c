#include <SDL_image.h>
#include "gl_utils.h"

void setup_blending() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

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
    for (int i = 0; i < n; i++) {
        shaders[i] = compile_shader(sources[i].type, sources[i].src);
        if (shaders[i] == 0) {
            n = i;  // delete previous compiled shaders
            goto CLEAN_UP;
        }
    }

    // Combine shaders into program
    program = glCreateProgram();
    for (int i = 0; i < n; i++)
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
    for (int i = 0; i < n; i++)
        glDeleteShader(shaders[i]);

    return program;
}

GLuint load_texture_from_file(const char *file) {
    SDL_Surface *img = IMG_Load(file);
    if (!img) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "load image failed: %s", IMG_GetError());
        return 0;
    }
    SDL_PixelFormat *f = img->format;
    if(f->Rmask != 0xff || f->Gmask != 0xff00 || f->Bmask != 0xff0000 || (f->Amask!= 0 && f->Amask!=0xff000000)) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "load tex failed: wrong format (8bit/col needed)");
        return 0;
    }

    GLenum format = f->Amask != 0 ? GL_RGBA : GL_RGB;

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    // GL_REPEAT is already default...
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, format, GL_UNSIGNED_BYTE, img->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    SDL_FreeSurface(img);
    return tex;
}
