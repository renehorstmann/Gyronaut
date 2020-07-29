//#define DEBUG
#include "cglm/cglm.h"
#include "render/render.h"
#include "camera.h"


mat3 view;
mat4 projection;


const float *camera_get_view() {
    return &view[0][0];
}
const float *camera_get_projection() {
    return &projection[0][0];
}


void camera_init() {
    glm_mat3_identity(view);
    glm_mat4_identity(projection);
}

void camera_update(int wnd_width, int wnd_height) {
    float width, height;
    if(wnd_width > wnd_height) {
        height = 200;
        width = 200 * wnd_width / wnd_height;
    } else {
        width = 200;
        height = 200 * wnd_height / wnd_width;
    }

    glm_ortho(-width/2, width/2, -height/2, height/2, -1, 1, projection);
}
