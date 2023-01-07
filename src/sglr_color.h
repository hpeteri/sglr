#ifndef SGLR_COLOR_H
#define SGLR_COLOR_H

#include <stdint.h>

#define  sglr_color_black  ( 0xff000000 )
#define  sglr_color_white  ( ~0;        )
#define  sglr_color_red    ( 0xff0000ff )
#define  sglr_color_green  ( 0xff00ff00 )
#define  sglr_color_blue   ( 0xffff0000 )
#define  sglr_color_yellow ( 0xff00ffff )
#define  sglr_color_cyan   ( 0xffffff00 )
#define  sglr_color_purple ( 0xffff00ff )

uint32_t sglr_inverse_gamma(uint32_t  rgba, float gamma);

#endif
