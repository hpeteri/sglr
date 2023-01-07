#include "sglr_material.h"

sglr_Material sglr_make_material(sglr_Shader shader){
  sglr_Material material;
  N1_ZERO_MEMORY(&material);

  material.shader = shader;

  for(int i = 0; i < 4; i++){
    material.textures[i].type = GL_TEXTURE_2D;
  }

  return material;
}
sglr_Material sglr_copy_material(sglr_Material material){
  sglr_Material copy = material;

  return copy;
}

void sglr_set_material(sglr_Material material){
  sglr_set_shader(material.shader);


  const char* texture_names[4] = {
    "texture0",
    "texture1",
    "texture2",
    "texture3",
  };

  for(int i = 0; i < 4; i++){
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(material.textures[i].type, material.textures[i].id);
    glUniform1i(glGetUniformLocation(material.shader.id, texture_names[i]), i);;
    sglr_check_error();
  }

  #if 0
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(material.textures[0].type, material.textures[0].id);
  glUniform1i(glGetUniformLocation(material.shader.id, "texture0"), 0);
  sglr_check_error();
  
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(material.textures[1].type, material.textures[1].id);
  glUniform1i(glGetUniformLocation(material.shader.id, "texture1"), 1);
  sglr_check_error();
  #endif
  
  GLuint light_info_loc = glGetUniformBlockIndex(material.shader.id, "LightInfo");
  if(light_info_loc != GL_INVALID_INDEX){
    //@todo, check that buffers on cpu and gpu are the same size
    //glBindBuffer(GL_UNIFORM_BUFFER, material.light_info);
    glBindBufferBase(GL_UNIFORM_BUFFER, light_info_loc, material.light_info);
    
    sglr_check_error();
  }
  sglr_check_error();

}

void sglr_set_material_texture_i(sglr_Material* material, int index, GLenum texture_type, GLuint texture_id){
  material->textures[index].type = texture_type;
  material->textures[index].id   = texture_id;
}

void sglr_set_material_light_info(sglr_Material* material, GLuint buffer_id){
  material->light_info = buffer_id;
}
