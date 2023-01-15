#include "sglr_texture.h"
#include "sglr_log.h"

sglr_Texture sglr_make_texture_2d(uint32_t width, uint32_t height,
                                  GLenum internal_format,
                                  GLenum data_format, GLenum data_type, void* data){
  sglr_Texture texture;
  N1_ZERO_MEMORY(&texture);  

  texture.type = GL_TEXTURE_2D;
  texture.width  = width;
  texture.height = height;
  texture.depth = 1;
  
  glGenTextures(1, &texture.id);
  sglr_check_error();
  
  sglr_set_texture(texture);
  
  glTexImage2D(GL_TEXTURE_2D,
               0,
               internal_format,
               width,
               height,
               0,
               data_format,
               data_type,
               data);
  
    
  sglr_set_texture_min_filter(texture, GL_NEAREST);
  sglr_set_texture_mag_filter(texture, GL_NEAREST);
  
  sglr_set_texture_wrap(texture, GL_CLAMP_TO_EDGE);
  
  sglr_unset_texture(texture);
  
  return texture;
}

sglr_Texture sglr_make_texture_2d_array(uint32_t width, uint32_t height, uint32_t depth, GLenum internal_format){
  sglr_Texture texture;
  N1_ZERO_MEMORY(&texture);
  
  texture.type = GL_TEXTURE_2D_ARRAY;
  texture.width  = width;
  texture.height = height;
  texture.depth = depth;
    
  glGenTextures(1, &texture.id);
  sglr_check_error();
  
  sglr_set_texture(texture);

  int32_t x;
  
  glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &x);
  printf("GL_MAX_3D_TEXTURE_SIZE: %d\n", x);
  
  glTexStorage3D(GL_TEXTURE_2D_ARRAY,
                 1,
                 internal_format,
                 width,
                 height,
                 depth);

  sglr_check_error();

  sglr_set_texture_min_filter(texture, GL_NEAREST);
  sglr_set_texture_mag_filter(texture, GL_NEAREST);
  sglr_set_texture_wrap(texture, GL_CLAMP_TO_EDGE);
  
  sglr_unset_texture(texture);

  
  return texture;
  
}

void sglr_make_texture_mipmap(sglr_Texture texture){
  glGenerateTextureMipmap(texture.id);
  sglr_check_error();
}
void sglr_set_texture_wrap(sglr_Texture texture, GLenum mode){

  glTexParameteri(texture.type, GL_TEXTURE_WRAP_S, mode);
  glTexParameteri(texture.type, GL_TEXTURE_WRAP_T, mode);
  glTexParameteri(texture.type, GL_TEXTURE_WRAP_R, mode);
  
  sglr_check_error();
}
void sglr_set_texture_swizzle(sglr_Texture texture, GLint component, GLint swizzle){
  glTexParameteri(texture.type, component, swizzle);
  sglr_check_error();
}

void sglr_set_texture_min_filter(sglr_Texture texture, GLenum mode){
  glTexParameteri(texture.type, GL_TEXTURE_MIN_FILTER, mode);
  sglr_check_error();
}

void sglr_set_texture_mag_filter(sglr_Texture texture, GLenum mode){
  glTexParameteri(texture.type, GL_TEXTURE_MAG_FILTER, mode);
  sglr_check_error();  
}

void sglr_free_texture(sglr_Texture texture){
  glDeleteTextures(1, &texture.id);
  sglr_check_error();  
}

void sglr_set_texture(sglr_Texture texture){
  glBindTexture(texture.type, texture.id);
  sglr_check_error();
}

void sglr_unset_texture(sglr_Texture texture){
  glBindTexture(texture.type, 0);
  sglr_check_error();
}

void sglr_unset_texture_by_type(GLenum type){
  glBindTexture(type, 0);
  sglr_check_error();
}

void sglr_set_texture_debug_name(sglr_Texture texture, const char* name){
  glObjectLabel(GL_TEXTURE,
                texture.id,
                strlen(name),
                name);
  sglr_check_error();
}


void sglr_set_texture_debug_name_from_id(GLuint id, const char* name){
  glObjectLabel(GL_TEXTURE,
                id,
                strlen(name),
                name);
  sglr_check_error();
  
}
