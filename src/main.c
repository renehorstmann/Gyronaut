#include <stdbool.h>
#include <SDL2/SDL.h>

#include "opengl_example.h"

int main() {

    SDL_Init(SDL_INIT_EVERYTHING);  // != 0 test

    SDL_Log("Hello World");
    SDL_Log("Hello Too");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GYRONAUT_OPENGL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GYRONAUT_OPENGL_MINOR_VERSION);

    // We want at least 8 bits per color
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

    SDL_Window *window = SDL_CreateWindow("Hello SDL2 OpenGL ES", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }

    // We will not actually need a context created, but we should create one
    SDL_GL_CreateContext(window);

    // Initialize triangle renderer
    triangle_init();

    while (true)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                goto BYE;
            // Process events so the app doesn't hang
        }
        // Draw triangle
        triangle_render(SDL_GetTicks());
        // Swap buffers
        SDL_GL_SwapWindow(window);
    }
    BYE:

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

