
#include "cglm/types.h"
#include "u/color.h"


// rgb[0:1] hsv[0:360, 0:1, 0:1]
void u_rgb2hsv(const vec3 rgb, vec3 dst_hsv) {
    // copied from stackoverflow
    float min, max, delta;

    min = rgb[0] < rgb[1] ? rgb[0] : rgb[1];
    min = min  < rgb[2] ? min  : rgb[2];

    max = rgb[0] > rgb[1] ? rgb[0] : rgb[1];
    max = max  > rgb[2] ? max  : rgb[2];

    dst_hsv[2] = max;
    delta = max - min;
    if (delta < 0.00001f) {
        dst_hsv[0] = 0; // undifined
        dst_hsv[1] = 0;
        return;
    }
    if( max > 0.0 ) { 
        // NOTE: if Max is == 0, this divide would cause a crash
        dst_hsv[1] = (delta / max);
    } else {
        // if max is 0, then r = g = b = 0              
        // s = 0, h is undefined
        dst_hsv[0] = 0;
        dst_hsv[1] = 0;
        return;
    }
    if(rgb[0] >= max )                           
        // > is bogus, just keeps compilor happy
        dst_hsv[0] = (rgb[1] - rgb[2]) / delta;        
        // between yellow & magenta
    else if(rgb[1] >= max )
        dst_hsv[0] = 2.0 + (rgb[2] - rgb[0]) / delta;  
        // between cyan & yellow
    else
        dst_hsv[0] = 4.0 + (rgb[0] - rgb[1]) / delta;  
        // between magenta & cyan

    dst_hsv[0] *= 60.0; // degrees

    if(dst_hsv[0] < 0)
        dst_hsv[0] += 360.0;
}

// rgb[0:1] hsv[0:360, 0:1, 0:1]
void u_hsv2rgb(const vec3 hsv, vec3 dst_rgb) {
    // copied from stackoverflow
    float hh, p, q, t, ff;
    long i;

    if(hsv[1] <= 0.0) {       
        // < is bogus, just shuts up warnings
        dst_rgb[0] = hsv[2];
        dst_rgb[1] = hsv[2];
        dst_rgb[2] = hsv[2];
        return;
    }
    hh = hsv[0];
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = hsv[2] * (1.0 - hsv[1]);
    q = hsv[2] * (1.0 - (hsv[1] * ff));
    t = hsv[2] * (1.0 - (hsv[1] * (1.0 - ff)));

    switch(i) {
    case 0:
        dst_rgb[0] = hsv[2];
        dst_rgb[1] = t;
        dst_rgb[2] = p;
        break;
    case 1:
        dst_rgb[0] = q;
        dst_rgb[1] = hsv[2];
        dst_rgb[2] = p;
        break;
    case 2:
        dst_rgb[0] = p;
        dst_rgb[1] = hsv[2];
        dst_rgb[2] = t;
        break;

    case 3:
        dst_rgb[0] = p;
        dst_rgb[1] = q;
        dst_rgb[2] = hsv[2];
        break;
    case 4:
        dst_rgb[0] = t;
        dst_rgb[1] = p;
        dst_rgb[2] = hsv[2];
        break;
    case 5:
    default:
        dst_rgb[0] = hsv[2];
        dst_rgb[1] = p;
        dst_rgb[2] = q;
        break;
    }
}
