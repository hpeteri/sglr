#ifndef SGLR_RENDER_TARGET_H
#define SGLR_RENDER_TARGET_H

#include "GL/gl.h"

#include <stdint.h>

typedef enum SGLR_RENDER_TARGET_TYPE{

  SGLR_RENDER_TARGET_TYPE_SINGLE_LAYER = 0,
  SGLR_RENDER_TARGET_TYPE_MULTI_LAYER,

} SGLR_RENDER_TARGET_TYPE;

typedef struct sglr_RenderTargetAttachment{

  GLenum type;
  GLint  id;
  GLenum format;
  
} sglr_RenderTargetAttachment;

typedef struct sglr_RenderTarget{

  int32_t width;
  int32_t height;
  int32_t depth;

  int8_t samples;

  SGLR_RENDER_TARGET_TYPE type;
  
  sglr_RenderTargetAttachment color_attachment_0;
  sglr_RenderTargetAttachment color_attachment_1; //gbuffer for shadows
  
  sglr_RenderTargetAttachment depth_attachment;
  
  GLint id;

} sglr_RenderTarget;

sglr_RenderTarget sglr_make_render_target(int32_t width, int32_t height, int32_t samples,
                                          GLenum color_format,
                                          GLenum depth_format);

sglr_RenderTarget sglr_make_render_target_layered(int32_t width, int32_t height, int32_t depth,
                                                  GLenum color_format,
                                                  GLenum depth_format);
                                                  

sglr_RenderTarget sglr_make_main_render_target(int32_t width, int32_t height, int32_t samples,
                                               GLenum color_format,
                                               GLenum depth_format);

sglr_RenderTarget sglr_main_render_target();
void              sglr_blit_main_render_target(int32_t width, int32_t height, GLenum filter);
void              sglr_resize_main_render_target(int32_t width, int32_t height);
void              sglr_free_render_target(sglr_RenderTarget target);
void              sglr_set_render_target(sglr_RenderTarget target);

void sglr_set_render_target_debug_name(sglr_RenderTarget target, const char* name);

void sglr_set_clear_color_u32_rgba(uint32_t color);
void sglr_set_clear_color_4f_rgba(float r, float g, float b, float a);
void sglr_set_clear_depth(float value);

void sglr_clear_render_target_depth();
void sglr_clear_render_target_color();
#endif
