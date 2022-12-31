#ifndef SGLR_CONTEXT_H
#define SGLR_CONTEXT_H

#include "c_allocator/n1_allocator.h"


//include all
#include "sglr_render_target.h"

typedef struct sglr_Context{
  n1_Allocator allocator;

  sglr_RenderTarget main_render_target;
  
} sglr_Context;

sglr_Context* sglr_make_context(n1_Allocator allocator);

void          sglr_free_context(sglr_Context* context);
void          sglr_set_context(sglr_Context* context);
sglr_Context* sglr_current_context();

#endif
