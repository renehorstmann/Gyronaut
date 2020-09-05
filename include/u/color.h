#ifndef U_COLOR_H
#define U_COLOR_H

#include "mathc/types/float.h"

// rgb[0:1] hsv[0:360, 0:1, 0:1]
vec3 u_rgb2hsv(vec3 rgb);


// rgb[0:1] hsv[0:360, 0:1, 0:1]
vec3 u_hsv2rgb(vec3 hsv);

#endif // U_COLOR_H
