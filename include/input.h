#ifndef GYRONAUT_INPUT_H
#define GYRONAUT_INPUT_H

#include <stdbool.h>
#include <SDL.h>


extern bool input_up;
extern bool input_left;
extern bool input_right;
extern bool input_down;
extern bool input_enter;
extern bool input_space;

extern bool input_rotation_active;
extern float input_actual_rotation;


enum PointerAction {POINTER_DOWN, POINTER_MOVE, POINTER_UP, POINTER_NUM_ACTIONS};

typedef struct Pointer_s {
    float x, y;
    enum PointerAction action;
    int id;
} Pointer_s;

void input_init();

void input_handle_pointer(SDL_Event *event);

void input_handle_keys(SDL_Event *event);

void input_handle_sensors(SDL_Event *event);

void input_register_pointer_event(void (*on_pointer_event)(Pointer_s, void *), void *user_data);

#endif //GYRONAUT_INPUT_H
