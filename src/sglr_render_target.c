#include "sglr_render_target.h"

sglr_RenderTarget sglr_make_main_render_target(int32_t width, int32_t height, int32_t samples,
                                               GLenum color_format,
                                               GLenum depth_format){
  sglr_Context* context = sglr_current_context();
  sglr_RenderTarget rt = context->main_render_target;
  
  GLuint color_id = 0;
  GLuint depth_id = 0;
  
  // === color ===
  {
  
    glGenTextures(1, &color_id);
    sglr_check_error();
    
    rt.color_attachment.format = color_format;
    rt.color_attachment.id     = color_id;
    rt.samples                 = samples;
    
    if(samples){
      glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, color_id);
      glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, color_format, width, height, GL_TRUE); 
      glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
      sglr_check_error();
    
    }else{
      glBindTexture(GL_TEXTURE_2D, color_id);
      glTexImage2D(GL_TEXTURE_2D, 0, color_format, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
      glBindTexture(GL_TEXTURE_2D, 0);
      sglr_check_error();
    }
  }
  
  // === depth ===
  if(depth_format){
    glGenTextures(1, &depth_id);
    sglr_check_error();

    rt.depth_attachment.format = depth_format;
    rt.depth_attachment.id     = depth_id;

    if(samples){
      glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, depth_id);
      glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, depth_format, width, height, GL_TRUE); 
      glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
      sglr_check_error();
    
    }else{
      glBindTexture(GL_TEXTURE_2D, depth_id);
      glTexImage2D(GL_TEXTURE_2D, 0, depth_format, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_BYTE, 0);
      glBindTexture(GL_TEXTURE_2D, 0);
      sglr_check_error();
    }
  }
  
  // === framebuffer attachments ===
  glGenFramebuffers(1, &rt.id);
  sglr_check_error();
  
  glBindFramebuffer(GL_FRAMEBUFFER, rt.id);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  
  glNamedFramebufferTexture(rt.id,
                            GL_COLOR_ATTACHMENT0,
                            color_id,
                            0);

  glNamedFramebufferTexture(rt.id,
                            GL_DEPTH_ATTACHMENT,
                            depth_id,
                            0);
  sglr_check_error();
  
  context->main_render_target = rt;
  
  GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if(status != GL_FRAMEBUFFER_COMPLETE){
    sglr_check_error;
    asm ("int3");
  }
  
  return context->main_render_target;  
}
sglr_RenderTarget sglr_main_render_target(){
  sglr_Context* context = sglr_current_context();

  return context->main_render_target;
}

void sglr_blit_main_render_target(int32_t width, int32_t height, GLenum filter){
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  
  sglr_RenderTarget render_target = sglr_main_render_target();
  if(render_target.id != 0){
    
    glBlitNamedFramebuffer(render_target.id,
                           0,
                           0, 0,
                           render_target.width,
                           render_target.height,
                           0, 0,
                           width,
                           height,
                           GL_COLOR_BUFFER_BIT,
                           filter);
    
    sglr_check_error();
  }
}
void sglr_resize_main_render_target(int32_t width, int32_t height){
  sglr_Context* context = sglr_current_context();
  
  context->main_render_target.width  = width;
  context->main_render_target.height = height;

  if(context->main_render_target.id){
    sglr_RenderTarget rt = context->main_render_target;
    
    uint8_t samples      = rt.samples;
    GLenum  color_format = rt.color_attachment.format;
    GLenum  depth_format = rt.depth_attachment.format;
    
    sglr_free_render_target(rt);
    sglr_make_main_render_target(width, height, samples, color_format, depth_format);
    sglr_check_error();
  }
}

void sglr_free_render_target(sglr_RenderTarget target){
  if(target.color_attachment.id){
    glDeleteTextures(1, &target.color_attachment.id);
    sglr_check_error();
  }

  if(target.depth_attachment.id){
    glDeleteTextures(1, &target.depth_attachment.id);
    sglr_check_error();
  }

  if(target.id){
    glDeleteFramebuffers(1, &target.id);
    sglr_check_error();
  }
}
                                                                    
                                                                    
void sglr_set_render_target(sglr_RenderTarget target){
  glBindFramebuffer(GL_FRAMEBUFFER, target.id);
  glViewport(0, 0, target.width, target.height);
  sglr_check_error();
}

void sglr_set_clear_color_i32_rgba(int32_t rgba){
  const float r = (rgba & 0xff) / 255.0f;
  const float g = ((rgba >> 8) & 0xff) / 255.0f;
  const float b = ((rgba >> 16) & 0xff) / 255.0f;
  const float a = ((rgba >> 24) & 0xff) / 255.0f;
 
  glClearColor(r, g, b, a);
  sglr_check_error();
}

void sglr_set_clear_color_4f_rgba(float r, float g, float b, float a){  
  glClearColor(r, g, b, a);
  sglr_check_error();
}
void sglr_clear_render_target_depth(){
  glClear(GL_DEPTH_BUFFER_BIT);
  sglr_check_error();
}
void sglr_clear_render_target_color(){
  glClear(GL_COLOR_BUFFER_BIT);
  sglr_check_error();
}
