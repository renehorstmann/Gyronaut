#ifndef GYRONAUT_ASTRONAUT_H
#define GYRONAUT_ASTRONAUT_H

void astronaut_init();

void astronaut_update(float dtime);

void astronaut_render();

// in [%]
void astronaut_rotate(float alpha_destination);

#endif //GYRONAUT_ASTRONAUT_H
