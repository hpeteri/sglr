#ifndef SGLR_COLOR_H
#define SGLR_COLOR_H

#include <stdint.h>
typedef uint32_t sglr_rgba32;

sglr_rgba32 sglr_inverse_gamma(sglr_rgba32 rgba, float gamma);

#endif
