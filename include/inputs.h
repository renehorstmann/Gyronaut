#ifndef GYRONAUT_INPUTS_H
#define GYRONAUT_INPUTS_H

#include <stdbool.h>
#include <SDL.h>


extern bool input_up_pressed;
extern bool input_left_pressed;
extern bool input_right_pressed;
extern bool input_down_pressed;
extern bool input_enter_pressed;
extern bool input_space_pressed;

enum PointerAction {POINTER_DOWN, POINTER_MOVE, POINTER_UP, POINTER_NUM_ACTIONS};

typedef struct Pointer_s {
    float x, y;
    enum PointerAction action;
    int id;
} Pointer_s;

void input_init();

void input_handle_pointer(SDL_Event *event);

void input_handle_keys(SDL_Event *event);

void input_register_pointer_event(void (*on_pointer_event)(Pointer_s, void *), void *user_data);

#endif //GYRONAUT_INPUTS_H
