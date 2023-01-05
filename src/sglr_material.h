#ifndef SGLR_MATERIAL_H
#define SGLR_MATERIAL_H

#include "sglr_shader.h"
typedef struct sglr_Material{
  sglr_Shader shader;
  GLuint texture_0;
} sglr_Material;

sglr_Material sglr_make_material(sglr_Shader shader);
sglr_Material sglr_copy_material(sglr_Material material);

void sglr_set_material(sglr_Material material);

void sglr_set_material_texture_0(sglr_Material* material, GLuint texture_id);

#endif
