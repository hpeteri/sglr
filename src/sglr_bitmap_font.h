#ifndef SGLR_BITMAP_FONT_H
#define SGLR_BITMAP_FONT_H

#include "sglr_texture.h"
typedef struct sglr_BitmapFont{
  sglr_Texture texture;
  
} sglr_BitmapFont;

sglr_BitmapFont sglr_make_bitmap_font_builtin();

#endif
