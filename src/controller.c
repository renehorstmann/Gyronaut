#include "utilc/assume.h"
#include "e/input.h"
#include "camera.h"
#include "astronaut.h"
#include "controller.h"


static bool rot_left = false;
static bool rot_right = false;

static void pointer(ePointer_s p, void *ud) {
    if (rot_left) {
        if (p.action == E_POINTER_UP || p.x > -25)
            rot_left = false;
    } else {
        if (p.action == E_POINTER_DOWN && p.x < -25)
            rot_left = true;
    }
    if (rot_right) {
        if (p.action == E_POINTER_UP || p.x < 25)
            rot_right = false;
    } else {
        if (p.action == E_POINTER_DOWN && p.x > 25)
            rot_right = true;
    }
}


static const float a_mean = 0.9f;
static const float cam_mean = 0.8f;


static bool accel;
static float ax, ay;
static float target;

void controller_init(int input_method) {

    if (input_method == 1)
        e_input_register_pointer_event(pointer, NULL);

    if (input_method == 2) {
        assume(e_input_accel_active, "Accel not available");
        ax = e_input_accel[0];
        ay = e_input_accel[1];
    }
    accel = input_method == 2;

}

void controller_update(float dtime) {
    if (accel) {
        ax = ax * a_mean + e_input_accel[0] * (1.0f - a_mean);
        ay = ay * a_mean + e_input_accel[1] * (1.0f - a_mean);

        float rot = atan2f(ay, ax);

        target = rot - M_PI_2;
    } else {
        if (e_input_left || rot_left)
            target += M_PI_2 * dtime;
        if (e_input_right || rot_right)
            target -= M_PI_2 * dtime;

        static float cam_target = 0;
        cam_target = cam_mean * cam_target + (1.0f - cam_mean) * target;
        camera_set_angle(cam_target);
    }

    astronaut_rotate(target);
}
