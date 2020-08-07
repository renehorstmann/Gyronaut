#include <stdbool.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "r/r.h"
#include "camera.h"
#include "input.h"
#include "game.h"

#ifdef __EMSCRIPTEN__
const Uint32 sdl_init_flags = SDL_INIT_VIDEO;
#else
const Uint32 sdl_init_flags = SDL_INIT_EVERYTHING;
#endif

static SDL_Window *window;
static Uint32 last_time;
static bool running;
static void main_loop();

int main() {
    puts("Gyronaut");

    if(SDL_Init(sdl_init_flags) != 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed: %s", SDL_GetError());
        return 1;
    }
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
    
    // initialize IMG
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "IMG_Init failed: %s", IMG_GetError());
        return 1;
    }
    
    // initialize TTF
    if (TTF_Init() == -1) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init failed: %s", TTF_GetError());
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
    window = SDL_CreateWindow("Gyronaut",
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
    SDL_GL_SetSwapInterval(1);  // (0=off, 1=V-Sync, -1=addaptive V-Sync)


    int max_vertex_attributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vertex_attributes);
    if(max_vertex_attributes < 16) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                "OpenGL failed: only has %d/16 vertex attributes", max_vertex_attributes);
        return 1;
    }


    // init
    r_setup_blending();
    r_text_default_font = TTF_OpenFont("res/fnf.ttf", 64);
    input_init();
    camera_init();
    game_init();



    last_time = SDL_GetTicks();
    running = true;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, true);
#else
    while (running)
        main_loop();
#endif

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


static void main_loop() {
    // delta time
    Uint32 time = SDL_GetTicks();
    float dtime = (time - last_time) / 1000.0f;
    last_time = time;

    // current window size
    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    // inputs
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                running = false;
                return;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONUP:
            case SDL_FINGERDOWN:
            case SDL_FINGERMOTION:
            case SDL_FINGERUP:
                input_handle_pointer(&event);
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                input_handle_keys(&event);
                break;
            case SDL_SENSORUPDATE:
                input_handle_sensors(&event);
                break;
        }
    }

    // simulate
    game_update(dtime);
    camera_update(width, height);

    // r
    glClearColor(1.0f, 0.5f * rand() / RAND_MAX, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    game_render();

    // Swap buffers
    SDL_GL_SwapWindow(window);

    // check for opengl errors:
    {
        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR)
            SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, "got an glError in this frame: 0x%04x", err);
    }
}


