#include "mathc/mathc.h"
#include "e/e.h"
#include "r/r.h"
#include "u/u.h"

#include "camera.h"
#include "game.h"


static void main_loop(float dtime);


int main() {
    puts("Gyronaut");
    
    e_window_init("Gyronaut");
    e_input_init();

    r_render_init(e_window);

    // init
    r_text_default_font = TTF_OpenFont("res/fnf.ttf", 64);
    camera_init();
    game_init();

    e_window_main_loop(main_loop);
    
    return 0;
}


static void main_loop(float delta_time) {
    
    e_window_update();
    e_input_update();
    

    // simulate
    game_update(delta_time);
    camera_update();

    // render
    r_render_begin_frame();
    
    game_render();

    // swap buffers
    r_render_end_frame();
    

    // check for opengl errors:
    r_render_error_check();
}


