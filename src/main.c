#include <stdbool.h>
#include <SDL2/SDL.h>

#include "opengl_example.h"

int main() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    // setup OpenGL usage
    SDL_Log("OpenGL minimal version: %d.%d", GYRONAUT_OPENGL_MAJOR_VERSION, GYRONAUT_OPENGL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GYRONAUT_OPENGL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GYRONAUT_OPENGL_MINOR_VERSION);

    // 8 bits per color
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

    // create window
    SDL_Window *window = SDL_CreateWindow("Gyronaut",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            640, 480,
            SDL_WINDOW_OPENGL);
    if (!window) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow failed: %s", SDL_GetError());
        return 1;
    }

    // Not necessary, but recommended to create a gl context:
    SDL_GL_CreateContext(window);


    //
    // opengl example:
    //

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

    //
    // opengl example end
    //

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

