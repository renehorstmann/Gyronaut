#ifndef GYRONAUT_ASTRONAUT_H
#define GYRONAUT_ASTRONAUT_H

static const float ASTRONAUT_W = 10;
static const float ASTRONAUT_H = 20;


void astronaut_init();

void astronaut_update(float dtime);

void astronaut_render();

void astronaut_rotate(float alpha_destination);

#endif //GYRONAUT_ASTRONAUT_H
