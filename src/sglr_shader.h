#ifndef SGLR_SHADER_H
#define SGLR_SHADER_H

#include "cmath/n1_cmath.h"

typedef struct sglr_Shader{
  GLuint id;
  
  GLuint vertex_id;
  GLuint fragment_id;

  int pos_loc;
  int tc_loc;
  int color_loc;
  int norm_loc;
  
  int model_loc;
  
} sglr_Shader;

sglr_Shader sglr_make_shader(const char* vertex, const char* fragment);

sglr_Shader sglr_make_shader_builtin_simple();
sglr_Shader sglr_make_shader_builtin_text();
sglr_Shader sglr_make_shader_builtin_pbr();
sglr_Shader sglr_make_shader_builtin_depth_only();

void        sglr_free_shader(sglr_Shader shader);
void        sglr_set_shader(sglr_Shader shader);
void        sglr_unset_shader();

//uniform access
void sglr_set_uniform_mat4(sglr_Shader shader, const char* name, mat4 mat);

void sglr_set_shader_debug_name(sglr_Shader shader, const char* name);

#endif
