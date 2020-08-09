#include "e/e.h"
#include "r/r.h"

#include "camera.h"
#include "game.h"

static Uint32 last_time;
static void main_loop();

int main() {
    puts("Gyronaut");
    
    e_window_init("Gyronaut");
    e_input_init();

    r_render_init();

    // init
    r_text_default_font = TTF_OpenFont("res/fnf.ttf", 64);
    camera_init();
    game_init();


    last_time = SDL_GetTicks();

    e_window_main_loop(main_loop);
    
    return 0;
}


static void main_loop() {
    // delta time
    Uint32 time = SDL_GetTicks();
    float dtime = (time - last_time) / 1000.0f;
    last_time = time;
    
    e_window_update();
    e_input_update();
    

    // simulate
    game_update(dtime);
    camera_update();

    // r
    glClearColor(1.0f, 0.5f * rand() / RAND_MAX, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    game_render();

    // Swap buffers
    SDL_GL_SwapWindow(e_window);

    // check for opengl errors:
    r_render_error_check();
}


