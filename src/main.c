#include <stdbool.h>
#include "gl.h"

#include "astronaut.h"

int main() {
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    // setup OpenGL usage
    SDL_Log("OpenGL minimal version: %d.%d", R_GL_MAJOR_VERSION, R_GL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, R_GL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, R_GL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, R_GL_PROFILE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

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

    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    SDL_Log("window size: %dx%d", width, height);

    // Not necessary, but recommended to create a gl context:
    SDL_GL_CreateContext(window);

    SDL_Log("OpenGL version: %s", glGetString(GL_VERSION));

    //
    // opengl example:
    //

    astronaut_init();
    // Initialize triangle renderer
//    triangle_init();

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
//        triangle_render(SDL_GetTicks());

        astronaut_render();

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

