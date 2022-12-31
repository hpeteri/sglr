#ifndef SGLR_RENDER_TARGET_H
#define SGLR_RENDER_TARGET_H

#include "GL/gl.h"

#include <stdint.h>

typedef struct sglr_RenderTarget{
  int32_t width;
  int32_t height;

  GLenum id;
} sglr_RenderTarget;

sglr_RenderTarget sglr_main_render_target();
void              sglr_resize_main_render_target(int32_t width, int32_t height);

void sglr_set_render_target(sglr_RenderTarget target);


void sglr_set_clear_color_i32(int32_t rgba);
void sglr_set_clear_color_4f(float r, float g, float b, float a);
void sglr_clear_render_target_color();
#endif
