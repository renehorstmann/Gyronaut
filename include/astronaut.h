#ifndef GYRONAUT_ASTRONAUT_H
#define GYRONAUT_ASTRONAUT_H

void astronaut_init();

void astronaut_update(float dtime);

void astronaut_render();

// in [%]
void astronaut_rotate(float angular_speed);

#endif //GYRONAUT_ASTRONAUT_H
