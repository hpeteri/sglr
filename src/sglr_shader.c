#include "sglr_shader.h"
#include "sglr_shader_builtin.c"


static int sglr_check_shader_module(const GLuint module){
  int success = 0;
  glGetShaderiv(module, GL_COMPILE_STATUS, &success);
  
  if(success)
    return 1;
  
  char buffer[1024];
  glGetShaderInfoLog(module, 1024, NULL, buffer);

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
  if(!sglr_check_shader_module(shader.vertex_id)){

    sglr_check_error();
    return shader;
  }
  
  sglr_check_error();
  
  //fragment
  shader.fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shader.fragment_id, 1, &fragment, NULL);
  glCompileShader(shader.fragment_id);
  if(!sglr_check_shader_module(shader.fragment_id)){
    sglr_check_error();
    return shader;
  }
  
  sglr_check_error();

  //link
  glAttachShader(shader.id, shader.vertex_id);
  glAttachShader(shader.id, shader.fragment_id);
  glLinkProgram(shader.id);

  if(!sglr_check_shader_link(shader.id)){
    sglr_check_error();
    return shader;
  }


  //query locations
  shader.pos_loc   = glGetAttribLocation(shader.id, "vert_pos");
  shader.tc_loc    = glGetAttribLocation(shader.id, "vert_tc");
  shader.color_loc = glGetAttribLocation(shader.id, "vert_color");
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

sglr_Shader sglr_make_shader_builtin_simple(){
  static sglr_Shader simple_shader;
  if(!simple_shader.id){
    return simple_shader,
      simple_shader = sglr_make_shader(simple_vert0_,
                                       simple_frag0_);
  }
  return simple_shader;
}

sglr_Shader sglr_make_shader_builtin_text(){
  static sglr_Shader text_shader;
  if(!text_shader.id){
    return text_shader,
      text_shader = sglr_make_shader(bitmap_font_vert,
                                     bitmap_font_frag);
  }
  return text_shader;

}

//uniforms

void sglr_set_uniform_mat4(sglr_Shader shader, const char* name, mat4 mat){

  int loc = glGetUniformLocation(shader.id, name);
  sglr_check_error();

  if(loc == -1)
    *(int*)NULL = 0;
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
