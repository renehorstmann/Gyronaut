#include "utilc/assume.h"
#include "inputs.h"

#define MAX_POINTER_EVENTS 32

static struct {
    void (*cb)(Pointer_s, void *);
    void *ud;
} reg_pointer_e[MAX_POINTER_EVENTS];
static int reg_pointer_e_size = 0;


// todo
static float from_pixel_x(int x) {
    return 0;
}
static float from_pixel_y(int y) {
    return 0;
}

void input_init() {

}

void input_handle_event(SDL_Event *event) {

//If mouse event happened
//    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
//    {
//        //Get mouse position
//        int x, y;
//        SDL_GetMouseState( &x, &y );

    switch (event->type) {
        case SDL_MOUSEBUTTONDOWN: {
            int x, y;
            SDL_GetMouseState(&x, &y);
            Pointer_s action = {POINTER_DOWN, from_pixel_x(x), from_pixel_y(y)};
            for(int i=0; i<reg_pointer_e_size; i++)
                reg_pointer_e[i].cb(action, reg_pointer_e[i].ud);
        } break;
        case SDL_MOUSEMOTION: {
            int x, y;
            SDL_GetMouseState(&x, &y);
            Pointer_s action = {POINTER_MOVE, from_pixel_x(x), from_pixel_y(y)};
            for(int i=0; i<reg_pointer_e_size; i++)
                reg_pointer_e[i].cb(action, reg_pointer_e[i].ud);
        } break;
        case SDL_MOUSEBUTTONUP: {
            int x, y;
            SDL_GetMouseState(&x, &y);
            Pointer_s action = {POINTER_UP, from_pixel_x(x), from_pixel_y(y)};
            for(int i=0; i<reg_pointer_e_size; i++)
                reg_pointer_e[i].cb(action, reg_pointer_e[i].ud);
        } break;
    }
}

void input_register_pointer_event(void (*on_pointer_event)(Pointer_s, void *), void *user_data) {
    assume(reg_pointer_e_size < MAX_POINTER_EVENTS, "too many registered pointer events");
    reg_pointer_e[reg_pointer_e_size].cb = on_pointer_event;
    reg_pointer_e[reg_pointer_e_size++].ud = user_data;
}
