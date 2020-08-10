#ifndef GYRONAUT_CONTROLLER_H
#define GYRONAUT_CONTROLLER_H

#include <stdbool.h>


void controller_init(bool use_accel);

void controller_update(float dtime);


#endif //GYRONAUT_CONTROLLER_H
