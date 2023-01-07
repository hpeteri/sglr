#ifndef SGLR_BITMAP_FONT_H
#define SGLR_BITMAP_FONT_H

#include "sglr_texture.h"
typedef struct sglr_BitmapFont{
  sglr_Texture texture;
  
} sglr_BitmapFont;

sglr_BitmapFont sglr_make_bitmap_font_builtin();

float sglr_text_height(float scale);
vec2 sglr_text_size(const char* text, float scale);

vec2 sglr_text_size_n(const char* text, size_t len, float scale);

#endif
