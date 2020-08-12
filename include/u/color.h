#ifndef U_COLOR_H
#define U_COLOR_H

#include "cglm/types.h"

// rgb[0:1] hsv[0:360, 0:1, 0:1]
void u_rgb2hsv(const vec3 rgb, vec3 dst_hsv);


// rgb[0:1] hsv[0:360, 0:1, 0:1]
void u_hsv2rgb(const vec3 hsv, vec3 dst_rgb);

#endif // U_COLOR_H
