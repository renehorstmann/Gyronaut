#include <SDL.h>
#include <SDL_image.h>
#include "utilc/strviu.h"
#include "gl_utils.h"



static char *file_read(const char *filename) {
    SDL_RWops *rw = SDL_RWFromFile(filename, "rb");
    if (rw == NULL) return NULL;

    Sint64 res_size = SDL_RWsize(rw);
    char *res = (char *) malloc(res_size + 1);

    Sint64 nb_read_total = 0, nb_read = 1;
    char *buf = res;
    while (nb_read_total < res_size && nb_read != 0) {
        nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
        nb_read_total += nb_read;
        buf += nb_read;
    }
    SDL_RWclose(rw);
    if (nb_read_total != res_size) {
        free(res);
        return NULL;
    }

    res[nb_read_total] = '\0';
    return res;
}


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
        printf("Compile failure in %s shader: %s", type == GL_VERTEX_SHADER ? "vertex_s" : "fragment", buffer);
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


GLuint compile_shader_from_file(const char *file) {
    GLint type;
    const char *shader_begin;
    {
        strviu viu = ToStrViu(file);
        if (sv_ends_with_cstring(viu, ".vsh")) {
            type = GL_VERTEX_SHADER;
            shader_begin = R_VERTEX;
        } else if (sv_ends_with_cstring(viu, ".fsh")) {
            type = GL_FRAGMENT_SHADER;
            shader_begin = R_FRAGMENT;
        } else {
            SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                            "compile shader failed, neither .vsh nor .fsh: %s", file);
            return 0;
        }
    }

    char *src = file_read(file);
    if (!src) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                        "load shader file %s failed: %s", file, SDL_GetError());
        return 0;
    }


    char *shader = malloc(strlen(shader_begin) + strlen(src) + 1);
    strcpy(shader, shader_begin);
    strcat(shader, src);


    GLint out = compile_shader(type, shader);
    free(src);
    free(shader);
    return out;
}

GLuint compile_glsl_from_files(char **files) {
    int n = -1;
    while(files[++n]);

    GLuint program = 0;
    GLuint shaders[n];

    // Compile shaders
    for (int i = 0; i < n; i++) {
        shaders[i] = compile_shader_from_file(files[i]);
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
    if (f->Rmask != 0xff || f->Gmask != 0xff00 || f->Bmask != 0xff0000 || (f->Amask != 0 && f->Amask != 0xff000000)) {
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
