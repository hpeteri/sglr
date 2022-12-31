#include "sglr_context.h"
#include "sglr_command_buffer.h"

#include "sglr_log.h" //debug_logger

static sglr_Context* sglr_context_;


sglr_Context* sglr_make_context(n1_Allocator allocator){
  sglr_Context* context = (sglr_Context*)allocator.alloc(sizeof(sglr_Context));
  
  N1_ZERO_MEMORY(context);
  context->allocator = allocator;
  
  sglr_make_debug_logger();

  //global vao
  glGenVertexArrays(1, &context->vao);
  sglr_check_error();
  
  return context;
}

void sglr_free_context(sglr_Context* context){
  if(!context)
    return;

  n1_Allocator allocator = context->allocator;
  allocator.free(context);

  sglr_set_context(NULL);  
}

void sglr_set_context(sglr_Context* context){
  sglr_context_ = context;
  glBindVertexArray(context->vao);
}

sglr_Context* sglr_current_context(){
  return sglr_context_;
}

void sglr_flush(){
  sglr_Context* context = sglr_current_context();

  if(!context)
    return;
  
  sglr_CommandBuffer* cb = context->command_buffers;
  while(cb){
    sglr_command_buffer_execute(cb);

    sglr_CommandBuffer* next = cb->next;
    
    sglr_free_command_buffer(cb);
    cb = next;
  }

  glFinish();
  glFlush();
  
  context->command_buffers = NULL;
}
