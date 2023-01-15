#include "sglr_shader.h"
#include "sglr_shader_builtin.c"


static int sglr_check_shader_module(const GLuint module, const char* desc){
  int success = 0;
  glGetShaderiv(module, GL_COMPILE_STATUS, &success);
  
  if(success)
    return 1;
  
  char buffer[1024];
  glGetShaderInfoLog(module, 1024, NULL, buffer);

  printf("error in stage: '%s'\n", desc);
  printf("%s\n", buffer);
  printf("\n");

  return 0;
}

static int sglr_check_shader_link(const GLuint shader){
  int success = 0;
  glGetProgramiv(shader, GL_LINK_STATUS, &success);
  if(success)
    return 1;
  
  char buffer[1024];
  glGetProgramInfoLog(shader, 1024, NULL, buffer);

  printf("%s\n", buffer);
  printf("\n");
  
  return 0;
}
sglr_Shader sglr_make_shader(const char* vertex,
                             const char* tesselation_control,
                             const char* tesselation_eval,
                             const char* geometry,
                             const char* fragment){
  sglr_Shader shader;
  N1_ZERO_MEMORY(&shader);

  if(vertex == NULL && fragment == NULL){
    return shader;
  }

  shader.id = glCreateProgram();
  sglr_check_error();
  
  //vertex
  shader.vertex_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(shader.vertex_id, 1, &vertex, NULL);
  glCompileShader(shader.vertex_id);
  if(!sglr_check_shader_module(shader.vertex_id, "vertex")){

    sglr_check_error();
    return shader;
  }
  
  sglr_check_error();
  
  //fragment
  shader.fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shader.fragment_id, 1, &fragment, NULL);
  glCompileShader(shader.fragment_id);
  if(!sglr_check_shader_module(shader.fragment_id, "fragment")){
    sglr_check_error();
    return shader;
  }
  
  sglr_check_error();

  //geometry
  if(geometry){
    shader.geometry_id = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(shader.geometry_id, 1, &geometry, NULL);
    glCompileShader(shader.geometry_id);
    if(!sglr_check_shader_module(shader.geometry_id, "geometry")){
      sglr_check_error();
      return shader;
    }
  
    sglr_check_error();
  }

  //tesselation_control
  if(tesselation_control){
    shader.tesselation_control_id = glCreateShader(GL_TESS_CONTROL_SHADER);
    glShaderSource(shader.tesselation_control_id, 1, &tesselation_control, NULL);
    glCompileShader(shader.tesselation_control_id);
    if(!sglr_check_shader_module(shader.tesselation_control_id, "tesselation control")){
      sglr_check_error();
      return shader;
    }
  
    sglr_check_error();
  }

  //tesselation
  if(tesselation_eval){
    shader.tesselation_eval_id = glCreateShader(GL_TESS_EVALUATION_SHADER);
    glShaderSource(shader.tesselation_eval_id, 1, &tesselation_eval, NULL);
    glCompileShader(shader.tesselation_eval_id);
    if(!sglr_check_shader_module(shader.tesselation_eval_id, "tesselation eval")){
      sglr_check_error();
      return shader;
    }
  
    sglr_check_error();
  }

  
  //link
  glAttachShader(shader.id, shader.vertex_id);
  glAttachShader(shader.id, shader.fragment_id);
  if(geometry){
    glAttachShader(shader.id, shader.geometry_id);
  }
  if(tesselation_control){
    glAttachShader(shader.id, shader.tesselation_control_id);
  }
  if(tesselation_eval){
    glAttachShader(shader.id, shader.tesselation_eval_id);
  }

  glLinkProgram(shader.id);
  sglr_set_shader(shader);
  sglr_check_error();
  
  if(!sglr_check_shader_link(shader.id)){
    sglr_check_error();
    *(int*)NULL = 0;
    return shader;
  }


  //query locations
  shader.pos_loc   = glGetAttribLocation(shader.id, "vert_pos");
  shader.tc_loc    = glGetAttribLocation(shader.id, "vert_tc");
  shader.color_loc = glGetAttribLocation(shader.id, "vert_color");
  shader.norm_loc  = glGetAttribLocation(shader.id, "vert_norm");

  sglr_check_error();
  
  shader.model_loc   = glGetAttribLocation(shader.id, "model");
  sglr_check_error();

  return shader;
}

void sglr_free_shader(sglr_Shader shader){

  if(shader.vertex_id){
    glDeleteShader(shader.vertex_id);
    sglr_check_error();
  }
  if(shader.fragment_id){
    glDeleteShader(shader.fragment_id);
    sglr_check_error();
  }
  if(shader.geometry_id){
    glDeleteShader(shader.geometry_id);
    sglr_check_error();
  }
  if(shader.tesselation_control_id){
    glDeleteShader(shader.tesselation_control_id);
    sglr_check_error();
  }
  if(shader.tesselation_eval_id){
    glDeleteShader(shader.tesselation_eval_id);
    sglr_check_error();
  }
  if(shader.id){
    glDeleteProgram(shader.id);
    sglr_check_error();
  }
  sglr_check_error();
}

void sglr_set_shader(sglr_Shader shader){
  glUseProgram(shader.id);
  sglr_check_error();
}

void sglr_unset_shader(){
  glUseProgram(0);
  sglr_check_error();
}

sglr_Shader sglr_make_shader_builtin_flat(){

  static sglr_Shader flat_shader;
  if(!flat_shader.id){

    flat_shader = sglr_make_shader(flat_vert,
                                   NULL,
                                   NULL,
                                   NULL,
                                   flat_frag);

  }
  return flat_shader;
}

sglr_Shader sglr_make_shader_builtin_text(){

  static sglr_Shader text_shader;
  if(!text_shader.id){

    text_shader = sglr_make_shader(bitmap_font_vert,
                                   NULL,
                                   NULL,
                                   NULL,
                                   bitmap_font_frag);

  }
  return text_shader;
}

//uniforms

void sglr_set_uniform_int(sglr_Shader shader, const char* name, uint32_t i){
  int loc = glGetUniformLocation(shader.id, name);
  sglr_check_error();

  if(loc == -1){
    return;
  }

  glUniform1i(loc,
              i);
  
  sglr_check_error();
}

void sglr_set_uniform_mat4(sglr_Shader shader, const char* name, mat4 mat){
  int loc = glGetUniformLocation(shader.id, name);
  sglr_check_error();

  if(loc == -1){
    return;
  }
  glUniformMatrix4fv(loc,
                     1,
                     0,
                     mat.a_f);
  sglr_check_error();
}

void sglr_set_shader_debug_name(sglr_Shader shader, const char* name){
  glObjectLabel(GL_PROGRAM,
                shader.id,
                strlen(name),
                name);
  sglr_check_error();
}
