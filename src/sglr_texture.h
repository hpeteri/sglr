#ifndef SGLR_TEXTURE_H
#define SGLR_TEXTURE_H

typedef struct sglr_Texture{
  GLuint id;

  GLenum type;
  GLenum format;
  
  uint32_t width;
  uint32_t height;
  uint32_t depth;
  
} sglr_Texture;

sglr_Texture sglr_make_texture_2d(uint32_t width, uint32_t height,
                                  GLenum internal_format,
                                  GLenum data_format, GLenum data_type, void* data);

sglr_Texture sglr_make_texture_2d_array(uint32_t width, uint32_t height, uint32_t depth,
                                        GLenum internal_format);

void sglr_make_texture_mipmap(sglr_Texture texture);
void sglr_set_texture_wrap(sglr_Texture texture, GLenum mode);
void sglr_set_texture_swizzle(sglr_Texture texture, GLint component, GLint swizzle);
void sglr_set_texture_min_filter(sglr_Texture texture, GLenum mode);
void sglr_set_texture_mag_filter(sglr_Texture texture, GLenum mode);



void sglr_free_texture(sglr_Texture texture);

void sglr_set_texture(sglr_Texture texture);
void sglr_unset_texture(sglr_Texture texture);
void sglr_unset_texture_by_type(GLenum type);


void sglr_set_texture_debug_name(sglr_Texture texture, const char* name);
void sglr_set_texture_debug_name_from_id(GLuint id, const char* name);
#endif
