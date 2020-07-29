#include <stdbool.h>
#include <SDL_image.h>
#include "gl.h"
#include "camera.h"
#include "astronaut.h"

int main() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed: %s", SDL_GetError());
        return 1;
    }
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "IMG_Init failed: %s", IMG_GetError());
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

    // Not necessary, but recommended to create a gl context:
    SDL_GL_CreateContext(window);
    SDL_Log("OpenGL version: %s", glGetString(GL_VERSION));


    // init
    setup_blending();
    camera_init();
    astronaut_init();


    Uint32 last_time = SDL_GetTicks();
    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT)
                goto BYE;

            // Process events so the app doesn't hang
        }

        int width, height;
        SDL_GetWindowSize(window, &width, &height);

        Uint32 time = SDL_GetTicks();
        double dtime = (time - last_time) / 1000.0;
        last_time = time;


        // simulate
        camera_update(width, height);

        astronaut_update(dtime);

        // render
        glClearColor(1.0f, 0.5f * rand() / RAND_MAX, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        astronaut_render();

        // Swap buffers
        SDL_GL_SwapWindow(window);
    }
    BYE:


    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

