#include "sglr_stats.h"

const char* sglr_gpu_name(){
  static const char* name;
  if(!name){
    name = glGetString(GL_RENDERER);
  }
  return name;
}
const char* sglr_gpu_vendor(){
  static const char* vendor;
  if(!vendor){
    vendor = glGetString(GL_VENDOR);
  }
  return vendor;
}
const char* sglr_gl_version(){
  static const char* version;
  if(!version){
    version = glGetString(GL_VERSION);
  }
  return version;
}
const char* sglr_glsl_version(){
  static const char* glsl_version;
  if(!glsl_version){
    glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);
  }
  return glsl_version;
}
void sglr_begin_query_time_elapsed_ns(){
  sglr_Context* context = sglr_current_context();
  
  if(!context->stats.time_query_id){
    glCreateQueries(GL_TIME_ELAPSED, 1, &context->current_stats.time_query_id);
    sglr_check_error();
  }
      
  glBeginQuery(GL_TIME_ELAPSED, context->current_stats.time_query_id);
  sglr_check_error();
}

int64_t sglr_end_query_time_elapsed_ns(){
  sglr_Context* context = sglr_current_context();
  
  if(context){
    glEndQuery(GL_TIME_ELAPSED);
    sglr_check_error();

    int64_t time = 0;
    glGetQueryObjectui64v(context->current_stats.time_query_id, GL_QUERY_RESULT, &time);

    sglr_check_error();
    return time;
  }

  return 0;
}

void sglr_stats_reset(){
  sglr_Context* context = sglr_current_context();
  if(context){
    context->stats = context->current_stats;
    
    sglr_stats_reset_triangle_count();
  }  
}

void sglr_stats_reset_triangle_count(){
  sglr_Context* context = sglr_current_context();
  if(context){
    context->current_stats.triangle_count = 0;
  }
}
void sglr_stats_add_triangle_count(int32_t triangles){
  sglr_Context* context = sglr_current_context();
  if(context){
    context->current_stats.triangle_count += triangles;
  }
}
void sglr_stats_add_triangle_count_indexed(int32_t index_count, GLenum topology){
  if(topology == GL_TRIANGLES){
    sglr_stats_add_triangle_count(index_count / 3);
  }else{
    //@todo, handle topology
    asm("int3");
  }
}

int32_t sglr_stats_triangle_count(){
  sglr_Context* context = sglr_current_context();
  if(context){
    return context->stats.triangle_count;
  }
}