#ifndef SGLR_MATERIAL_H
#define SGLR_MATERIAL_H

#include "sglr_shader.h"
#include "sglr_texture.h"
typedef struct sglr_MaterialTextureBinding{
  GLenum      type;
  GLuint      id;
  GLenum      format;
} sglr_MaterialTextureBinding;

typedef struct sglr_UniformBufferBinding{
  GLuint id;
} sglr_UniformBufferBinding;

typedef struct sglr_Material{
  sglr_Shader shader;
  
  union{
    struct {
      sglr_MaterialTextureBinding texture_0;
      sglr_MaterialTextureBinding texture_1;
      sglr_MaterialTextureBinding texture_2;
      sglr_MaterialTextureBinding texture_3;
    };
    sglr_MaterialTextureBinding textures[4];
  };

  union {
    struct{
      sglr_UniformBufferBinding buffer_0;
      sglr_UniformBufferBinding buffer_1;
      sglr_UniformBufferBinding buffer_2;
      sglr_UniformBufferBinding buffer_3;
    };
    sglr_UniformBufferBinding buffers[4];
  };
} sglr_Material;

sglr_Material sglr_make_material(sglr_Shader shader);
sglr_Material sglr_copy_material(sglr_Material material);

void sglr_set_material(sglr_Material material);
void sglr_set_material_2(sglr_Material material, int is_compute);

//sampler
void sglr_set_material_sampler_i(sglr_Material* material, int index, sglr_Texture texture);
void sglr_set_material_sampler_i_2(sglr_Material* material, int index, GLenum texture_type, GLuint texture_id);

//image
void sglr_set_material_image_i(sglr_Material* material, int index, sglr_Texture texture);

//buffer
void sglr_set_material_buffer_i(sglr_Material* material, int index, sglr_Buffer buffer);

#endif
