#include "sglr_color.h"

uint32_t sglr_inverse_gamma(uint32_t color, float gamma){
  float r   = (color & 0xff) / 255.0f;
  float   g = ((color >> 8) & 0xff) / 255.0f;
  float   b = ((color >> 16) & 0xff) / 255.0f;
  float   a = ((color >> 24) & 0xff) / 255.0f;

  r = pow(r, gamma);
  g = pow(g, gamma);
  b = pow(b, gamma);

  uint8_t r8 = (uint8_t)(r * 255); 
  uint8_t g8 = (uint8_t)(g * 255); 
  uint8_t b8 = (uint8_t)(b * 255);
  uint8_t a8 = (uint8_t)(a * 255);
 
  
  return r8 | (g8 << 8) | (b8 << 16) | (a8 << 24);
}
