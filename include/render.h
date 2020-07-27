#ifndef GYRONAUT_RENDER_H
#define GYRONAUT_RENDER_H

#include <stdbool.h>
#include <SDL2/SDL.h>


void r_init();


void r_render(double delta_time, int wnd_width, int wnd_height);


#endif //GYRONAUT_RENDER_H
