#ifndef GYRONAUT_INPUTS_H
#define GYRONAUT_INPUTS_H

#include <SDL.h>

enum TouchAction {TOUCH_DOWN, TOUCH_MOVE, TOUCH_UP};

struct Touch {
    enum TouchAction action;
    float x, y;
};

void input_handle_event(SDL_Event *event);

#endif //GYRONAUT_INPUTS_H
