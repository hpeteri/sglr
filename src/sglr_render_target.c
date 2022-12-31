#include "sglr_render_target.h"

sglr_RenderTarget sglr_main_render_target(){
  sglr_Context* context = sglr_current_context();
  //context might be NULL, but in this we case we want to crash anyways...
  return context->main_render_target;  
}

void sglr_resize_main_render_target(int32_t width, int32_t height){
  sglr_Context* context = sglr_current_context();

  context->main_render_target.width  = width;
  context->main_render_target.height = height;
  
}

void sglr_set_render_target(sglr_RenderTarget target){
  //todo
}

void sglr_set_clear_color_i32(int32_t rgba){
  const float r = (rgba & 0xff) / 255.0f;
  const float g = ((rgba >> 8) & 0xff) / 255.0f;
  const float b = ((rgba >> 16) & 0xff) / 255.0f;
  const float a = ((rgba >> 24) & 0xff) / 255.0f;
 
  glClearColor(r, g, b, a);                                             
}

void sglr_set_clear_color_4f(float r, float g, float b, float a){  
  glClearColor(r, g, b, a);                                             
}

void sglr_clear_render_target_color(){
  glClear(GL_COLOR_BUFFER_BIT);
}
