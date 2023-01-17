#include "sglr_render_target.h"

sglr_RenderTarget sglr_make_render_target(int32_t width, int32_t height, int32_t samples,
                                               GLenum color_format,
                                               GLenum depth_format){
  sglr_RenderTarget rt;
  N1_ZERO_MEMORY(&rt);

  rt.type    = SGLR_RENDER_TARGET_TYPE_SINGLE_LAYER;
  rt.width   = width;
  rt.height  = height;
  rt.depth   = 1;
  rt.samples = samples;
  
  GLuint color_id_0 = 0;
  GLuint color_id_1 = 0;
  GLuint depth_id = 0;
  
  // === color ===
  if(color_format != GL_NONE){
    glGenTextures(1, &color_id_0);
    glGenTextures(1, &color_id_1);
    
    sglr_check_error();

    if(samples){

      // attachment 0
      glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, color_id_0);
      glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, color_format, width, height, GL_TRUE); 
      glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
      sglr_check_error();

      sglr_set_texture_debug_name_from_id(color_id_0, "rt_attachment_0");
      
      rt.color_attachment_0.id     = color_id_0;
      rt.color_attachment_0.format = color_format;
      rt.color_attachment_0.type   = GL_TEXTURE_2D_MULTISAMPLE;
      
      // attachment 1
      glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, color_id_1);
      glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGBA16F, width, height, GL_TRUE); 
      glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
      sglr_check_error();
      
      sglr_set_texture_debug_name_from_id(color_id_1, "rt_attachment_1");
      
      rt.color_attachment_1.id     = color_id_1;
      rt.color_attachment_1.format = GL_RGBA16F;
      rt.color_attachment_1.type   = GL_TEXTURE_2D_MULTISAMPLE;
      
    }else{

      // attachment 0
      glBindTexture(GL_TEXTURE_2D, color_id_0);
      glTexImage2D(GL_TEXTURE_2D, 0, color_format, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
      
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glBindTexture(GL_TEXTURE_2D, 0);
      sglr_check_error();

      rt.color_attachment_0.id     = color_id_0;
      rt.color_attachment_0.format = color_format;
      rt.color_attachment_0.type   = GL_TEXTURE_2D;
    

      // attachment 1
      glBindTexture(GL_TEXTURE_2D, color_id_1);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
      
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glBindTexture(GL_TEXTURE_2D, 0);
      sglr_check_error();
   
      rt.color_attachment_1.id     = color_id_1;
      rt.color_attachment_1.format = GL_RGBA16F;
      rt.color_attachment_1.type   = GL_TEXTURE_2D;
    }
            
  }  
  // === depth ===

  if(depth_format != GL_NONE){
    glGenTextures(1, &depth_id);
    sglr_check_error();


    if(samples){
      glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, depth_id);
      glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, depth_format, width, height, GL_TRUE); 
      glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
      sglr_check_error();

      rt.depth_attachment.format = depth_format;
      rt.depth_attachment.id     = depth_id;
      rt.depth_attachment.type   = GL_TEXTURE_2D_MULTISAMPLE;
      
    }else{
      glBindTexture(GL_TEXTURE_2D, depth_id);
      glTexImage2D(GL_TEXTURE_2D, 0, depth_format, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glBindTexture(GL_TEXTURE_2D, 0);
      sglr_check_error();

      rt.depth_attachment.format = depth_format;
      rt.depth_attachment.id     = depth_id;
      rt.depth_attachment.type   = GL_TEXTURE_2D;
    }
  }
  
  // === framebuffer attachments ===
  glGenFramebuffers(1, &rt.id);
  sglr_check_error();
  
  glBindFramebuffer(GL_FRAMEBUFFER, rt.id);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  if(color_id_0){
    glNamedFramebufferTexture(rt.id,
                              GL_COLOR_ATTACHMENT0,
                              color_id_0,
                              0);

  }
  if(color_id_1){
    glNamedFramebufferTexture(rt.id,
                              GL_COLOR_ATTACHMENT1,
                              color_id_1,
                              0);

  }
  
  if(depth_id){
    glNamedFramebufferTexture(rt.id,
                              GL_DEPTH_ATTACHMENT,
                              depth_id,
                              0);
    sglr_check_error();
  }
  
  return rt;
}

