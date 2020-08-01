#include "utilc/assume.h"
#include "input.h"
#include "camera.h"

#define MAX_POINTER_EVENTS 32


bool input_up;
bool input_left;
bool input_right;
bool input_down;
bool input_enter;
bool input_space;


bool input_rotation_active;
float input_actual_rotation;


static struct {
    void (*cb)(Pointer_s, void *);

    void *ud;
} reg_pointer_e[MAX_POINTER_EVENTS];

static int reg_pointer_e_size = 0;

static void to_perspective(float gl_x, float gl_y, float *x, float *y) {
    vec4s res = glms_mat4_mulv(camera_p_inv, (vec4s) {gl_x, gl_y, 0, 1});
    *x = res.x;
    *y = res.y;
}

static Pointer_s pointer_mouse(enum PointerAction action) {
    Pointer_s res;
    res.action = action;
    res.id = 0;

    int x, y;
    SDL_GetMouseState(&x, &y);

    float gl_x = (2.0f * x) / camera_wnd_size[0] - 1.0f;
    float gl_y = 1.0f - (2.0f * y) / camera_wnd_size[1];

    to_perspective(gl_x, gl_y, &res.x, &res.y);
    return res;
}

static Pointer_s pointer_finger(enum PointerAction action, float x, float y, int finger_id) {
    Pointer_s res;
    res.action = action;
    res.id = finger_id;

    float gl_x = 2.0f * x - 1.0f;
    float gl_y = 1.0f - 2.0f * y;

    to_perspective(gl_x, gl_y, &res.x, &res.y);
    return res;
}

void input_init() {
	int num_sensors = SDL_NumSensors();
	bool accel_opened = false;
	for(int i=0; i<num_sensors; i++) {
		if (SDL_SensorGetDeviceType(i) == SDL_SENSOR_ACCEL) {
            SDL_Sensor *sensor = SDL_SensorOpen(i);
            if (sensor) {
                accel_opened = true;
                break;
            }
		}
	}
	
	input_rotation_active = accel_opened;
	if(accel_opened)
	    SDL_Log("opened accel sensor");
}

void input_handle_pointer(SDL_Event *event) {
    switch (event->type) {
#ifdef R_GLES
        case SDL_FINGERDOWN: {
            Pointer_s action = pointer_finger(POINTER_DOWN,
                                              event->tfinger.x, event->tfinger.y, event->tfinger.fingerId);
            for (int i = 0; i < reg_pointer_e_size; i++)
                reg_pointer_e[i].cb(action, reg_pointer_e[i].ud);
        }
            break;
        case SDL_FINGERMOTION: {
            Pointer_s action = pointer_finger(POINTER_MOVE,
                                              event->tfinger.x, event->tfinger.y, event->tfinger.fingerId);
            for (int i = 0; i < reg_pointer_e_size; i++)
                reg_pointer_e[i].cb(action, reg_pointer_e[i].ud);
        }
            break;
        case SDL_FINGERUP: {
            Pointer_s action = pointer_finger(POINTER_UP,
                                              event->tfinger.x, event->tfinger.y, event->tfinger.fingerId);
            for (int i = 0; i < reg_pointer_e_size; i++)
                reg_pointer_e[i].cb(action, reg_pointer_e[i].ud);
        }
            break;
#else
        case SDL_MOUSEBUTTONDOWN: {
            Pointer_s action = pointer_mouse(POINTER_DOWN);
            for (int i = 0; i < reg_pointer_e_size; i++)
                reg_pointer_e[i].cb(action, reg_pointer_e[i].ud);
        }
            break;
        case SDL_MOUSEMOTION: {
            Pointer_s action = pointer_mouse(POINTER_MOVE);
            for (int i = 0; i < reg_pointer_e_size; i++)
                reg_pointer_e[i].cb(action, reg_pointer_e[i].ud);
        }
            break;
        case SDL_MOUSEBUTTONUP: {
            Pointer_s action = pointer_mouse(POINTER_UP);
            for (int i = 0; i < reg_pointer_e_size; i++)
                reg_pointer_e[i].cb(action, reg_pointer_e[i].ud);
        }
            break;
#endif
    }
}

void input_handle_keys(SDL_Event *event) {
    bool down = event->type == SDL_KEYDOWN;
    switch (event->key.keysym.sym) {
        case SDLK_UP:
            input_up = down;
            break;
        case SDLK_LEFT:
            input_left = down;
            break;
        case SDLK_RIGHT:
            input_right = down;
            break;
        case SDLK_DOWN:
            input_down = down;
            break;
        case SDLK_RETURN:
            input_enter = down;
            break;
        case SDLK_SPACE:
            input_space = down;
            break;
    }
}



void input_handle_sensors(SDL_Event *event) {
	SDL_Sensor *sensor = SDL_SensorFromInstanceID(event->sensor.which);
    if (!sensor
        || SDL_SensorGetType(sensor) != SDL_SENSOR_ACCEL) {
        SDL_LogWarn(SDL_LOG_CATEGORY_INPUT, "Couldn't get sensor for sensor event\n");
        return;
    }
    
    const float *data = event->sensor.data;
    float alpha = atan2(data[1], data[0]);
    input_actual_rotation = alpha;
    
    //SDL_Log("Gyro update: %.2f, %.2f, %.2f\n", data[0], data[1], data[2]);
      
}

void input_register_pointer_event(void (*on_pointer_event)(Pointer_s, void *), void *user_data) {
    assume(reg_pointer_e_size < MAX_POINTER_EVENTS, "too many registered pointer events");
    reg_pointer_e[reg_pointer_e_size].cb = on_pointer_event;
    reg_pointer_e[reg_pointer_e_size++].ud = user_data;
}
