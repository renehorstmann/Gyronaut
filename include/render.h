#ifndef GYRONAUT_RENDER_H
#define GYRONAUT_RENDER_H

#include <stdbool.h>
#include <SDL2/SDL.h>


void render_init();

void render_update(int wnd_with, int wnd_height, float *world_pose);

void render_hud_mode();


#endif //GYRONAUT_RENDER_H
