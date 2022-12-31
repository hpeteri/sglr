#include "sglr_texture.h"
#include "sglr_log.h"

sglr_Texture sglr_make_texture_2d_rgba(uint32_t width, uint32_t height, void* data){
  sglr_Texture texture;
  N1_ZERO_MEMORY(&texture);  
  
  glGenTextures(1, &texture.id);
  sglr_check_error();

  texture.type = GL_TEXTURE_2D;

  sglr_set_texture(texture);

  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_SRGB_ALPHA,
               width,
               height,
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               data);
  sglr_check_error();

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  sglr_unset_texture(GL_TEXTURE_2D);
  
  return texture;
}

sglr_Texture sglr_make_texture_2d_red(uint32_t width, uint32_t height, void* data){
  sglr_Texture texture;
  N1_ZERO_MEMORY(&texture);  
  
  glGenTextures(1, &texture.id);
  sglr_check_error();

  texture.type = GL_TEXTURE_2D;
  
  sglr_set_texture(texture);

  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_R8,
               width,
               height,
               0,
               GL_RED,
               GL_UNSIGNED_BYTE,
               data);
  
  sglr_check_error();

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  sglr_unset_texture(GL_TEXTURE_2D);
  
  return texture;  
}
void sglr_free_texture(sglr_Texture texture){
  glDeleteTextures(1, &texture.id);
  sglr_check_error();  
}

void sglr_set_texture(sglr_Texture texture){
  glBindTexture(texture.type, texture.id);
  sglr_check_error();
}

void sglr_unset_texture(GLenum type){
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
