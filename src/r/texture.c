#include <SDL_image.h>
#include "r/texture.h"

GLuint r_texture_from_img(SDL_Surface *img) {
	SDL_PixelFormat *f = img->format;

    GLenum in_format = 0;

    if(f->Rmask == 0xff && f->Gmask == 0xff00 && f->Bmask == 0xff0000) {
        if(f->Amask == 0)
            in_format = GL_RGB;
        else if(f->Amask == 0xff000000)
            in_format = GL_RGBA;
    }

    if(f->Rmask == 0xff0000 && f->Gmask == 0xff00 && f->Bmask == 0xff) {
        if(f->Amask == 0)
            in_format = GL_BGR;
        else if(f->Amask == 0xff000000)
            in_format = GL_BGRA;
    }

    if (!in_format) {
        SDL_LogCritical(SDL_LOG_CATEGORY_RENDER,
                "load tex failed: wrong format, needed GL_RGB(A) or GL_BGR(A)");
        return 0;
    }

    GLenum out_format = f->Amask != 0 ? GL_RGBA : GL_RGB;

    // todo:
    if(out_format == GL_RGB) {
        SDL_LogWarn(SDL_LOG_CATEGORY_RENDER,
                "load tex may have failed, no alpha channel");
    }

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    // GL_REPEAT is already default...
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, out_format, img->w, img->h, 0, in_format, GL_UNSIGNED_BYTE, img->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    return tex;
}


GLuint r_texture_from_file(const char *file) {
    SDL_Surface *img = IMG_Load(file);
    if (!img) {
        SDL_LogCritical(SDL_LOG_CATEGORY_RENDER,
                "load image (%s) failed: %s", file, IMG_GetError());
        return 0;
    }
    
    GLuint tex = r_texture_from_img(img);
    SDL_FreeSurface(img);
    return tex;
}