sglr_RenderTarget sglr_make_render_target_layered(int32_t width, int32_t height, int32_t depth,
                                                  GLenum color_format,
                                                  GLenum depth_format){
  sglr_RenderTarget rt;
  N1_ZERO_MEMORY(&rt);

  rt.type   = SGLR_RENDER_TARGET_TYPE_MULTI_LAYER;
  rt.width  = width;
  rt.height = height;
  rt.depth  = depth;
  rt.samples = 0;
  
  GLuint color_id_0 = 0;
  GLuint depth_id = 0;
  
  // === color ===
  if(color_format != GL_NONE){
    glGenTextures(1, &color_id_0);
    sglr_check_error();
    
    rt.color_attachment_0.format = color_format;
    rt.color_attachment_0.id     = color_id_0;
    
    glBindTexture(GL_TEXTURE_2D_ARRAY, color_id_0);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, color_format, width, height, depth, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
      
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    sglr_check_error();
    
    rt.color_attachment_0.format = depth_format;
    rt.color_attachment_0.id     = color_id_0;
    rt.color_attachment_0.type   = GL_TEXTURE_2D_ARRAY;
      
  }  
  // === depth ===

  if(depth_format != GL_NONE){
    glGenTextures(1, &depth_id);
    sglr_check_error();

    rt.depth_attachment.format = depth_format;
    rt.depth_attachment.id     = depth_id;
    
    glBindTexture(GL_TEXTURE_2D_ARRAY, depth_id);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, depth_format, width, height, depth, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    sglr_check_error();

    
    rt.depth_attachment.format = depth_format;
    rt.depth_attachment.id     = depth_id;
    rt.depth_attachment.type   = GL_TEXTURE_2D_ARRAY;
      
  }
  
  // === framebuffer attachments ===
  glGenFramebuffers(1, &rt.id);
  sglr_check_error();
  
  glBindFramebuffer(GL_FRAMEBUFFER, rt.id);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  
  glNamedFramebufferTexture(rt.id,
                            GL_COLOR_ATTACHMENT0,
                            color_id_0,
                            0);
  
  glNamedFramebufferTexture(rt.id,
                            GL_DEPTH_ATTACHMENT,
                            depth_id,
                            0);
  sglr_check_error();
  
  return rt;
}
sglr_RenderTarget sglr_make_main_render_target(int32_t width, int32_t height, int32_t samples,
                                               GLenum color_format,
                                               GLenum depth_format){
  sglr_Context* context = sglr_current_context();
  context->main_render_target = sglr_make_render_target(width, height, samples, color_format, depth_format);
  sglr_set_render_target_debug_name(sglr_main_render_target(), "main_rt");
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
    GLenum  color_format = rt.color_attachment_0.format;
    GLenum  depth_format = rt.depth_attachment.format;
    
    sglr_free_render_target(rt);
    sglr_make_main_render_target(width, height, samples, color_format, depth_format);
    sglr_check_error();
  }
}

void sglr_free_render_target(sglr_RenderTarget target){
  if(target.color_attachment_0.id){
    glDeleteTextures(1, &target.color_attachment_0.id);
    sglr_check_error();
  }

  if(target.color_attachment_1.id){
    glDeleteTextures(1, &target.color_attachment_1.id);
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

void sglr_set_render_target_debug_name(sglr_RenderTarget target, const char* name){
  glObjectLabel(GL_FRAMEBUFFER,
                target.id,
                strlen(name),
                name);
  sglr_check_error();
}

void sglr_set_clear_color_u32_rgba(uint32_t rgba){

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

void sglr_set_clear_depth(float value){
  
  glClearDepth(value);
  sglr_check_error();
}

void sglr_clear_render_target_depth(){
  glDepthMask(GL_TRUE);
  glClear(GL_DEPTH_BUFFER_BIT);
  
  sglr_check_error();
}

void sglr_clear_render_target_color(){
  glDrawBuffer(GL_COLOR_ATTACHMENT0);
  glClear(GL_COLOR_BUFFER_BIT);

  glClearColor(inf32, inf32, inf32, inf32);
  glDrawBuffer(GL_COLOR_ATTACHMENT1);
  glClear(GL_COLOR_BUFFER_BIT);

  sglr_check_error();
}
