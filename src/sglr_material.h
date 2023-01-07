#ifndef SGLR_MATERIAL_H
#define SGLR_MATERIAL_H

#include "sglr_shader.h"

typedef struct sglr_MaterialTextureBinding{
  GLenum type;
  GLuint id;
} sglr_MaterialTextureBinding;
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
  
  GLuint light_info;
} sglr_Material;

sglr_Material sglr_make_material(sglr_Shader shader);
sglr_Material sglr_copy_material(sglr_Material material);

void sglr_set_material(sglr_Material material);

void sglr_set_material_texture_i(sglr_Material* material, int index, GLenum texture_type, GLuint texture_id);

void sglr_set_material_light_info(sglr_Material* material, GLuint buffer_id);
#endif
