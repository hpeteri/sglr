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
  sglr_set_material_2(material, 0);
}
void sglr_set_material_2(sglr_Material material, int is_compute){
  sglr_set_shader(material.shader);

  if(!is_compute){
    for(int i = 0; i < 4; i++){
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(material.textures[i].type, material.textures[i].id);
      GLint loc = material.shader.texture_locs[i];
      if(loc != (int32_t)GL_INVALID_INDEX){
        glUniform1i(loc, i);
        sglr_check_error();
      }
    }

  }else{
    for(int i = 0; i < 4; i++){
      
      if(material.textures[i].id == 0)
        continue;
      
      if(material.textures[i].format == GL_NONE){
        printf("\n");
        printf("!!! set_compute_pipeline: texture format is GL_NONE!\n");
        printf("!!! use sglr_set_material_format_texture_i to specify texture format\n");
      }
  
      glBindImageTexture(i,
                         material.textures[i].id,
                         0,
                         GL_FALSE,
                         0,
                         GL_WRITE_ONLY,
                         material.textures[i].format);
  
      sglr_check_error();
    }
  }
  
  for(int i = 0; i < 4; i++){
    GLint loc = material.shader.buffer_locs[i];
    if(loc != (int32_t)GL_INVALID_INDEX){
      glBindBufferBase(GL_UNIFORM_BUFFER, loc, material.buffers[i].id);
      sglr_check_error();  
    }
  }

  sglr_check_error();  
}

void sglr_set_material_sampler_i(sglr_Material* material, int index, sglr_Texture texture){

  if(texture.type == GL_NONE){
    printf("assertion failed: texture type is GL_NONE!\n");
    *(int*)NULL = 0;
  }
  material->textures[index].type   = texture.type;
  material->textures[index].id     = texture.id;
  material->textures[index].format = texture.format;

}

void sglr_set_material_sampler_i_2(sglr_Material* material, int index, GLenum texture_type, GLuint texture_id){

  if(texture_type == GL_NONE){
    printf("assertion failed: texture type is GL_NONE!\n");
    *(int*)NULL = 0;
  }
  
  material->textures[index].type   = texture_type;
  material->textures[index].id     = texture_id;
  material->textures[index].format = GL_NONE; 

}

void sglr_set_material_image_i(sglr_Material* material, int index, sglr_Texture texture){
  
  material->textures[index].type   = texture.type;
  material->textures[index].id     = texture.id;
  material->textures[index].format = texture.format;
}

void sglr_set_material_buffer_i(sglr_Material* material, int index, sglr_Buffer buffer){
  material->buffers[index].id = buffer.id;
}


