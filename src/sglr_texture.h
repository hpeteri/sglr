#ifndef SGLR_TEXTURE_H
#define SGLR_TEXTURE_H

typedef struct sglr_Texture{
  GLuint id;

  GLenum type;

  uint32_t width;
  uint32_t height;
  
} sglr_Texture;

sglr_Texture sglr_make_texture_2d_rgba(uint32_t width, uint32_t height, void* data);
sglr_Texture sglr_make_texture_2d_red(uint32_t width, uint32_t height, void* data);

void         sglr_free_texture(sglr_Texture texture);
void         sglr_set_texture(sglr_Texture texture);
void         sglr_unset_texture(GLenum type);

void         sglr_set_texture_debug_name(sglr_Texture texture, const char* name);
#endif
