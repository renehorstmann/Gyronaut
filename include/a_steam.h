#ifndef GYRONAUT_A_STEAM_H
#define GYRONAUT_A_STEAM_H

#include "mathc/types/float.h"

void a_steam_init();

void a_steam_update(float dtime, mat4 pose, float curve);

void a_steam_render();

#endif //GYRONAUT_A_STEAM_H
