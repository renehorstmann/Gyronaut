#include "cglm/cglm.h"
#include "utilc/assume.h"
#include "inputs.h"
#include "camera.h"

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

static void to_perspective(int wnd_x, int wnd_y, float *x, float *y) {
	const int *wnd_size = camera_get_wnd_size();
	vec4 pos;
	pos[0] = (2.0f * wnd_x) / wnd_size[0] - 1.0f;
	pos[1] = 1.0f - (2.0f * wnd_y) / wnd_size[1];
	pos[2] = 0;
	pos[3] = 1;
	
	vec4 res;
	glm_mat4_mulv(camera_get_p_inv(), pos, res);
	*x = res[0];
	*y = res[1];
}

static Pointer_s pointer_init(enum PointerAction action) {
	Pointer_s res;
	res.action = action;
	
	int x, y;
	SDL_GetMouseState(&x, &y);
	
	to_perspective(x, y, &res.x, &res.y);
	return res;
}

void input_init() {

}

void input_handle_event(SDL_Event *event) {
    switch (event->type) {
        case SDL_MOUSEBUTTONDOWN: {
            Pointer_s action = pointer_init(POINTER_DOWN);
            for(int i=0; i<reg_pointer_e_size; i++)
                reg_pointer_e[i].cb(action, reg_pointer_e[i].ud);
        } break;
        case SDL_MOUSEMOTION: {
            Pointer_s action = pointer_init(POINTER_MOVE);
            for(int i=0; i<reg_pointer_e_size; i++)
                reg_pointer_e[i].cb(action, reg_pointer_e[i].ud);
        } break;
        case SDL_MOUSEBUTTONUP: {
            Pointer_s action = pointer_init(POINTER_UP);
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
