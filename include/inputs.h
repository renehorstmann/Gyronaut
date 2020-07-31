#ifndef GYRONAUT_INPUTS_H
#define GYRONAUT_INPUTS_H

#include <SDL.h>

enum PointerAction {POINTER_DOWN, POINTER_MOVE, POINTER_UP, POINTER_NUM_ACTIONS};

typedef struct Pointer_s {
    float x, y;
    enum PointerAction action;
    int id;
} Pointer_s;

void input_init();

void input_handle_event(SDL_Event *event);

void input_register_pointer_event(void (*on_pointer_event)(Pointer_s, void *), void *user_data);

#endif //GYRONAUT_INPUTS_H
