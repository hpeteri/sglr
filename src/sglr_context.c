#include "sglr_context.h"

#include "sglr_log.h" //debug_logger

static sglr_Context* sglr_context_;


sglr_Context* sglr_make_context(n1_Allocator allocator){
  sglr_Context* context = (sglr_Context*)allocator.alloc(sizeof(sglr_Context));
  
  N1_ZERO_MEMORY(context);
  context->allocator = allocator;
  
  sglr_make_debug_logger();

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
}

sglr_Context* sglr_current_context(){
  return sglr_context_;
}
