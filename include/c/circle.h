#ifndef C_CIRCLE_H
#define C_CIRCLE_H

#include "math.h"
#include "stdbool.h"
#include "core.h"


typedef struct cCircle_s {
	float x, y, r;
} cCircle_s;


static bool c_circle_oo(cCircle_s a, cCircle_s b) {
	float d_sqr = powf(b.x-a.x, 2) + powf(b.y-a.y, 2);
	return d_sqr < powf(a.r+b.r, 2);
}


cIndices_s c_circle_og(cCircle_s a, const cCircle_s *b, int n, int ignore);


#endif //C_CIRCLE_H
