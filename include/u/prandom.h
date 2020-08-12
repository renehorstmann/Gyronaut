#ifndef U_PRANDOM_H
#define U_PRANDOM_H

#include <stdint.h>

static const uint32_t U_PRAND_MAX = 0x0fffffff;

uint32_t u_prand();

float u_prandf();

#endif //U_PRANDOM_H
