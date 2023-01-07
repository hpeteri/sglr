#include "sglr_material.h"

sglr_Material sglr_make_material(sglr_Shader shader){
  sglr_Material material;
  N1_ZERO_MEMORY(&material);

  material.shader = shader;

  return material;
}
sglr_Material sglr_copy_material(sglr_Material material){
  sglr_Material copy = material;

  return copy;
}

void sglr_set_material(sglr_Material material){
  sglr_set_shader(material.shader);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, material.texture_0);

  sglr_check_error();

}

void sglr_set_material_texture_0(sglr_Material* material, GLuint texture_id){
  material->texture_0 = texture_id;
}
